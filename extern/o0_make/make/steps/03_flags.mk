################################################################################

include $(O0_MAKE_DIR)make/target_toolchains/$(O0_BUILD_FRAMEWORK)/$(O0_BUILD_FRAMEWORK)_toolchain_flags.mk

################################################################################

O0_CFLAGS += -std=$(O0_CFLAGS_STD_VERSION)
O0_CFLAGS += $(O0_CFLAGS_WARNING_FLAGS)
O0_CFLAGS += $(O0_CFLAGS_INTERMEDIATE_FILES_FLAGS)
O0_CFLAGS += $(O0_CFLAGS_OPTIMIZATION_FLAGS)
O0_CFLAGS += $(O0_CFLAGS_DEBUGGING_FLAGS)

O0_CFLAGS += -DO0_TARGET_PLATFORM_$(shell echo $(O0_TARGET_PLATFORM) | tr '[:lower:]' '[:upper:]')
O0_CFLAGS += -DO0_TARGET_PLATFORM_TYPE_$(shell echo $(O0_TARGET_PLATFORM_TYPE) | tr '[:lower:]' '[:upper:]')
O0_CFLAGS += -DO0_BUILD_FRAMEWORK_$(shell echo $(O0_BUILD_FRAMEWORK) | tr '[:lower:]' '[:upper:]')
O0_CFLAGS += -DO0_BUILD_MODE_$(shell echo $(O0_BUILD_MODE) | tr '[:lower:]' '[:upper:]')

ifeq ($(O0_BUILD_MODE), debug)
  O0_CFLAGS += -DDEBUG
else
  O0_CFLAGS += -DNDEBUG
endif

O0_CFLAGS += -MP -MD $(foreach DIR, $(O0_INCLUDE_DIRS), -I$(DIR))

################################################################################

O0_LDFLAGS += $(O0_LDFLAGS_OPTIMIZATION_FLAGS)
O0_LDFLAGS += $(O0_CFLAGS_DEBUGGING_FLAGS)
#O0_LDFLAGS += -std=$(O0_CFLAGS_STD_VERSION)

################################################################################

O0_SIZE_INFO_OUTPUT_FILE ?= $(O0_BUILD_INTERMEDIATE_FILES_DIR)/$(O0_PRJ_NAME)_size.txt
O0_SIZE_INFO_FLAGS += $(O0_BUILD_OUTPUT_FILE)

################################################################################

O0_OBJDUMP_OUTPUT_FILE ?= $(O0_BUILD_INTERMEDIATE_FILES_DIR)/$(O0_PRJ_NAME).lss
O0_OBJDUMP_FLAGS ?= -h -S $(O0_BUILD_OUTPUT_FILE)

################################################################################