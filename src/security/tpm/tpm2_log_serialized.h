/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef __TPM2_LOG_SERIALIZED_H__
#define __TPM2_LOG_SERIALIZED_H__

#include <stdint.h>

#include <commonlib/helpers.h>
#include <commonlib/tpm_log_defs.h>

#define MAX_TCPA_LOG_ENTRIES 50
#define TCPA_PCR_HASH_NAME 50
#define TCPA_PCR_HASH_LEN 10
/* Assumption of 2K TCPA log size reserved for CAR/SRAM, but depends on hash */
#define MAX_PRERAM_TCPA_LOG_ENTRIES 15

/*
 * TPM2.0 log entries can't be generally represented as C structures due to
 * varying number of digests and their sizes. However, it works as long as
 * we're only using single kind of digests.
 */
#if CONFIG(TPM_LOG_CB) && CONFIG(TPM1)
#  define TCPA_DIGEST_MAX_LENGTH SHA1_DIGEST_SIZE
#elif CONFIG(TPM_LOG_CB) && CONFIG(TPM2)
#  define TCPA_DIGEST_MAX_LENGTH SHA256_DIGEST_SIZE
#elif CONFIG(TPM_LOG_TPM12)
#  define TCPA_DIGEST_MAX_LENGTH SHA1_DIGEST_SIZE
#elif CONFIG(TPM_LOG_TPM2)
#  if CONFIG(TPM_HASH_SHA1)
#    define TCPA_DIGEST_MAX_LENGTH SHA1_DIGEST_SIZE
#  endif
#  if CONFIG(TPM_HASH_SHA256)
#    define TCPA_DIGEST_MAX_LENGTH SHA256_DIGEST_SIZE
#  endif
#  if CONFIG(TPM_HASH_SHA384)
#    define TCPA_DIGEST_MAX_LENGTH SHA384_DIGEST_SIZE
#  endif
#  if CONFIG(TPM_HASH_SHA512)
#    define TCPA_DIGEST_MAX_LENGTH SHA512_DIGEST_SIZE
#  endif
#endif

#ifndef TCPA_DIGEST_MAX_LENGTH
#  error "Misconfiguration: failed to determine TPM hashing algorithm"
#endif

/* TCG_PCR_EVENT2 */
struct tcpa_entry {
	uint32_t pcr;
	uint32_t event_type;
	uint32_t digest_count;
	uint16_t digest_type;
	uint8_t digest[TCPA_DIGEST_MAX_LENGTH];
	uint32_t name_length;
	char name[TCPA_PCR_HASH_NAME];
} __packed;

struct tcpa_table {
	struct tcg_efi_spec_id_event header; /* TCG_PCR_EVENT actually */
	struct tpm_digest_sizes digest_sizes[1];
	uint8_t vendor_info_size;
	uint16_t max_entries;
	uint16_t num_entries;
	struct tcpa_entry entries[0]; /* Variable number of entries */
} __packed;

#endif
