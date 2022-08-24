/* SPDX-License-Identifier: GPL-2.0-only */

#include <arch/mmio.h>
#include <console/console.h>
#include <security/intel/cbnt/cbnt.h>
#include <security/intel/txt/txt.h>
#include <security/intel/txt/txt_register.h>
#include <soc/cnl_memcfg_init.h>
#include <soc/romstage.h>
#include <cbfs.h>

static const struct cnl_mb_cfg board_memcfg_cfg = {
	/* Access memory info through SMBUS. */
	.spd[0] = {
		.read_type = READ_SMBUS,
		.spd_spec = {.spd_smbus_address = 0xA0}
	},
	.spd[1] = {
		.read_type = NOT_EXISTING,
	},
	.spd[2] = {
		.read_type = READ_SMBUS,
		.spd_spec = {.spd_smbus_address = 0xA4}
	},
	.spd[3] = {
		.read_type = NOT_EXISTING,
	},

	/* Baseboard uses 121, 81 and 100 rcomp resistors */
	.rcomp_resistor = {121, 81, 100},

	/*
	 * Baseboard Rcomp target values.
	 */
	.rcomp_targets = {100, 40, 20, 20, 26},

	/* Baseboard is an interleaved design */
	.dq_pins_interleaved = 1,

	/* Baseboard is using config 2 for vref_ca */
	.vref_ca_config = 2,

	/* Enable Early Command Training */
	.ect = 1,
};

void mainboard_memory_init_params(FSPM_UPD *memupd)
{	
	cannonlake_memcfg_init(&memupd->FspmConfig, &board_memcfg_cfg);
	size_t size = 0;
	uint32_t bios_acm_error;
	uint64_t acm_status;
	uint64_t txt_error;
	uint32_t txt_devid;
	uint32_t txt_ftif;

	intel_txt_log_bios_acm_error();
	txt_devid = read32((void *)TXT_DIDVID);
	bios_acm_error = read32((void *)TXT_BIOSACM_ERRORCODE);
	acm_status = read64((void *)TXT_SPAD);
	txt_error = read64((void *)TXT_ERROR);
	txt_ftif = read32((void *)0xFED30800);

	printk(BIOS_DEBUG, "TXT-TEE: TXT_BIOSACM_ERRORCODE: %08x\n", bios_acm_error);
	printk(BIOS_DEBUG, "TXT-TEE: TXT_SPAD: %016llx\n", acm_status);
	printk(BIOS_DEBUG, "TXT-TEE: TXT_ERROR: %016llx\n", txt_error);
	printk(BIOS_DEBUG, "TXT-TEE: TXT DIDVID: %08x\n", txt_devid);
	printk(BIOS_DEBUG, "TXT-TEE: TXT FTIF: %08x\n", txt_ftif);

	memupd->FspmConfig.TxtImplemented = 1;
	memupd->FspmConfig.Txt = 1;
	memupd->FspmConfig.SinitMemorySize = 0x50000;
	memupd->FspmConfig.TxtHeapMemorySize = 0xf0000;
	memupd->FspmConfig.TxtDprMemorySize = 4 << 20;
	memupd->FspmConfig.TxtDprMemoryBase = 1; // Set to non-zero, FSP will update it
	memupd->FspmConfig.BiosAcmBase = (uintptr_t)cbfs_map(CONFIG_INTEL_TXT_CBFS_BIOS_ACM,
							     &size);
	memupd->FspmConfig.BiosAcmSize = size;
	memupd->FspmConfig.ApStartupBase = (uintptr_t)cbfs_map("txt_ap_init", &size);
	memupd->FspmTestConfig.TxtAcheckRequest = 0;
	memupd->FspmConfig.IsTPMPresence = 1;
	memupd->FspmConfig.TgaSize = 0;
	memupd->FspmConfig.TxtLcpPdBase = 0;
	memupd->FspmConfig.TxtLcpPdSize = 0;
}
