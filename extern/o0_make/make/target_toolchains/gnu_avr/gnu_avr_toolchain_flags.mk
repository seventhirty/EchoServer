################################################################################

O0_CFLAGS += -DF_CPU=$(O0_TARGET_CPU_FREQUENCY_HZ) 
O0_CFLAGS += -DBAUD=$(O0_MONITOR_BAUD_RATE_BPS) 
O0_CFLAGS += -mmcu=$(O0_TARGET_MCU)
O0_CFLAGS += -fno-exceptions
O0_CFLAGS += -fno-rtti

################################################################################

O0_LDFLAGS += -mmcu=$(O0_TARGET_MCU)

################################################################################

O0_SIZE_INFO_FLAGS += --mcu=$(O0_TARGET_MCU)
O0_SIZE_INFO_FLAGS += --format=avr

################################################################################

O0_OBJCOPY_FLAGS_OUTPUT_TARGET_BFD_NAME ?= ihex
O0_OBJCOPY_FLAGS_SECTION ?= -R .eeprom

O0_OBJCOPY_FLAGS += $(O0_OBJCOPY_FLAGS_SECTION)
O0_OBJCOPY_FLAGS += -O $(O0_OBJCOPY_FLAGS_OUTPUT_TARGET_BFD_NAME)
O0_OBJCOPY_FLAGS += -v

################################################################################

O0_FLASH_FLAGS += -c $(O0_FLASH_FLAGS_PROGRAMMER_TYPE)
O0_FLASH_FLAGS += -p $(O0_TARGET_MCU)
O0_FLASH_FLAGS += -b $(O0_FLASH_FLAGS_BAUD_RATE_BPS)
O0_FLASH_FLAGS += -P $(O0_TARGET_HOST_PORT)
O0_FLASH_FLAGS += -U flash:w:$(O0_POST_BUILD_OUTPUT_FILE)

################################################################################

-include $(O0_MAKE_DIR)make/target_toolchains/$(O0_BUILD_FRAMEWORK)/target_platforms/$(O0_TARGET_PLATFORM)_toolchain_flags.mk

################################################################################

O0_RUN_TARGET_CMD = $(O0_FLASH) $(O0_FLASH_FLAGS)

################################################################################