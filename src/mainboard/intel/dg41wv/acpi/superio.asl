/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#undef SUPERIO_DEV
#undef SUPERIO_PNP_BASE
#undef W83627DHG_SHOW_UARTA
#undef W83627DHG_SHOW_UARTB
#undef W83627DHG_SHOW_KBC
#undef W83627DHG_SHOW_PS2M
#undef W83627DHG_SHOW_HWMON
#define SUPERIO_DEV		SIO0
#define SUPERIO_PNP_BASE	0x2e
#define W83627DHG_SHOW_UARTA
#define W83627DHG_SHOW_UARTB
#define W83627DHG_SHOW_KBC
#define W83627DHG_SHOW_PS2M
#define W83627DHG_SHOW_HWMON
#include <superio/winbond/w83627dhg/acpi/superio.asl>
