################################################################################

O0_GNU_TOOLCHAIN_PREFIX := avr-
include $(O0_MAKE_DIR)make/target_toolchains/common/common_gnu_toolchain.mk

################################################################################

O0_FLASH := avrdude
O0_TARGET_PLATFORM_TYPE := mcu
O0_LD_OUTPUT_FILE_EXTENSION ?= .elf

################################################################################

-include $(O0_MAKE_DIR)make/target_toolchains/$(O0_BUILD_FRAMEWORK)/target_platforms/$(O0_TARGET_PLATFORM)_toolchain_setup.mk

################################################################################


