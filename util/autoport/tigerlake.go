package main

import "fmt"

type tigerlake struct {
}

func (i tigerlake) Scan(ctx Context, addr PCIDevData) {
	fmt.Printf("tigerlake\n")
	inteltool := ctx.InfoSource.GetInteltool()

	/* FIXME:XX Move this somewhere else.  */
	MainboardIncludes = append(MainboardIncludes, "drivers/intel/gma/int15.h")
	MainboardEnable += (`	/* FIXME: fix these values. */
	install_intel_vga_int15_handler(GMA_INT15_ACTIVE_LFP_INT_LVDS,
					GMA_INT15_PANEL_FIT_DEFAULT,
					GMA_INT15_BOOT_DISPLAY_DEFAULT, 0);
`)

	DevTree = DevTreeNode{
		Chip:          "northbridge/intel/tigerlake",
		MissingParent: "northbridge",
		Comment:       "FIXME: GPU registers may not always apply.",
		Registers: map[string]string{
			"gpu_dp_b_hotplug":                    FormatInt32((inteltool.IGD[0xc4030] >> 2) & 7),
			"gpu_dp_c_hotplug":                    FormatInt32((inteltool.IGD[0xc4030] >> 10) & 7),
			"gpu_dp_d_hotplug":                    FormatInt32((inteltool.IGD[0xc4030] >> 18) & 7),
			"gpu_panel_port_select":               FormatInt32((inteltool.IGD[0xc7208] >> 30) & 3),
			"gpu_panel_power_up_delay":            FormatInt32((inteltool.IGD[0xc7208] >> 16) & 0x1fff),
			"gpu_panel_power_backlight_on_delay":  FormatInt32(inteltool.IGD[0xc7208] & 0x1fff),
			"gpu_panel_power_down_delay":          FormatInt32((inteltool.IGD[0xc720c] >> 16) & 0x1fff),
			"gpu_panel_power_backlight_off_delay": FormatInt32(inteltool.IGD[0xc720c] & 0x1fff),
			"gpu_panel_power_cycle_delay":         FormatInt32(inteltool.IGD[0xc7210] & 0xff),
			"gpu_cpu_backlight":                   FormatHex32(inteltool.IGD[0x48254]),
			"gpu_pch_backlight":                   FormatHex32((inteltool.IGD[0xc8254] >> 16) * 0x10001),
			"gfx": fmt.Sprintf("GMA_STATIC_DISPLAYS(%d)", (inteltool.IGD[0xc6200] >> 12) & 1),
		},
		Children: []DevTreeNode{
			{
				Chip: "cpu_cluster",
				Dev:  0,
			},
		},
	}

	PutPCIDev(addr, "Host bridge")

	KconfigBool["SOC_INTEL_TIGERLAKE"] = true
	KconfigBool["HAVE_ACPI_TABLES"] = true

	DSDTIncludes = append(DSDTIncludes, DSDTInclude{
		File: "cpu/intel/common/acpi/cpu.asl",
	})
}

func init() {
	// RegisterPCI(0x8086, 0x9a14, tigerlake{})
	for _, id := range []uint16{
		0x9a49,
	} {
		RegisterPCI(0x8086, id, GenericVGA{GenericPCI{}})
	}

	/* PCIe bridge */
	for _, id := range []uint16{
		0x9a09, 0x9a23, 0xa0bc,
		0xa0b0, 0xa0b1, 0xa0b2,
	} {
		RegisterPCI(0x8086, id, GenericPCI{})
	}

	/* UNKNOWN PLEASE IMPLEMENT CORRECTLY */
	for _, id := range []uint16{
		0x9a0d, 0x9a13, 0x9a1b,
		0xa0e8, 0xa0e9, 0xa0ea,
		0xa0e0, 0xa082, 0xa0a3, 0xa0a4,
	}{
		RegisterPCI(0x8086, id, GenericPCI{})
	}
}
