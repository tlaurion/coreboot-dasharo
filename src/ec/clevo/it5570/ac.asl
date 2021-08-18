/* Initially copied from System76: src/mainboard/system76/cml-u/acpi */
/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

Device (AC)
{
	Name (_HID, "ACPI0003" /* Power Source Device */)  // _HID: Hardware ID
	Name (_PCL, Package (0x01)  // _PCL: Power Consumer List
	{
		_SB
	})

	Name (ACFG, One)

	Method (_PSR, 0, NotSerialized)  // _PSR: Power Source
	{
		Return (ACFG)
	}

	Method (_STA, 0, NotSerialized)  // _STA: Status
	{
		Return (0x0F)
	}
}
