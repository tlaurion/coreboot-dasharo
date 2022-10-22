/* SPDX-License-Identifier: GPL-2.0-only */

/*
 * Unlike log.c this implements TCPA log according to TPM1.2 specification
 * rather then using coreboot-specific log format.
 */

#include <endian.h>
#include <console/console.h>
#include <security/tpm/tspi.h>
#include <string.h>
#include <symbols.h>
#include <cbmem.h>
#include <bootstate.h>
#include <vb2_sha.h>

#define EV_NO_ACTION  0x03
#define EV_ACTION     0x05

static struct tcpa_table *tcpa_cbmem_init(void)
{
	static struct tcpa_table *tclt;
	if (tclt)
		return tclt;

	if (cbmem_possibly_online()) {
		size_t tcpa_log_len;
		struct spec_id_event_data *hdr;
		struct tcpa_log_ref *tcpa_ref;

		tclt = cbmem_find(CBMEM_ID_TPM_LOG);
		if (tclt)
			return tclt;

		tcpa_log_len = sizeof(*tclt) + MAX_TCPA_LOG_ENTRIES * sizeof(tclt->entries[0]);
		tclt = cbmem_add(CBMEM_ID_TPM_LOG, tcpa_log_len);
		if (!tclt)
			return NULL;

		memset(tclt, 0, sizeof(*tclt));
		hdr = &tclt->spec_id;

		/* Fill in first "header" entry. */
		tclt->event_type = htole32(EV_NO_ACTION);
		tclt->event_data_size = htole32(sizeof(*hdr) + hdr->vendor_info_size);
		strcpy(hdr->signature, TCPA_SPEC_ID_EVENT_SIGNATURE);
		hdr->platform_class = htole32(0x00); // client platform
		hdr->spec_version_minor = 0x02;
		hdr->spec_version_major = 0x01;
		hdr->spec_errata = 0x01;
		hdr->vendor_info_size = sizeof(tclt->max_entries) + sizeof(tclt->num_entries);

		tclt->max_entries = MAX_TCPA_LOG_ENTRIES;
		tclt->num_entries = 0;

		tcpa_ref = cbmem_add(CBMEM_ID_TPM_LOG_REF, sizeof(*tcpa_ref));
		tcpa_ref->start = (uintptr_t)tclt;
		tcpa_ref->size = tcpa_log_len;
	}

	return tclt;
}

struct tcpa_table *tcpa_log_init(void)
{
	static struct tcpa_table *tclt;

	/* We are dealing here with pre CBMEM environment.
	 * If cbmem isn't available use CAR or SRAM */
	if (!cbmem_possibly_online() &&
		!CONFIG(VBOOT_RETURN_FROM_VERSTAGE)) {
		return (struct tcpa_table *)_tpm_tcpa_log;
	} else if (ENV_ROMSTAGE &&
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
	int i, j;
	struct tcpa_table *tclt;

	tclt = tcpa_log_init();
	if (!tclt)
		return;

	printk(BIOS_INFO, "coreboot TCPA measurements:\n\n");
	for (i = 0; i < tclt->num_entries; i++) {
		struct tcpa_entry *tce = &tclt->entries[i];

		printk(BIOS_INFO, " PCR-%u ", le32toh(tce->pcr));

		for (j = 0; j < TCPA_DIGEST_MAX_LENGTH; j++)
			printk(BIOS_INFO, "%02x", tce->digest[j]);

		printk(BIOS_INFO, " %s [%s]\n", "SHA1", tce->name);
	}
	printk(BIOS_INFO, "\n");
}

void tcpa_log_add_table_entry(const char *name, const uint32_t pcr,
			      enum vb2_hash_algorithm digest_algo,
			      const uint8_t *digest,
			      const size_t digest_len)
{
	struct tcpa_table *tclt;
	struct tcpa_entry *tce;

	tclt = tcpa_log_init();
	if (!tclt) {
		printk(BIOS_WARNING, "TCPA: Log non-existent!\n");
		return;
	}

	if (!name) {
		printk(BIOS_WARNING, "TCPA: TCPA entry name not set\n");
		return;
	}

	if (tclt->num_entries >= tclt->max_entries) {
		printk(BIOS_WARNING, "TCPA: TCPA log table is full\n");
		return;
	}

	tce = &tclt->entries[tclt->num_entries++];

	tce->pcr = htole32(pcr);
	tce->event_type = htole32(EV_ACTION);

	memcpy(tce->digest, digest, digest_len);

	tce->name_length = htole32(TCPA_PCR_HASH_NAME);
	strncpy(tce->name, name, TCPA_PCR_HASH_NAME - 1);
}

void tcpa_preram_log_clear(void)
{
	printk(BIOS_INFO, "TCPA: Clearing coreboot TCPA log\n");
	struct tcpa_table *tclt = (struct tcpa_table *)_tpm_tcpa_log;
	tclt->max_entries = MAX_TCPA_LOG_ENTRIES;
	tclt->num_entries = 0;
}

#if !CONFIG(VBOOT_RETURN_FROM_VERSTAGE)
static void recover_tcpa_log(int is_recovery)
{
	struct tcpa_table *preram_log = (struct tcpa_table *)_tpm_tcpa_log;
	struct tcpa_table *ram_log = NULL;
	int i;

	if (preram_log->num_entries > MAX_PRERAM_TCPA_LOG_ENTRIES) {
		printk(BIOS_WARNING,
		       "TCPA: Pre-RAM TCPA log is too full, possible corruption\n");
		return;
	}

	ram_log = tcpa_cbmem_init();
	if (!ram_log) {
		printk(BIOS_WARNING, "TCPA: CBMEM not available something went wrong\n");
		return;
	}

	for (i = 0; i < preram_log->num_entries; i++) {
		struct tcpa_entry *tce = &ram_log->entries[ram_log->num_entries++];

		tce->pcr = preram_log->entries[i].pcr;
		tce->event_type = preram_log->entries[i].event_type;

		memcpy(tce->digest, preram_log->entries[i].digest, TCPA_DIGEST_MAX_LENGTH);

		tce->name_length = htole32(TCPA_PCR_HASH_NAME);
		strncpy(tce->name, preram_log->entries[i].name, TCPA_PCR_HASH_NAME - 1);
	}
}
CBMEM_CREATION_HOOK(recover_tcpa_log);
#endif

BOOT_STATE_INIT_ENTRY(BS_PAYLOAD_BOOT, BS_ON_ENTRY, tcpa_log_dump, NULL);
