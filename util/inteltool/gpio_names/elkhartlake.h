#ifndef GPIO_NAMES_ALDERLAKE_H
#define GPIO_NAMES_ALDERLAKE_H

#include "gpio_groups.h"

/* ----------------------------- Elkhart Lake ----------------------------- */

const char *const elkhartlake_pch_group_a_names[] = {
"GP_A00","GP-In","n/a",
"GP_A01","GP-In","n/a",
"GP_A02","GP-In","n/a",
"GP_A03","GP-In","n/a",
"GP_A04","GP-In","n/a",
"GP_A05","GP-In","n/a",
"GP_A06","GP-In","n/a",
"GP_A07","GP-In","n/a",
"GP_A08","GP-In","n/a",
"GP_A09","GP-In","n/a",
"GP_A10","GP-In","n/a",
"GP_A11","GP-In","n/a",
"GP_A12","GP-In","n/a",
"GP_A13","GP-In","n/a",
"GP_A14","GP-In","n/a",
"GP_A15","GP-In","n/a",
"GP_A16","GP-In","n/a",
"GP_A17","GP-In","n/a",
"GP_A18","GP-In","n/a",
"GP_A19","GP-In","AVS_I2S5_SCLK",
"GP_A20","GP-In","AVS_I2S5_SFRM",
"GP_A21","GP-In","AVS_I2S5_TXD",
"GP_A22","GP-In","AVS_I2S5_RXD",
"GP_A23","GP-In","n/a",
};

const struct gpio_group elkhart_pch_group_a = {
	.display	= "------- GPIO Group GPP_A -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_a_names) / 3,
	.func_count	= 3,
	.pad_names	= elkhartlake_pch_group_a_names,
};

const char *const elkhartlake_pch_group_b_names[] = {
"GP_B00","Native F1","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_B01","Native F1","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_B02","Native F4/GP-In","n/a","n/a","ESPI_ALERT2_N","n/a","n/a","n/a","PSE_TGPIO25",
"GP_B03","Native F4/GP-In","n/a","n/a","ESPI_ALERT0_N","n/a","n/a","n/a","PSE_TGPIO26",
"GP_B04","Native F4/GP-In","n/a","n/a","ESPI_ALERT1_N","n/a","n/a","n/a","PSE_TGPIO27",
"GP_B05","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO06",
"GP_B06","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO07",
"GP_B07","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO08",
"GP_B08","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO09",
"GP_B09","Native F4/GP-In","PSE_I2C2_SDA","n/a","ESPI_CS3_N","n/a","n/a","n/a","n/a",
"GP_B10","Native F4/GP-In","PSE_I2C2_SCL","n/a","ESPI_ALERT3_N","n/a","n/a","n/a","n/a",
"GP_B11","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO06",
"GP_B12","Native F1","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_B13","Native F1","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_B14","GP-Out","PMC_TGPIO1","SIO_SPI0_CS1_N","PSE_SPI2_CS1_N","n/a","n/a","n/a","n/a",
"GP_B15","Native F5/GP-In","n/a","PSE_SPI2_CS0_N","n/a","ESPI_CS1_N","n/a","n/a","n/a",
"GP_B16","GP-In","n/a","PSE_SPI2_CLK","n/a","n/a","n/a","n/a","n/a",
"GP_B17","GP-In","n/a","PSE_SPI2_MISO","n/a","n/a","n/a","n/a","n/a",
"GP_B18","GP-Out","n/a","PSE_SPI2_MOSI","n/a","n/a","n/a","n/a","n/a",
"GP_B19","Native F5/GP-In","n/a","PSE_SPI3_CS0_N","n/a","ESPI_CS2_N","n/a","n/a","n/a",
"GP_B20","GP-In","RSVD","PSE_SPI3_CLK","n/a","n/a","n/a","n/a","n/a",
"GP_B21","GP-In","RSVD","PSE_SPI3_MISO","n/a","n/a","n/a","n/a","n/a",
"GP_B22","GP-Out","n/a","PSE_SPI3_MOSI","n/a","n/a","n/a","n/a","n/a",
"GP_B23","GP-Out","PCHHOT_N","SIO_SPI1_CS1_N","PSE_SPI3_CS1_N","n/a","n/a","n/a","PSE_TGPIO28",
"GPIO_RSVD_0","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GPIO_RSVD_1","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
};

const struct gpio_group elkhart_pch_group_b = {
	.display	= "------- GPIO Group GPP_B -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_b_names) / 9,
	.func_count	= 9,
	.pad_names	= elkhartlake_pch_group_b_names,
};

const char *const elkhartlake_pch_group_c_names[] = {
"GP_C00","Native F1","PSE_I2C3_SCL","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO18",
"GP_C01","Native F1","PSE_I2C3_SDA","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO19",
"GP_C02","Native F2/GP-Out","SMB_ALERT_N","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO29",
"GP_C03","GP-In","n/a","PSE_HSUART3_EN","n/a","n/a","RSVD","n/a","n/a",
"GP_C04","GP-In","n/a","PSE_UART3_RTS_N","PSE_HSUART3_DE","n/a","RSVD","n/a","n/a",
"GP_C05","GP-Out","n/a","PSE_UART3_CTS_N","n/a","n/a","SML_ALERT0_N","n/a","PSE_TGPIO30",
"GP_C06","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_C07","GP-In","n/a","PSE_HSUART3_RE","n/a","n/a","n/a","n/a","n/a",
"GP_C08","Native F2","DNX_FORCE_RELOAD","n/a","RSVD","n/a","n/a","n/a","n/a",
"GP_C09","GP-In","n/a","n/a","RSVD","n/a","n/a","n/a","n/a",
"GP_C10","GP-In","n/a","n/a","RSVD","n/a","n/a","n/a","n/a",
"GP_C11","GP-In","n/a","n/a","RSVD","n/a","n/a","n/a","n/a",
"GP_C12","GP-In","n/a","n/a","SIO_UART1_RXD","n/a","n/a","n/a","n/a",
"GP_C13","GP-In","n/a","n/a","SIO_UART1_TXD","n/a","n/a","n/a","n/a",
"GP_C14","GP-In","PSE_HSUART0_DE","n/a","SIO_UART1_RTS_N","n/a","n/a","n/a","n/a",
"GP_C15","GP-In","n/a","n/a","SIO_UART1_CTS_N","n/a","n/a","n/a","n/a",
"GP_C16","GP-In","n/a","PSE_UART3_RXD","SIO_I2C0_SDA","n/a","n/a","n/a","n/a",
"GP_C17","GP-In","n/a","PSE_UART3_TXD","SIO_I2C0_SCL","n/a","n/a","n/a","n/a",
"GP_C18","GP-In","n/a","SML_DATA0","SIO_I2C1_SDA","n/a","n/a","n/a","n/a",
"GP_C19","GP-In","n/a","SML_CLK0","SIO_I2C1_SCL","n/a","n/a","n/a","n/a",
"GP_C20","GP-In","n/a","RSVD","SIO_UART2_RXD","n/a","n/a","n/a","n/a",
"GP_C21","GP-In","n/a","RSVD","SIO_UART2_TXD","n/a","n/a","n/a","n/a",
"GP_C22","GP-In","A0: N/A B0: ISI_SPIM_MOSI","RSVD","SIO_UART2_RTS_N","n/a","n/a","n/a","n/a",
"GP_C23","GP-In","A0: N/A B0: ISI_SPIS_MOSI","RSVD","SIO_UART2_CTS_N","n/a","n/a","n/a","n/a",
};

const struct gpio_group elkhart_pch_group_c = {
	.display	= "------- GPIO Group GPP_C -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_c_names) / 9,
	.func_count	= 9,
	.pad_names	= elkhartlake_pch_group_c_names,
};

const char *const elkhartlake_pch_group_d_names[] = {
"GP_D00","GP-In","n/a","RSVD","PSE_SPI1_CS0_N","n/a","n/a","n/a","PSE_TGPIO32",
"GP_D01","GP-In","n/a","RSVD","PSE_SPI1_CLK","n/a","n/a","n/a","PSE_TGPIO33",
"GP_D02","GP-In","n/a","RSVD","PSE_SPI1_MISO","n/a","n/a","n/a","PSE_TGPIO34",
"GP_D03","GP-In","n/a","RSVD","PSE_SPI1_MOSI","n/a","n/a","n/a","PSE_TGPIO35",
"GP_D04","GP-In","n/a","RSVD","PSE_SPI1_CS1_N","n/a","n/a","n/a","PSE_TGPIO36",
"GP_D05","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_D06","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_D07","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_D08","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_D09","GP-In","n/a","n/a","n/a","n/a","n/a","SIO_SPI2_CS0_N","PSE_TGPIO10",
"GP_D10","GP-In","n/a","n/a","n/a","n/a","n/a","SIO_SPI2_CLK","PSE_TGPIO11",
"GP_D11","GP-In","n/a","n/a","n/a","n/a","n/a","SIO_SPI2_MISO","PSE_TGPIO12",
"GP_D12","GP-In","n/a","n/a","n/a","n/a","n/a","SIO_SPI2_MOSI","PSE_TGPIO13",
"GP_D13","GP-In","n/a","RSVD","n/a","n/a","n/a","n/a","PSE_TGPIO37",
"GP_D14","GP-In","n/a","RSVD","n/a","n/a","n/a","n/a","PSE_TGPIO38",
"GP_D15","GP-In","SIO_SPI2_CS1_N","RSVD","PSE_SPI0_CS1_N","n/a","n/a","n/a","PSE_TGPIO39",
"GP_D16","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO40",
"GP_D17","GP-In","A0: N/A B0: ISI_SPIM_MOSI","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO41",
"GP_D18","GP-In","A0: N/A B0: ISI_SPIS_MOSI","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO42",
"GP_D19","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO43",
"GPIO_RSVD_3","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
};

const struct gpio_group elkhart_pch_group_d = {
	.display	= "------- GPIO Group GPP_D -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_d_names) / 9,
	.func_count	= 9,
	.pad_names	= elkhartlake_pch_group_d_names,
};

const char *const elkhartlake_pch_group_dsw_names[] = {
"GP_DSW00","Native F1",
"GP_DSW01","Native F1",
"GP_DSW02","Native F1",
"GP_DSW03","Native F1",
"GP_DSW04","Native F1/GP-Out",
"GP_DSW05","Native F1/GP-Out",
"GP_DSW07","GP-Out",
"GP_DSW08","Native F1",
"GP_DSW09","Native F1/GP-Out",
"GP_DSW10","Native F1/GP-Out",
"GP_DSW11","Native F1/GP-Out",
"GPIO_RSVD_8","n/a",
"GPIO_RSVD_9","n/a",
"GPIO_RSVD_10","n/a",
"GPIO_RSVD_11","n/a",
"GPIO_RSVD_12","n/a",
};

const struct gpio_group elkhart_pch_group_dsw = {
	.display	= "------- GPIO Group GPP_DSW -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_dsw_names) / 2,
	.func_count	= 2,
	.pad_names	= elkhartlake_pch_group_dsw_names,
};

const char *const elkhartlake_pch_group_e_names[] = {
"GP_E00","Native F2/GP-In","SATAXPCIE_0","RSVD","RSVD","RSVD","RSVD","SATA_0_GP","n/a",
"GP_E01","GP-In","RSVD","RSVD","RSVD","RSVD","RSVD","RSVD","n/a",
"GP_E02","GP-In","RSVD","RSVD","RSVD","RSVD","RSVD","RSVD","n/a",
"GP_E03","GP-In","PNL_MISC_DDI1","RSVD","RSVD","RSVD","RSVD","CPU_GP0","PSE_TGPIO15",
"GP_E04","GP-In","n/a","RSVD","RSVD","RSVD","RSVD","PSE_PWM08","PSE_TGPIO44",
"GP_E05","GP-In","n/a","RSVD","RSVD","RSVD","RSVD","PSE_PWM09","PSE_TGPIO17",
"GP_E06","GP-Out","RSVD","RSVD","RSVD","RSVD","RSVD","PSE_PWM10","PSE_TGPIO18",
"GP_E07","GP-In","n/a","RSVD","RSVD","RSVD","RSVD","CPU_GP1","PSE_TGPIO16",
"GP_E08","GP-In","SATA_1_DEVSLP","RSVD","RSVD","n/a","RSVD","RSVD","PSE_TGPIO45",
"GP_E09","GP-In","n/a","RSVD","RSVD","n/a","RSVD","n/a","n/a",
"GP_E10","GP-In","RSVD","RSVD","RSVD","n/a","RSVD","RSVD","n/a",
"GP_E11","GP-In","RSVD","RSVD","RSVD","n/a","RSVD","RSVD","n/a",
"GP_E12","GP-In","RSVD","RSVD","RSVD","n/a","RSVD","RSVD","n/a",
"GP_E13","GP-In","RSVD","RSVD","RSVD","n/a","RSVD","RSVD","n/a",
"GP_E14","GP-In","PNL_MISC_DDI0","RSVD","RSVD","n/a","RSVD","n/a","PSE_TGPIO19",
"GP_E15","Native F2","RSVD","RSVD","RSVD","n/a","RSVD","PSE_CAN0_TX","PSE_TGPIO17",
"GP_E16","Native F2","RSVD","RSVD","RSVD","RSVD","RSVD","PSE_CAN0_RX","PSE_TGPIO16",
"GP_E17","GP-In","RSVD","RSVD","RSVD","PNL_MISC_DDI2","RSVD","PSE_PWM11","PSE_TGPIO46",
"GP_E18","Native F5","n/a","n/a","n/a","RSVD","n/a","PSE_PWM12","PSE_TGPIO23",
"GP_E19","Native F5","n/a","n/a","n/a","RSVD","n/a","PSE_PWM13","PSE_TGPIO24",
"GP_E20","GP-In","n/a","n/a","n/a","n/a","n/a","PSE_CAN1_TX","PSE_TGPIO14",
"GP_E21","GP-In","n/a","n/a","n/a","n/a","n/a","PSE_CAN1_RX","PSE_TGPIO15",
"GP_E22","GP-In","n/a","n/a","n/a","n/a","n/a","PSE_PWM14","PSE_TGPIO18",
"GP_E23","GP-Out","n/a","n/a","n/a","n/a","n/a","PSE_PWM15","PSE_TGPIO19",
};

const struct gpio_group elkhart_pch_group_e = {
	.display	= "------- GPIO Group GPP_E -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_e_names) / 9,
	.func_count	= 9,
	.pad_names	= elkhartlake_pch_group_e_names,
};

const char *const elkhartlake_pch_group_f_names[] = {
"GP_F00","Native F1","SIO_UART0_RTS_N","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_F01","Native F1","SIO_UART0_RXD","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_F02","Native F1","SIO_UART0_TXD","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_F03","Native F1","SIO_UART0_CTS_N","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_F04","Native F1","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_F05","Native F2","RSVD","RSVD","RSVD","n/a","n/a","n/a","PSE_TGPIO14",
"GP_F06","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO47",
"GP_F07","GP-Out","n/a","n/a","n/a","AVS_I2S4_SCLK","n/a","n/a","PSE_TGPIO14",
"GP_F08","Native F5","n/a","n/a","PSE_TRACEDATA_0","ISI_TRACEDATA_0","n/a","n/a","PSE_TGPIO48",
"GP_F09","Native F1","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_F10","GP-Out","n/a","n/a","n/a","AVS_I2S4_SFRM","n/a","n/a","PSE_TGPIO15",
"GP_F11","Native F5","n/a","RSVD","PSE_TRACECLK","ISI_TRACECLK","n/a","n/a","PSE_TGPIO49",
"GP_F12","Native F5","AVS_I2S4_TXD","RSVD","PSE_TRACESWO","ISI_TRACESWO","n/a","n/a","n/a",
"GP_F13","Native F5","AVS_I2S4_SFRM","RSVD","PSE_SWDIO","ISI_SWDIO","n/a","n/a","n/a",
"GP_F14","Native F5","AVS_I2S4_RXD","RSVD","PSE_TRACEDATA_1","ISI_TRACEDATA_1","n/a","n/a","n/a",
"GP_F15","Native F5","n/a","RSVD","PSE_TRACEDATA_2","ISI_TRACEDATA_2","n/a","n/a","n/a",
"GP_F16","Native F5","AVS_I2S4_SCLK","RSVD","PSE_SWCLK","ISI_SWCLK","n/a","n/a","n/a",
"GP_F17","Native F5","n/a","RSVD","PSE_TRACEDATA_3","ISI_TRACEDATA_3","n/a","n/a","PSE_TGPIO50",
"GP_F18","GP-In","n/a","n/a","n/a","AVS_I2S4_TXD","n/a","n/a","PSE_TGPIO16",
"GP_F19","GP-In","n/a","n/a","n/a","AVS_I2S4_RXD","n/a","n/a","PSE_TGPIO17",
"GP_F20","Native F1","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_F21","Native F1","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_F22","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_F23","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GPIO_RSVD_30","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GPIO_RSVD_31","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GPIO_RSVD_32","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GPIO_RSVD_33","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GPIO_RSVD_34","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GPIO_RSVD_35","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GPIO_RSVD_36","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
};

const struct gpio_group elkhart_pch_group_f = {
	.display	= "------- GPIO Group GPP_E -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_f_names) / 9,
	.func_count	= 9,
	.pad_names	= elkhartlake_pch_group_f_names,
};

const char *const elkhartlake_pch_group_g_names[] = {
"GP_G00","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G01","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G02","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G03","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G04","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G05","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G06","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G07","GP-In","n/a","n/a","DMIC_CLK_A0","n/a","n/a","n/a","n/a",
"GP_G08","Native F2","RSVD","n/a","DMIC_DATA0","n/a","n/a","n/a","n/a",
"GP_G09","Native F2","RSVD","RSVD","DMIC_CLK_A1","n/a","n/a","n/a","n/a",
"GP_G10","GP-In","n/a","n/a","DMIC_DATA1","n/a","n/a","n/a","n/a",
"GP_G11","GP-In","n/a","n/a","DMIC_DATA0","n/a","n/a","n/a","PSE_TGPIO07",
"GP_G12","Native F3/GP-In","SATA_1_GP","SATAXPCIE_1","DMIC_DATA1","n/a","n/a","n/a","PSE_TGPIO31",
"GP_G13","GP-In","n/a","n/a","DMIC_CLK_B0","n/a","n/a","n/a","PSE_TGPIO08",
"GP_G14","GP-In","n/a","n/a","DMIC_CLK_B1","n/a","n/a","n/a","PSE_TGPIO09",
"GP_G15","Native F1/GP-In","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G16","Native F1/GP-In","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G17","Native F1/Native F2","Reserved","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G18","Native F1/Native F2","Reserved","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G19","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G20","Native F1/GP-In","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G21","Native F1/GP-In","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G22","Native F1/GP-In","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G23","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GPIO_RSVD_2","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
};

const struct gpio_group elkhart_pch_group_g = {
	.display	= "------- GPIO Group GPP_G -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_g_names) / 9,
	.func_count	= 9,
	.pad_names	= elkhartlake_pch_group_g_names,
};

const char *const elkhartlake_pch_group_h_names[] = {
"GP_H00","GP-Out","n/a","n/a","PSE_UART5_RXD","n/a","n/a","n/a","n/a",
"GP_H01","GP-In","n/a","n/a","PSE_UART5_TXD","n/a","n/a","n/a","n/a",
"GP_H02","GP-Out","n/a","n/a","PSE_UART5_RTS_N","n/a","n/a","n/a","n/a",
"GP_H03","GP-In","n/a","n/a","PSE_UART5_CTS_N","n/a","n/a","n/a","PSE_TGPIO21",
"GP_H04","GP-In","n/a","n/a","PSE_PWM08","n/a","n/a","n/a","PSE_TGPIO10",
"GP_H05","GP-In","n/a","n/a","PSE_PWM09","n/a","n/a","n/a","PSE_TGPIO11",
"GP_H06","GP-In","PSE_I2C5_SDA","n/a","PSE_PWM10","n/a","n/a","n/a","n/a",
"GP_H07","GP-In","PSE_I2C5_SCL","n/a","PSE_PWM11","n/a","n/a","n/a","n/a",
"GP_H08","GP-In","RSVD","n/a","PSE_PWM12","n/a","n/a","n/a","n/a",
"GP_H09","GP-In","RSVD","n/a","PSE_PWM13","n/a","n/a","n/a","n/a",
"GP_H10","GP-In","n/a","n/a","PSE_PWM14","n/a","n/a","n/a","n/a",
"GP_H11","GP-In","n/a","n/a","PSE_PWM15","n/a","n/a","n/a","n/a",
"GP_H12","GP-In","n/a","n/a","M2_SKT2_CFG0","n/a","n/a","n/a","PSE_TGPIO51",
"GP_H13","GP-In","n/a","n/a","M2_SKT2_CFG1","n/a","n/a","n/a","PSE_TGPIO52",
"GP_H14","GP-In","n/a","n/a","M2_SKT2_CFG2","n/a","n/a","n/a","PSE_TGPIO53",
"GP_H15","GP-In","n/a","n/a","M2_SKT2_CFG3","n/a","n/a","n/a","PSE_TGPIO54",
"GP_H16","GP-In","DDI2_DDC_SCL","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_H17","GP-In","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_H18","Native F1","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_H19","GP-In","DDI2_DDC_SDA","n/a","PMC_TGPIO0","n/a","n/a","n/a","PSE_TGPIO20",
"GP_H20","GP-In","DDI2_HPD","n/a","RSVD","n/a","n/a","n/a","PSE_TGPIO55",
"GP_H21","GP-In","PSE_UART1_RTS_N","n/a","RSVD","n/a","n/a","n/a","PSE_TGPIO56",
"GP_H22","GP-In","n/a","n/a","RSVD","n/a","n/a","n/a","PSE_TGPIO57",
"GP_H23","GP-In","n/a","n/a","RSVD","n/a","n/a","n/a","PSE_TGPIO58",
};

const struct gpio_group elkhart_pch_group_h = {
	.display	= "------- GPIO Group GPP_H -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_h_names) / 9,
	.func_count	= 9,
	.pad_names	= elkhartlake_pch_group_h_names,
};

const char *const elkhartlake_pch_group_r_names[] = {
"GP_R00","Native F1","AVS_I2S0_SCLK","PSE_I2S0_SCLK","RSVD","n/a",
"GP_R01","Native F1","AVS_I2S0_SFRM","PSE_I2S0_SFRM","n/a","n/a",
"GP_R02","Native F1","AVS_I2S0_TXD","PSE_I2S0_TXD","RSVD","DMIC_CLK_B0",
"GP_R03","Native F1","AVS_I2S0_RXD","PSE_I2S0_RXD","RSVD","DMIC_CLK_B1",
"GP_R04","Native F1","n/a","n/a","n/a","DMIC_CLK_A1",
"GP_R05","GP-In","AVS_I2S1_RXD","n/a","n/a","DMIC_DATA1",
"GP_R06","GP-In","AVS_I2S1_TXD","n/a","n/a","DMIC_CLK_A0",
"GP_R07","GP-In","AVS_I2S1_SFRM","n/a","n/a","DMIC_DATA0",
};

const struct gpio_group elkhart_pch_group_r = {
	.display	= "------- GPIO Group GPP_R -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_r_names) / 6,
	.func_count	= 6,
	.pad_names	= elkhartlake_pch_group_r_names,
};

const char *const elkhartlake_pch_group_s_names[] = {
"GPIO_RSVD_13","n/a",
"GPIO_RSVD_14","n/a",
"GPIO_RSVD_15","n/a",
"GPIO_RSVD_16","n/a",
"GPIO_RSVD_17","n/a",
"GPIO_RSVD_18","n/a",
"GPIO_RSVD_19","n/a",
"GPIO_RSVD_20","n/a",
"GPIO_RSVD_21","n/a",
"GPIO_RSVD_22","n/a",
"GPIO_RSVD_23","n/a",
"GPIO_RSVD_24","n/a",
"GPIO_RSVD_25","n/a",
"GPIO_RSVD_26","n/a",
"GPIO_RSVD_27","n/a",
"GPIO_RSVD_28","n/a",
"GPIO_RSVD_29","n/a",
"GP_S00","Native F1",
"GP_S01","Native F1",
};

const struct gpio_group elkhart_pch_group_s = {
	.display	= "------- GPIO Group GPP_S -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_s_names) / 2,
	.func_count	= 2,
	.pad_names	= elkhartlake_pch_group_s_names,
};

const char *const elkhartlake_pch_group_t_names[] = {
"GP_T00","GP-In","n/a","SIO_I2C6_SDA","n/a","n/a","n/a","n/a","PSE_TGPIO08",
"GP_T01","GP-In","n/a","SIO_I2C6_SCL","n/a","n/a","n/a","n/a","PSE_TGPIO09",
"GP_T02","GP-In","n/a","SIO_I2C7_SDA","n/a","n/a","n/a","n/a","PSE_TGPIO07",
"GP_T03","GP-In","n/a","SIO_I2C7_SCL","n/a","n/a","n/a","n/a","PSE_TGPIO06",
"GP_T04","GP-In","n/a","n/a","RSVD","n/a","n/a","n/a","n/a",
"GP_T05","GP-In","n/a","n/a","RSVD","n/a","n/a","n/a","n/a",
"GP_T06","GP-In","USB2_OC1_N","n/a","RSVD","n/a","n/a","n/a","n/a",
"GP_T07","GP-In","n/a","n/a","RSVD","n/a","n/a","n/a","PSE_TGPIO59",
"GP_T08","GP-In","RSVD","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO22",
"GP_T09","GP-In","RSVD","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_T10","GP-In","RSVD","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_T11","GP-In","RSVD","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO06",
"GP_T12","GP-In","SIO_UART0_RXD","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_T13","GP-In","SIO_UART0_TXD","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_T14","GP-In","SIO_UART0_RTS_N","PSE_HSUART2_DE","n/a","n/a","n/a","n/a","n/a",
"GP_T15","GP-In","SIO_UART0_CTS_N","n/a","n/a","n/a","n/a","n/a","n/a",};

const struct gpio_group elkhart_pch_group_t = {
	.display	= "------- GPIO Group GPP_T -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_t_names) / 9,
	.func_count	= 9,
	.pad_names	= elkhartlake_pch_group_t_names,
};

const char *const elkhartlake_pch_group_u_names[] = {
"GP_U00","GP-In","PSE_I2C6_SCL","RSVD","n/a","n/a","n/a","n/a","n/a",
"GP_U01","GP-In","PSE_I2C6_SDA","RSVD","n/a","n/a","n/a","n/a","n/a",
"GP_U02","GP-In","PSE_I2C7_SCL","RSVD","n/a","n/a","n/a","n/a","n/a",
"GP_U03","GP-In","PSE_I2C7_SDA","RSVD","n/a","n/a","n/a","n/a","n/a",
"GP_U04","GP-In","n/a","RSVD","PSE_SPI1_CS0_N","n/a","n/a","n/a","n/a",
"GP_U05","GP-In","n/a","RSVD","PSE_SPI1_CLK","n/a","n/a","n/a","n/a",
"GP_U06","GP-In","n/a","RSVD","PSE_SPI1_MISO","n/a","n/a","n/a","n/a",
"GP_U07","GP-In","n/a","RSVD","PSE_SPI1_MOSI","n/a","n/a","n/a","PSE_TGPIO10",
"GP_U08","GP-In","n/a","RSVD","n/a","n/a","n/a","n/a","PSE_TGPIO10",
"GP_U09","GP-In","ISI_I2CS_SCL","RSVD","n/a","n/a","n/a","n/a","PSE_TGPIO11",
"GP_U10","GP-In","ISI_I2CS_SDA","RSVD","n/a","n/a","n/a","n/a","PSE_TGPIO12",
"GP_U11","GP-In","n/a","RSVD","n/a","n/a","n/a","n/a","PSE_TGPIO11",
"GP_U12","Native F1","n/a","RSVD","n/a","n/a","n/a","n/a","n/a",
"GP_U13","Native F1","n/a","RSVD","n/a","n/a","n/a","n/a","n/a",
"GP_U14","GP-In","n/a","RSVD","n/a","n/a","n/a","n/a","n/a",
"GP_U15","GP-In","n/a","RSVD","n/a","n/a","n/a","n/a","PSE_TGPIO13",
"GP_U16","Native F1","n/a","RSVD","n/a","n/a","n/a","n/a","n/a",
"GP_U17","Native F1","n/a","RSVD","n/a","n/a","n/a","n/a","n/a",
"GP_U18","Native F1","n/a","RSVD","n/a","n/a","n/a","n/a","n/a",
"GP_U19","GP-In","n/a","RSVD","n/a","n/a","n/a","n/a","PSE_TGPIO12",
"GPIO_RSVD_4","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GPIO_RSVD_5","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GPIO_RSVD_6","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GPIO_RSVD_7","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
};

const struct gpio_group elkhart_pch_group_u = {
	.display	= "------- GPIO Group GPP_U -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_u_names) / 9,
	.func_count	= 9,
	.pad_names	= elkhartlake_pch_group_u_names,
};

const char *const elkhartlake_pch_group_v_names[] = {
"GP_V00","GP-In",
"GP_V01","GP-In",
"GP_V02","GP-In",
"GP_V03","GP-In",
"GP_V04","GP-In",
"GP_V05","GP-In",
"GP_V06","GP-In",
"GP_V07","GP-In",
"GP_V08","GP-In",
"GP_V09","GP-In",
"GP_V10","GP-In",
"GP_V11","GP-In",
"GP_V12","GP-In",
"GP_V13","GP-In",
"GP_V14","GP-In",
"GP_V15","GP-In",
};

const struct gpio_group elkhart_pch_group_v = {
	.display	= "------- GPIO Group GPP_V -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_v_names) / 2,
	.func_count	= 7,
	.pad_names	= elkhartlake_pch_group_v_names,
};

const char *const elkhartlake_pch_group_vgpio_names[] = {
"VGPIO_0","n/a",
"VGPIO_4","n/a",
"VGPIO_5","n/a",
"VGPIO_6","n/a",
"VGPIO_7","n/a",
"VGPIO_8","n/a",
"VGPIO_9","n/a",
"VGPIO_10","n/a",
"VGPIO_11","n/a",
"VGPIO_12","n/a",
"VGPIO_13","n/a",
"VGPIO_18","n/a",
"VGPIO_19","n/a",
"VGPIO_20","n/a",
"VGPIO_21","n/a",
"VGPIO_22","n/a",
"VGPIO_23","n/a",
"VGPIO_24","n/a",
"VGPIO_25","n/a",
"VGPIO_30","n/a",
"VGPIO_31","n/a",
"VGPIO_32","n/a",
"VGPIO_33","n/a",
"VGPIO_34","n/a",
"VGPIO_35","n/a",
"VGPIO_36","n/a",
"VGPIO_37","n/a",
"VGPIO_39","n/a",
};

const struct gpio_group elkhart_pch_group_vgpio = {
	.display	= "------- GPIO Group GPP_VGPIO -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_vgpio_names) / 2,
	.func_count	= 2,
	.pad_names	= elkhartlake_pch_group_vgpio_names,
};


const char *const elkhartlake_pch_group_vgpio_usb_names[] = {
"VGPIO_USB_0","n/a",
"VGPIO_USB_1","n/a",
"VGPIO_USB_2","n/a",
"VGPIO_USB_3","n/a",
};

const struct gpio_group elkhart_pch_group_vgpio_usb = {
	.display	= "------- GPIO Group GPP_VGPIO_USB -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_vgpio_usb_names) / 2,
	.func_count	= 2,
	.pad_names	= elkhartlake_pch_group_vgpio_usb_names,
};

const struct gpio_group *const elkhartlake_community_0_groups[] = {
	&elkhart_pch_group_b,
    &elkhart_pch_group_t,
    &elkhart_pch_group_g,
};

const struct gpio_community elkhartlake_community_0 = {
	.name		= "------- GPIO Community 0 -------",
	.pcr_port_id	= 0x69,
	.group_count	= ARRAY_SIZE(elkhartlake_community_0_groups),
	.groups		= elkhartlake_community_0_groups,
};

const struct gpio_group *const elkhartlake_community_1_groups[] = {
    &elkhart_pch_group_v,
    &elkhart_pch_group_h,
    &elkhart_pch_group_d,
    &elkhart_pch_group_u,
    &elkhart_pch_group_vgpio,
};

const struct gpio_community elkhartlake_community_1 = {
	.name		= "------- GPIO Community 1 -------",
	.pcr_port_id	= 0x69,
	.group_count	= ARRAY_SIZE(elkhartlake_community_1_groups),
	.groups		= elkhartlake_community_1_groups,
};

const struct gpio_group *const elkhartlake_community_2_groups[] = {
    &elkhart_pch_group_dsw,
};

const struct gpio_community elkhartlake_community_2 = {
	.name		= "------- GPIO Community 2 -------",
	.pcr_port_id	= 0x69,
	.group_count	= ARRAY_SIZE(elkhartlake_community_2_groups),
	.groups		= elkhartlake_community_2_groups,
};

const struct gpio_group *const elkhartlake_community_3_groups[] = {
    &elkhart_pch_group_s,
    &elkhart_pch_group_a,
    &elkhart_pch_group_vgpio_usb,
};

const struct gpio_community elkhartlake_community_3 = {
	.name		= "------- GPIO Community 3 -------",
	.pcr_port_id	= 0x69,
	.group_count	= ARRAY_SIZE(elkhartlake_community_3_groups),
	.groups		= elkhartlake_community_3_groups,
};

const struct gpio_group *const elkhartlake_community_4_groups[] = {
    &elkhart_pch_group_c,
    &elkhart_pch_group_f,
    &elkhart_pch_group_e,
};

const struct gpio_community elkhartlake_community_4 = {
	.name		= "------- GPIO Community 4 -------",
	.pcr_port_id	= 0x69,
	.group_count	= ARRAY_SIZE(elkhartlake_community_4_groups),
	.groups		= elkhartlake_community_4_groups,
};

const struct gpio_group *const elkhartlake_community_5_groups[] = {
    &elkhart_pch_group_r,
};

const struct gpio_community elkhartlake_community_5 = {
	.name		= "------- GPIO Community 5 -------",
	.pcr_port_id	= 0x69,
	.group_count	= ARRAY_SIZE(elkhartlake_community_5_groups),
	.groups		= elkhartlake_community_5_groups,
};

const struct gpio_community *const alderlake_pch_h_communities[] = {
	&elkhartlake_community_0,
	&elkhartlake_community_1,
	&elkhartlake_community_2,
	&elkhartlake_community_3,
	&elkhartlake_community_4,
	&elkhartlake_community_5,
};

#endif