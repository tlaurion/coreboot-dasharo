/* SPDX-License-Identifier: GPL-2.0-only */

/*
 * Unlike log.c this implements TCPA log according to TPM2 specification
 * rather then using coreboot-specific log format.
 *
 * First entry is in TPM1.2 format and serves as a header, the rest are in
 * a newer format which supports SHA256 and multiple hashes, but we always
 * store one hash in SHA1 format.
 *
 * This is defined in "TCG EFI Protocol Specification" and is what skiboot
 * uses.
 */

#include <endian.h>
#include <console/console.h>
#include <security/tpm/tspi.h>
#include <region_file.h>
#include <string.h>
#include <symbols.h>
#include <cbmem.h>
#include <bootstate.h>
#include <vb2_sha.h>

struct vendor_info {
	uint8_t vendor_info_size;
	uint16_t next_offset; // Offset within data array of tcpa_table.
};

struct log_event {
	uint32_t pcr;
	uint32_t event_type;
	uint32_t digest_count;
	struct {
		uint16_t hash_type;
		uint8_t *hash;
	} digests[ENABLED_TPM_ALGS_NUM];
	uint32_t name_len;
	char *name;
};

static uint16_t tpmalg_from_vb2_hash(enum vb2_hash_algorithm hash_type)
{
	switch (hash_type) {
	case VB2_HASH_SHA1:
		return TPM2_ALG_SHA1;
	case VB2_HASH_SHA256:
		return TPM2_ALG_SHA256;
	case VB2_HASH_SHA384:
		return TPM2_ALG_SHA384;
	case VB2_HASH_SHA512:
		return TPM2_ALG_SHA512;

	default:
		return 0xFF;
	}
}

static enum vb2_hash_algorithm tpmalg_to_vb2_hash(uint16_t hash_type)
{
	switch (hash_type) {
	case TPM2_ALG_SHA1:
		return VB2_HASH_SHA1;
	case TPM2_ALG_SHA256:
		return VB2_HASH_SHA256;
	case TPM2_ALG_SHA384:
		return VB2_HASH_SHA384;
	case TPM2_ALG_SHA512:
		return VB2_HASH_SHA512;

	default:
		return VB2_HASH_INVALID;
	}
}

static struct vendor_info *get_vendor_info(struct tcpa_table *tclt)
{
	uint8_t *p;

	/* Start at the first variable-sized part of the header. */
	p = (uint8_t *)tclt->header.digest_sizes;
	/* Skip over it. */
	p += ENABLED_TPM_ALGS_NUM * sizeof(tclt->header.digest_sizes[0]);
	/* *p is `uint8_t vendor_info_size` here. */
	return (struct vendor_info *)p;
}

static uint16_t get_events_start(struct tcpa_table *tclt)
{
	return (uint8_t *)get_vendor_info(tclt) + sizeof(struct vendor_info) -
		tclt->data;
}

static uint16_t get_uint16(uint8_t **data)
{
	uint16_t value;
	memcpy(&value, *data, sizeof(value));
	*data += sizeof(uint16_t);
	return le16toh(value);
}

static uint32_t get_uint32(uint8_t **data)
{
	uint32_t value;
	memcpy(&value, *data, sizeof(value));
	*data += sizeof(uint32_t);
	return le32toh(value);
}

/* Returns non-zero if an event was parsed. */
static int parse_log_event(struct tcpa_table *tclt, struct log_event *ev, uint16_t *offset)
{
	uint8_t *tce;
	uint32_t i;
	uint16_t start = get_events_start(tclt);

	if (start + *offset == get_vendor_info(tclt)->next_offset)
		return 0;

	tce = &tclt->data[start + *offset];

	ev->pcr = get_uint32(&tce);
	ev->event_type = get_uint32(&tce);
	ev->digest_count = get_uint32(&tce);

	for (i = 0; i < ev->digest_count; ++i) {
		ev->digests[i].hash_type = get_uint16(&tce);

		ev->digests[i].hash = tce;
		tce += vb2_digest_size(tpmalg_to_vb2_hash(ev->digests[i].hash_type));
	}

	ev->name_len = get_uint32(&tce);

	ev->name = (char *)tce;
	tce += ev->name_len;

	*offset = (tce - tclt->data) - start;
	return 1;
}

static struct tcpa_table *tcpa_cbmem_init(void)
{
	static struct tcpa_table *tclt;
	if (tclt)
		return tclt;

	if (cbmem_possibly_online()) {
		int i;
		struct tcg_efi_spec_id_event *hdr;
		struct tcpa_log_ref *tcpa_ref;
		struct vendor_info *vendor_info;

		tclt = cbmem_find(CBMEM_ID_TPM_LOG);
		if (tclt)
			return tclt;

		tclt = cbmem_add(CBMEM_ID_TPM_LOG, MAX_TCPA_LOG_SIZE);
		if (!tclt)
			return NULL;

		hdr = &tclt->header;
		memset(hdr, 0, sizeof(*hdr));

		hdr->num_of_algorithms = htole32(ENABLED_TPM_ALGS_NUM);

		hdr->event_type = htole32(EV_NO_ACTION);
		hdr->event_size = htole32(29 +
					  ENABLED_TPM_ALGS_NUM * sizeof(hdr->digest_sizes[0]) +
					  sizeof(*vendor_info));
		memcpy(hdr->signature, TCG_EFI_SPEC_ID_EVENT_SIGNATURE, sizeof(hdr->signature));
		hdr->platform_class = htole32(0x00); // client platform
		hdr->spec_version_minor = 0x00;
		hdr->spec_version_major = 0x02;
		hdr->spec_errata = 0x00;
		hdr->uintn_size = 0x02; // 64-bit UINT

		for (i = 0; i < ENABLED_TPM_ALGS_NUM; ++i) {
			hdr->digest_sizes[i].alg_id = tpmalg_from_vb2_hash(enabled_tpm_algs[i]);
			hdr->digest_sizes[i].digest_size = vb2_digest_size(enabled_tpm_algs[i]);
		}

		vendor_info = get_vendor_info(tclt);
		vendor_info->vendor_info_size = sizeof(*vendor_info) - 1;
		vendor_info->next_offset = get_events_start(tclt);

		tcpa_ref = cbmem_add(CBMEM_ID_TPM_LOG_REF, sizeof(*tcpa_ref));
		tcpa_ref->start = (uintptr_t)tclt;
		tcpa_ref->size = MAX_TCPA_LOG_SIZE;
	}
	return tclt;
}

struct tcpa_table *tcpa_log_init(void)
{
	static struct tcpa_table *tclt;

	/* We are dealing here with pre CBMEM environment.
	 * If cbmem isn't available use CAR or SRAM */
	if (!cbmem_possibly_online() &&
		!CONFIG(VBOOT_RETURN_FROM_VERSTAGE))
		return (struct tcpa_table *)_tpm_tcpa_log;
	else if (ENV_ROMSTAGE &&
		!CONFIG(VBOOT_RETURN_FROM_VERSTAGE)) {
		tclt = tcpa_cbmem_init();
		if (!tclt)
			return (struct tcpa_table *)_tpm_tcpa_log;
	} else {
		tclt = tcpa_cbmem_init();
	}

	return tclt;
}

void tcpa_log_dump(void *unused)
{
	uint16_t offset;
	struct log_event ev;
	struct tcpa_table *tclt;

	tclt = tcpa_log_init();
	if (!tclt)
		return;

	printk(BIOS_INFO, "coreboot TCPA measurements:\n\n");
	offset = 0;
	while (parse_log_event(tclt, &ev, &offset)) {
		uint32_t i;

		printk(BIOS_INFO, " PCR-%u [%s]:\n", ev.pcr, ev.name);

		for (i = 0; i < ev.digest_count; ++i) {
			enum vb2_hash_algorithm hash_type;
			int digest_size, j;

			hash_type = tpmalg_to_vb2_hash(ev.digests[i].hash_type);
			digest_size = vb2_digest_size(hash_type);

			printk(BIOS_INFO, "  %6s: ", vb2_get_hash_algorithm_name(hash_type));
			for (j = 0; j < digest_size; ++j)
				printk(BIOS_INFO, "%02x", ev.digests[i].hash[j]);
			printk(BIOS_INFO, "\n");
		}
	}
	printk(BIOS_INFO, "\n");
}

static void put_uint16(uint8_t **data, uint16_t value)
{
	value = htole16(value);
	memcpy(*data, &value, sizeof(value));
	*data += sizeof(uint16_t);
}

static void put_uint32(uint8_t **data, uint32_t value)
{
	value = htole32(value);
	memcpy(*data, &value, sizeof(value));
	*data += sizeof(uint32_t);
}

void tcpa_log_add_table_entry(const char *name, uint32_t pcr, const struct tpm_digest *digests,
			      int digests_len)
{
	struct vendor_info *vendor_info;
	struct tcpa_table *tclt;
	uint16_t name_len, needed_size;
	uint8_t *tce;
	int i;

	if (!name) {
		printk(BIOS_WARNING, "TCPA: TCPA entry name not set\n");
		return;
	}

	tclt = tcpa_log_init();
	if (!tclt) {
		printk(BIOS_WARNING, "TCPA: Log non-existent!\n");
		return;
	}

	vendor_info = get_vendor_info(tclt);

	name_len = strlen(name) + 1;
	needed_size = 4 * sizeof(uint32_t) + name_len;
	for (i = 0; i < digests_len; ++i)
		needed_size += sizeof(uint16_t) + vb2_digest_size(digests[i].hash_type);

	if (sizeof(*tclt) + vendor_info->next_offset + needed_size > MAX_TCPA_LOG_SIZE) {
		printk(BIOS_WARNING, "TCPA: TCPA log table is full\n");
		return;
	}

	tce = &tclt->data[vendor_info->next_offset];

	put_uint32(&tce, pcr);
	put_uint32(&tce, EV_ACTION);
	put_uint32(&tce, digests_len);

	for (i = 0; i < digests_len; ++i) {
		int hash_size = vb2_digest_size(digests[i].hash_type);

		put_uint16(&tce, tpmalg_from_vb2_hash(digests[i].hash_type));

		memcpy(tce, digests[i].hash, hash_size);
		tce += hash_size;
	}

	put_uint32(&tce, name_len);
	memcpy(tce, name, name_len);

	vendor_info->next_offset += needed_size;
}

void tcpa_preram_log_clear(void)
{
	printk(BIOS_INFO, "TCPA: Clearing coreboot TCPA log\n");
	struct tcpa_table *tclt = (struct tcpa_table *)_tpm_tcpa_log;
	get_vendor_info(tclt)->next_offset = get_events_start(tclt);
}

#if !CONFIG(VBOOT_RETURN_FROM_VERSTAGE)
static void recover_tcpa_log(int is_recovery)
{
	uint16_t offset;
	struct log_event ev;

	struct tcpa_table *preram_log = (struct tcpa_table *)_tpm_tcpa_log;

	if (tcpa_cbmem_init() == NULL) {
		printk(BIOS_WARNING, "TCPA: CBMEM not available, something went wrong\n");
		return;
	}

	offset = 0;
	while (parse_log_event(preram_log, &ev, &offset)) {
		uint32_t i;
		struct tpm_digest digests[ENABLED_TPM_ALGS_NUM];

		for (i = 0; i < ev.digest_count; ++i) {
			digests[i].hash_type = tpmalg_to_vb2_hash(ev.digests[i].hash_type);
			digests[i].hash = ev.digests[i].hash;
		}

		tcpa_log_add_table_entry(ev.name, ev.pcr, digests, ev.digest_count);
	}
}
CBMEM_CREATION_HOOK(recover_tcpa_log);
#endif

int
tcpa_measure_cache_to_pcr(void)
{
	uint16_t offset;
	struct log_event ev;
	struct tcpa_table *tclt;

	tclt = tcpa_log_init();
	if (!tclt) {
		printk(BIOS_WARNING, "TCPA: Log non-existent!\n");
		return VB2_ERROR_UNKNOWN;
	}

	printk(BIOS_DEBUG, "TPM: Write digests cached in TCPA log to PCR\n");

	offset = 0;
	while (parse_log_event(tclt, &ev, &offset)) {
		int result;
		uint32_t i;
		struct tpm_digest digests[ENABLED_TPM_ALGS_NUM];

		for (i = 0; i < ev.digest_count; ++i) {
			digests[i].hash_type = tpmalg_to_vb2_hash(ev.digests[i].hash_type);
			digests[i].hash = ev.digests[i].hash;
		}

		printk(BIOS_DEBUG, "TPM: Write digest for %s into PCR %d\n", ev.name, ev.pcr);

		result = tlcl_extend(ev.pcr, digests, ev.digest_count);
		if (result != TPM_SUCCESS) {
			printk(BIOS_ERR,
			       "TPM: Writing digest of %s into PCR failed with error %d\n",
			       ev.name, result);
			return VB2_ERROR_UNKNOWN;
		}
	}

	return VB2_SUCCESS;
}

BOOT_STATE_INIT_ENTRY(BS_PAYLOAD_BOOT, BS_ON_ENTRY, tcpa_log_dump, NULL);
