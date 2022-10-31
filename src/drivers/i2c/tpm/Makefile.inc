ifeq ($(CONFIG_TPM)$(CONFIG_I2C_TPM),yy)

all-$(CONFIG_DRIVER_TIS_DEFAULT) += tis.c
all-$(CONFIG_TPM_ATMEL) += tis_atmel.c
all-$(CONFIG_TPM_GOOGLE) += cr50.c
all-y += tpm.c

endif

ramstage-$(CONFIG_DRIVER_I2C_TPM_ACPI) += chip.c
