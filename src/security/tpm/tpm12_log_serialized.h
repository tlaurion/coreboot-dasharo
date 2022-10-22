/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef __TPM12_LOG_SERIALIZED_H__
#define __TPM12_LOG_SERIALIZED_H__

#include <stdint.h>

#define TCPA_SPEC_ID_EVENT_SIGNATURE "Spec ID Event00"

#define MAX_TCPA_LOG_ENTRIES 50
#define TCPA_DIGEST_MAX_LENGTH 20
#define TCPA_PCR_HASH_NAME 50
#define TCPA_PCR_HASH_LEN 10
/* Assumption of 2K TCPA log size reserved for CAR/SRAM */
#define MAX_PRERAM_TCPA_LOG_ENTRIES 15

struct tcpa_entry {
	uint32_t pcr;
	uint32_t event_type;
	uint8_t digest[TCPA_DIGEST_MAX_LENGTH];
	uint32_t name_length;
	char name[TCPA_PCR_HASH_NAME];
} __packed;

struct spec_id_event_data {
	char signature[16];
	uint32_t platform_class;
	uint8_t spec_version_minor;
	uint8_t spec_version_major;
	uint8_t spec_errata;
	uint8_t reserved;
	uint8_t vendor_info_size;
} __packed;

struct tcpa_table {
	/* The first entry of the log is inlined and describes the log itself */
	uint32_t pcr;
	uint32_t event_type;
	uint8_t digest[TCPA_DIGEST_MAX_LENGTH];
	uint32_t event_data_size;
	struct spec_id_event_data spec_id;
	/* Vendor info, outside of spec_id to avoid #ifdef on using tcpa_table */
	uint16_t max_entries;
	uint16_t num_entries;

	struct tcpa_entry entries[0]; /* Variable number of entries */
} __packed;

#endif
