/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

// GPP_D9 SCI
Method (_L29, 0, Serialized) {
	Debug = Concatenate("GPE _L29: ", ToHexString(\_SB.PCI0.LPCB.EC0.WFNO))
	If (\_SB.PCI0.LPCB.EC0.ECOK) {
		If (\_SB.PCI0.LPCB.EC0.WFNO == One) {
			Notify(\_SB.LID0, 0x80)
		}
	}
}
