################################################################################

# O0_PRJ_TYPE possible values: app, lib
O0_PRJ_TYPE ?= app

# O0_BUILD_MODE possible values: debug, release, final
O0_BUILD_MODE ?= debug

# O0_TARGET_PLATFORM possible values: host, linux, win32, win64, macos, 
# arduino_uno_r3, stm32_f401, stm32_f103c8, nucleo_f401re 
O0_TARGET_PLATFORM ?= host

# O0_TARGET_PLATFORM_TYPE possible values: desktop, mcu
# if empty, depends on O0_TARGET_PLATFORM (auto-detected)
O0_TARGET_PLATFORM_TYPE ?=

# O0_BUILD_FRAMEWORK possible values: gnu_desktop, gnu_avr, gnu_arm
O0_BUILD_FRAMEWORK ?= gnu_desktop

# By default, assume makefile was started from the main directory
O0_PRJ_DIR ?= .

# By default, the name of the project corresponds to the main project dir's name
O0_PRJ_NAME ?= $(notdir $(shell pwd))

# By defailt, we use c, but cpp is also supported (not mixing yet though)
O0_SRC_FILES_TYPE ?= c

# External dependencies that adhere to o0 project conventions
O0_DEPS_TO_COMPILE ?=
O0_DEPS_TO_LINK ?=

# Other external dependencies
O0_ADDITIONAL_SRC_DIRS ?=
O0_ADDITIONAL_INCLIDE_DIRS ?=
O0_ADDITIONAL_LIB_FILES ?=

# Custom pre- and post-build recipes
O0_PRE_BUILD_RECIPE ?= pre_build_default
O0_POST_BUILD_RECIPE ?= post_build_default

# Build flags
O0_CFLAGS_STD_VERSION ?= gnu99
O0_CFLAGS_WARNING_FLAGS ?= -Wall -Wextra -Wpedantic# -Werror

O0_CFLAGS_INTERMEDIATE_FILES_FLAGS ?= -save-temps=obj
O0_CFLAGS_OPTIMIZATION_FLAGS ?= -Os -flto -ffunction-sections -fdata-sections
O0_CFLAGS_DEBUGGING_FLAGS ?= -g

O0_LDFLAGS_OPTIMIZATION_FLAGS ?= -Os -flto -Wl,--gc-sections

# Run flags
O0_RUN_TARGET_CMD_FLAGS ?=

################################################################################
# Desktop-specific

# O0_TARGET_OS will be automatically set if O0_TARGET_PLATFORM is "host" (which 
# is the default)
O0_TARGET_OS ?=

################################################################################
# MCU-specific

O0_TARGET_CPU_FREQUENCY_HZ ?= 16000000UL
O0_MONITOR_BAUD_RATE_BPS ?= 9600
O0_TARGET_HOST_PORT ?= /dev/ttyACM0

O0_HOST_SERIAL_MONITOR ?= gtkterm
O0_HOST_SERIAL_MONITOR_FLAGS ?= -p $(O0_TARGET_HOST_PORT) -s $(O0_MONITOR_BAUD_RATE_BPS)

################################################################################

O0_MAKE_DIR := $(dir $(lastword $(MAKEFILE_LIST)))/../
include $(O0_MAKE_DIR)make/o0_make_internal.mk

################################################################################