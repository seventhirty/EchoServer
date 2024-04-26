################################################################################
# Replace "host" with the actual target platform name (linux, win64)
ifeq ($(O0_TARGET_PLATFORM), host)
  O0_TARGET_PLATFORM := $(O0_HOST_OS)
  O0_TARGET_OS := $(O0_HOST_OS)
endif

################################################################################

include $(O0_MAKE_DIR)make/target_toolchains/$(O0_BUILD_FRAMEWORK)/$(O0_BUILD_FRAMEWORK)_toolchain_setup.mk

################################################################################