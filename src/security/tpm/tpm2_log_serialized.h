/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef __TCPA_SPEC_LOG_SERIALIZED_H__
#define __TCPA_SPEC_LOG_SERIALIZED_H__

/*
 * This can't be part of commonlib, because of CONFIG macro because of tcpa_table redefinition.
 */

#include <stdint.h>

#include <commonlib/tpm2_log_serialized.h>

#define MAX_TCPA_LOG_SIZE 4096
#define TCPA_PCR_HASH_NAME 50

struct tcpa_table {
	struct tcg_efi_spec_id_event header; // TCG_PCR_EVENT actually
	/* Digest sizes followed by vendor info size and vendor info */

	uint8_t data[0];
} __packed;

#endif
