/* SPDX-License-Identifier: BSD-3-Clause */

#include <console/console.h>
#include <security/tpm/tis.h>
#include <security/tpm/tss.h>
#include <vb2_api.h>

#include "tcg-1.2/tss.h"
#include "tcg-2.0/tss.h"

/*
 * This unit dispatches to either TPM1.2 or TPM2.0 implementation based on
 * TPM family determined on probing during initialization.
 */

static int tpm_family;

/* Probe for TPM device and chose implementation based on the returned TPM family. */
uint32_t tlcl_lib_init(void)
{
	tis_sendrecv_fn tis_sendrecv;

	if (tpm_family != 0)
		return VB2_SUCCESS;

	tis_sendrecv = tis_probe(&tpm_family);
	if (tis_sendrecv == NULL) {
		printk(BIOS_ERR, "%s: tis_probe returned error\n", __func__);
		return VB2_ERROR_UNKNOWN;
	}

#if CONFIG(TPM1)
	if (tpm_family == 1) {
		tlcl12_lib_init(tis_sendrecv);
		return VB2_SUCCESS;
	}
#endif
#if CONFIG(TPM2)
	if (tpm_family == 2) {
		tlcl2_lib_init(tis_sendrecv);
		return VB2_SUCCESS;
	}
#endif

	printk(BIOS_ERR, "%s: tis_probe returned incorrect tpm_family: %d\n", __func__,
	       tpm_family);
	tpm_family = 0;
	return VB2_ERROR_UNKNOWN;
}

uint32_t tlcl_startup(void)
{
#if CONFIG(TPM1)
	if (tpm_family == 1)
		return tlcl12_startup();
#endif
#if CONFIG(TPM2)
	if (tpm_family == 2)
		return tlcl2_startup();
#endif

	die("%s: can't be used with TPM %d\n", __func__, tpm_family);
}

uint32_t tlcl_resume(void)
{
#if CONFIG(TPM1)
	if (tpm_family == 1)
		return tlcl12_resume();
#endif
#if CONFIG(TPM2)
	if (tpm_family == 2)
		return tlcl2_resume();
#endif

	die("%s: can't be used with TPM %d\n", __func__, tpm_family);
}

uint32_t tlcl_save_state(void)
{
#if CONFIG(TPM1)
	if (tpm_family == 1)
		return tlcl12_save_state();
#endif
#if CONFIG(TPM2)
	if (tpm_family == 2)
		return tlcl2_save_state();
#endif

	die("%s: can't be used with TPM %d\n", __func__, tpm_family);
}

uint32_t tlcl_self_test_full(void)
{
#if CONFIG(TPM1)
	if (tpm_family == 1)
		return tlcl12_self_test_full();
#endif
#if CONFIG(TPM2)
	if (tpm_family == 2)
		return tlcl2_self_test_full();
#endif

	die("%s: can't be used with TPM %d\n", __func__, tpm_family);
}

uint32_t tlcl_write(uint32_t index, const void *data, uint32_t length)
{
#if CONFIG(TPM1)
	if (tpm_family == 1)
		return tlcl12_write(index, data, length);
#endif
#if CONFIG(TPM2)
	if (tpm_family == 2)
		return tlcl2_write(index, data, length);
#endif

	die("%s: can't be used with TPM %d\n", __func__, tpm_family);
}

uint32_t tlcl_read(uint32_t index, void *data, uint32_t length)
{
#if CONFIG(TPM1)
	if (tpm_family == 1)
		return tlcl12_read(index, data, length);
#endif
#if CONFIG(TPM2)
	if (tpm_family == 2)
		return tlcl2_read(index, data, length);
#endif

	die("%s: can't be used with TPM %d\n", __func__, tpm_family);
}

uint32_t tlcl_assert_physical_presence(void)
{
#if CONFIG(TPM1)
	if (tpm_family == 1)
		return tlcl12_assert_physical_presence();
#endif
#if CONFIG(TPM2)
	if (tpm_family == 2)
		return tlcl2_assert_physical_presence();
#endif

	die("%s: can't be used with TPM %d\n", __func__, tpm_family);
}

uint32_t tlcl_physical_presence_cmd_enable(void)
{
#if CONFIG(TPM1)
	if (tpm_family == 1)
		return tlcl12_physical_presence_cmd_enable();
#endif
#if CONFIG(TPM2)
	if (tpm_family == 2)
		return tlcl2_physical_presence_cmd_enable();
#endif

	die("%s: can't be used with TPM %d\n", __func__, tpm_family);
}

uint32_t tlcl_finalize_physical_presence(void)
{
#if CONFIG(TPM1)
	if (tpm_family == 1)
		return tlcl12_finalize_physical_presence();
#endif
#if CONFIG(TPM2)
	if (tpm_family == 2)
		return tlcl2_finalize_physical_presence();
#endif

	die("%s: can't be used with TPM %d\n", __func__, tpm_family);
}

uint32_t tlcl_force_clear(void)
{
#if CONFIG(TPM1)
	if (tpm_family == 1)
		return tlcl12_force_clear();
#endif
#if CONFIG(TPM2)
	if (tpm_family == 2)
		return tlcl2_force_clear();
#endif

	die("%s: can't be used with TPM %d\n", __func__, tpm_family);
}

uint32_t tlcl_extend(int pcr_num, const uint8_t *in_digest, uint8_t *out_digest)
{
#if CONFIG(TPM1)
	if (tpm_family == 1)
		return tlcl12_extend(pcr_num, in_digest, out_digest);
#endif
#if CONFIG(TPM2)
	if (tpm_family == 2)
		return tlcl2_extend(pcr_num, in_digest, out_digest);
#endif

	die("%s: can't be used with TPM %d\n", __func__, tpm_family);
}
