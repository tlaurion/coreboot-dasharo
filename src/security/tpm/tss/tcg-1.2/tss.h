/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef TSS12_H_
#define TSS12_H_

#include "tss_structures.h"

/*
 * Declarations for "private" functions which are dispatched to by tss.c in
 * the parent directory based on TPM family.
 */

void tlcl12_lib_init(tis_sendrecv_fn sendrecv);
uint32_t tlcl12_save_state(void);
uint32_t tlcl12_resume(void);
uint32_t tlcl12_startup(void);
uint32_t tlcl12_self_test_full(void);
uint32_t tlcl12_read(uint32_t index, void *data, uint32_t length);
uint32_t tlcl12_write(uint32_t index, const void *data, uint32_t length);
uint32_t tlcl12_assert_physical_presence(void);
uint32_t tlcl12_physical_presence_cmd_enable(void);
uint32_t tlcl12_finalize_physical_presence(void);
uint32_t tlcl12_force_clear(void);
uint32_t tlcl12_extend(int pcr_num, const uint8_t *in_digest, uint8_t *out_digest);

#endif
