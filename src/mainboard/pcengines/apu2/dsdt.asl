/* SPDX-License-Identifier: GPL-2.0-only */

/* DefinitionBlock Statement */

#if CONFIG(BOARD_PCENGINES_APU2)
#define DEVICE_NAME "apu2
#elif CONFIG(BOARD_PCENGINES_APU3)
#define DEVICE_NAME "apu3
#elif CONFIG(BOARD_PCENGINES_APU4)
#define DEVICE_NAME "apu4
#elif CONFIG(BOARD_PCENGINES_APU5)
#define DEVICE_NAME "apu5
#endif

#include <acpi/acpi.h>
DefinitionBlock (
	"DSDT.AML",	/* Output filename */
	"DSDT",		/* Signature */
	0x02,		/* DSDT Revision, needs to be 2 for 64bit */
	OEM_ID,
	ACPI_TABLE_CREATOR,
	0x00010001	/* OEM Revision */
	)
{	/* Start of ASL file */

	/* Globals for the platform */
	#include "acpi/mainboard.asl"

	/* Describe the USB Overcurrent pins */
	#include "acpi/usb_oc.asl"

	/* PCI IRQ mapping for the Southbridge */
	#include <southbridge/amd/pi/hudson/acpi/pcie.asl>

	/* Describe the processor tree (\_SB) */
	#include <cpu/amd/pi/00730F01/acpi/cpu.asl>

	/* Contains the supported sleep states for this chipset */
	#include <southbridge/amd/common/acpi/sleepstates.asl>

	/* Contains the Sleep methods (WAK, PTS, GTS, etc.) */
	#include "acpi/sleep.asl"

	/* System Bus */
	Scope(\_SB) { /* Start \_SB scope */
		/* global utility methods expected within the \_SB scope */
		#include <arch/x86/acpi/globutil.asl>

		/* Describe IRQ Routing mapping for this platform (within the \_SB scope) */
		#include "acpi/routing.asl"

		Device(PCI0) {
			/* Describe the AMD Northbridge */
			#include <northbridge/amd/pi/00730F01/acpi/northbridge.asl>

			/* Describe the AMD Fusion Controller Hub Southbridge */
			#include <southbridge/amd/pi/hudson/acpi/fch.asl>
		}

		/* Describe PCI INT[A-H] for the Southbridge */
		#include <southbridge/amd/pi/hudson/acpi/pci_int.asl>

		/* Describe the GPIO controller in southbridge */
		#include "acpi/gpio.asl"
	} /* End \_SB scope */

	/* Describe SMBUS for the Southbridge */
	#include <southbridge/amd/pi/hudson/acpi/smbus.asl>

	/* Define the General Purpose Events for the platform */
	#include "acpi/gpe.asl"

	/* Define the System Indicators for the platform */
	#include "acpi/si.asl"

	/* Super IO devices (COM ports) */
	#include "acpi/superio.asl"

	/* GPIO buttons and leds */
	#include "acpi/buttons.asl"
	#include "acpi/leds.asl"
}
/* End of ASL file */
