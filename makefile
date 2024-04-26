O0_BUILD_MODE ?= debug
O0_TARGET_PLATFORM ?= linux
O0_BUILD_FRAMEWORK ?= gnu_desktop

# Build flags
O0_SRC_FILES_TYPE = cpp
O0_CFLAGS_STD_VERSION ?= c++17

include ./extern/o0_make/include/o0_make.mk