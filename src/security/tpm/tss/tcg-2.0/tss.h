/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef TSS2_H__
#define TSS2_H__

#include "tss_structures.h"

/*
 * Declarations for "private" functions which are dispatched to by tss.c in
 * the parent directory based on TPM family.
 */

void tlcl2_lib_init(tis_sendrecv_fn sendrecv);
uint32_t tlcl2_save_state(void);
uint32_t tlcl2_resume(void);
uint32_t tlcl2_startup(void);
uint32_t tlcl2_self_test_full(void);
uint32_t tlcl2_read(uint32_t index, void *data, uint32_t length);
uint32_t tlcl2_write(uint32_t index, const void *data, uint32_t length);
uint32_t tlcl2_assert_physical_presence(void);
uint32_t tlcl2_physical_presence_cmd_enable(void);
uint32_t tlcl2_finalize_physical_presence(void);
uint32_t tlcl2_force_clear(void);
uint32_t tlcl2_extend(int pcr_num, const uint8_t *in_digest, uint8_t *out_digest);

#endif
