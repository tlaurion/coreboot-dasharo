package main

import (
)

type tigerlake_southbridge struct {
}

func (b tigerlake_southbridge) EnableGPE(in int) {
}

func (b tigerlake_southbridge) EncodeGPE(in int) int {
	return in + 0x10
}

func (b tigerlake_southbridge) DecodeGPE(in int) int {
	return in - 0x10
}

func (b tigerlake_southbridge) GetGPIOHeader() string {
	return "southbridge/intel/bd82x6x/pch.h"
}

func (b tigerlake_southbridge) NeedRouteGPIOManually() {
}

func (b tigerlake_southbridge) Scan(ctx Context, addr PCIDevData) {
	SouthBridge = &b
}
func init() {
	RegisterPCI(0x8086, 0x9a14, tigerlake_southbridge{})
}
