/* SPDX-License-Identifier: GPL-2.0-only */

#include <arch/mmio.h>
#include <soc/pci_devs.h>
#include <device/pci_ops.h>
#include <console/console.h>
#include <drivers/crb/tpm.h>
#include <security/intel/txt/txt_register.h>
#include <stdint.h>

#include "ptt.h"

#define PCI_ME_HFSTS4 0x64
#define PTT_ENABLE (1 << 19)

#define PTT_CRB_DATA_BUFFER 0x80
/* Max bytes from PTT_CRB_DATA_BUFFER, 0xFED40080 - 0xFED40FFF = 3968 Bytes */
#define PTT_CRB_LENGTH 3968

/* Dump Intel ME register */
static uint32_t read_register(int reg_addr)
{
	if (!PCH_DEV_CSE)
		return 0xFFFFFFFF;

	return pci_read_config32(PCH_DEV_CSE, reg_addr);
}

/*
 * ptt_active()
 *
 * Check if PTT Flag is set - so that PTT is active.
 *
 * Return true if active, false otherwise.
 */
bool ptt_active(void)
{
	uint32_t ver_ftif = read32((void *)TXT_STS_FTIF);

	if (ver_ftif != 0 && ver_ftif != UINT32_MAX) {
		if ((ver_ftif & TXT_PTT_PRESENT) == TXT_PTT_PRESENT)
			return true;
	}

	uint32_t fwsts4 = read_register(PCI_ME_HFSTS4);

	if (fwsts4 == 0xFFFFFFFF)
		return false;

	if ((fwsts4 & PTT_ENABLE) == 0) {
		printk(BIOS_DEBUG, "Intel ME Establishment bit not valid.\n");
		return false;
	}

	return true;
}

/*
 * ptt_init
 *
 * Initializes the CRB Control Area for PTT.
 *
 * The Command and response address/size must be initialized first. Not all
 * platforms/FSPs do it.
 */
void ptt_init(void)
{
	write32(CRB_REG(0, CRB_REG_CMD_SIZE), PTT_CRB_LENGTH);
	write64(CRB_REG(0, CRB_REG_CMD_ADDR), TPM_CRB_BASE_ADDRESS + PTT_CRB_DATA_BUFFER);
	write32(CRB_REG(0, CRB_REG_RESP_SIZE), PTT_CRB_LENGTH);
	write64(CRB_REG(0, CRB_REG_RESP_ADDR), TPM_CRB_BASE_ADDRESS + PTT_CRB_DATA_BUFFER);

	printk(BIOS_DEBUG, "PTT Control Area:\n");
	printk(BIOS_DEBUG, "\tCommand size: 0x%x\n", read32(CRB_REG(0, CRB_REG_CMD_SIZE)));
	printk(BIOS_DEBUG, "\tCommand addr: 0x%llx\n", read64(CRB_REG(0, CRB_REG_CMD_ADDR)));
	printk(BIOS_DEBUG, "\tResponse size: 0x%x\n", read32(CRB_REG(0, CRB_REG_RESP_SIZE)));
	printk(BIOS_DEBUG, "\tResponse addr: 0x%llx\n", read64(CRB_REG(0, CRB_REG_RESP_ADDR)));
}
