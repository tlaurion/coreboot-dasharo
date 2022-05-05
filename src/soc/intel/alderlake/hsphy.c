/* SPDX-License-Identifier: GPL-2.0-only */

#define __SIMPLE_DEVICE__

#include <assert.h>
#include <stdlib.h>
#include <console/console.h>
#include <device/device.h>
#include <device/mmio.h>
#include <device/pci_def.h>
#include <device/pci_ops.h>
#include <intelblocks/cse.h>
#include <soc/hsphy.h>
#include <soc/iomap.h>
#include <soc/pci_devs.h>
#include <vb2_api.h>
#include <lib.h>

#define HASHALG_SHA1		0x00000001
#define HASHALG_SHA256		0x00000002
#define HASHALG_SHA384		0x00000003
#define HASHALG_SHA512		0x00000004

#define MAX_HASH_SIZE		64 // 64 is max size for SHA512

#define GET_IP_FIRMWARE_CMD	0x21

#define HSPHY_PAYLOAD_SIZE		32*KiB

#define CPU_PID_PCIE_PHYX16_BROADCAST	0x55

struct ip_push_model {
	uint16_t count;
	union {
		uint16_t address;
		uint16_t type; // Valid only for Extended mode push model operations
	} mode;
	uint32_t data[0];
};

static void *pcr_reg_address(uint8_t pid, uint16_t offset)
{
	uintptr_t reg_addr;

	/* Create an address based off of port id and offset. */
	reg_addr = REG_BASE_ADDRESS;
	reg_addr += ((uintptr_t)pid) << 16;
	reg_addr += (uintptr_t)offset;

	return (void *)reg_addr;
}

static void cpu_pcr_write32(uint8_t pid, uint16_t offset, uint32_t indata)
{
	/* Ensure the PCR offset is correctly aligned. */
	assert(IS_ALIGNED(offset, sizeof(indata)));

	write32(pcr_reg_address(pid, offset), indata);
}

static int heci_get_hsphy_payload(void *buf, uint32_t *buf_size, uint8_t *hash_buf,
				  uint8_t *hash_alg)
{
	size_t reply_size;

	struct heci_ip_load_request {
		struct mkhi_hdr hdr;
		uint32_t version;
		uint32_t operation;
		uint32_t dram_base_low;
		uint32_t dram_base_high;
		uint32_t memory_size;
		uint32_t reserved;
	} __packed msg = {
		.hdr = {
			.group_id = MKHI_GROUP_ID_BUP_COMMON,
			.command = GET_IP_FIRMWARE_CMD,
		},
		.version = 1,
		.operation = 1,
		.dram_base_low = (uintptr_t)buf,
		.dram_base_high = 0,
		.memory_size = *buf_size,
		.reserved = 0,
	};

	struct heci_ip_load_response {
		struct mkhi_hdr hdr;
		uint32_t payload_size;
		uint32_t reserved[2];
		uint32_t status;
		uint8_t hash_type;
		uint8_t hash[MAX_HASH_SIZE];
	} __packed reply;

	if (!buf || !buf_size || !hash_buf || !hash_alg) {
		printk(BIOS_ERR, "%s: Invalid parameters\n", __func__);
		return -1;
	}

	reply_size = sizeof(reply);
	memset(&reply, 0, reply_size);

	if (heci_send_receive(&msg, sizeof(msg), &reply, &reply_size, HECI_MKHI_ADDR)) {
		printk(BIOS_ERR, "HECI: Get IP firmware failed\n");
		return -1;
	}

	hexdump(&reply, sizeof(reply));

	if (reply.hdr.result) {
		printk(BIOS_ERR, "HECI: Get IP firmware response invalid\n");
		return -1;
	}

	*buf_size = reply.payload_size;
	*hash_alg = reply.hash_type;
	memcpy(hash_buf, reply.hash, MAX_HASH_SIZE);

	printk(BIOS_DEBUG, "HECI: Get IP firmware success. Response:\n");
	printk(BIOS_DEBUG, "  Payload size = 0x%x\n", *buf_size);
	printk(BIOS_DEBUG, "  Hash type used for signing payload = 0x%x\n", *hash_alg);

	return 0;
}

static int verify_hsphy_hash(void *buf, uint32_t buf_size, uint8_t *hash_buf, uint8_t hash_alg)
{
	enum vb2_hash_algorithm alg;
	uint32_t hash_size;
	uint8_t hash_calc[MAX_HASH_SIZE];

	switch (hash_alg) {
	case HASHALG_SHA256:
		alg = VB2_HASH_SHA256;
		hash_size = VB2_SHA256_DIGEST_SIZE;
		break;
	case HASHALG_SHA384:
		alg = VB2_HASH_SHA384;
		hash_size = VB2_SHA384_DIGEST_SIZE;
		break;
	case HASHALG_SHA512:
		alg = VB2_HASH_SHA512;
		hash_size = VB2_SHA512_DIGEST_SIZE;
		break;
	case HASHALG_SHA1:
	default:
		printk (BIOS_ERR, "Hash alg %d not supported, try SHA384\n", hash_alg);
		alg = VB2_HASH_SHA384;
		hash_size = VB2_SHA384_DIGEST_SIZE;
		break;
	}

	if (vb2_digest_buffer(buf, buf_size, alg, hash_calc, hash_size)) {
		printk(BIOS_ERR, "HSPHY SHA calculation failed\n");
		return -1;
	}

	if (memcmp(hash_buf, hash_calc, hash_size)) {
		printk(BIOS_ERR, "HSPHY SHA hashes do not match\n");
		hexdump(hash_buf, hash_size);
		hexdump(hash_calc, hash_size);
		return -1;
	}

	return 0;
}

static void upload_hsphy_to_cpu_pcie(void *buf, uint32_t buf_size)
{
	uint32_t i = 0, j = 0;
	struct ip_push_model *push_model = (struct ip_push_model *)buf;

	while (i < buf_size) {
		i += sizeof (*push_model);

		if ((push_model->mode.type == 0) && (push_model->count == 0)) {
			break; // End of file
		}

		for (j = 0; j < push_model->count; j++) {
			cpu_pcr_write32(CPU_PID_PCIE_PHYX16_BROADCAST,
					push_model->mode.address,
					push_model->data[j]);
			i += sizeof (uint32_t);
		}

		push_model = (struct ip_push_model *)(buf + i);
	}
}

void load_and_init_hsphy(void)
{
	void *hsphy_buf;
	uint8_t hsphy_hash[MAX_HASH_SIZE];
	uint8_t hash_type;
	uint32_t buf_size = HSPHY_PAYLOAD_SIZE;
	pci_devfn_t dev = PCH_DEV_CSE;
	uint16_t pci_cmd_bme_mem = PCI_COMMAND_MASTER | PCI_COMMAND_MEMORY;

	hsphy_buf = malloc(HSPHY_PAYLOAD_SIZE);

	if (!hsphy_buf) {
		printk(BIOS_ERR, "Could not allocate memory for HSPHY blob\n");
		return;
	}

	memset(hsphy_buf, 0, HSPHY_PAYLOAD_SIZE);

	if (!is_cse_enabled()) {
		printk(BIOS_ERR, "%s: CSME not enabled or not visible\n", __func__);
		return;
	}

	/* Ensure BAR, BME and memory space are enabled */
	if ((pci_read_config16(dev, PCI_COMMAND) & pci_cmd_bme_mem) != pci_cmd_bme_mem)
		pci_or_config16(dev, PCI_COMMAND, pci_cmd_bme_mem);


	if (pci_read_config32(dev, PCI_BASE_ADDRESS_0) == 0) {
		pci_and_config16(dev, PCI_COMMAND, ~pci_cmd_bme_mem);
		pci_write_config32(dev, PCI_BASE_ADDRESS_0, HECI1_BASE_ADDRESS);
		pci_or_config16(dev, PCI_COMMAND, pci_cmd_bme_mem);
	}

	if (heci_get_hsphy_payload(hsphy_buf, &buf_size, hsphy_hash, &hash_type))
		return;

	if (verify_hsphy_hash(hsphy_buf, buf_size, hsphy_hash, hash_type))
		return;
	
	upload_hsphy_to_cpu_pcie(hsphy_buf, buf_size);

	free(hsphy_buf);
}
