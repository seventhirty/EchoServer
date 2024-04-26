################################################################################

O0_BUILD_ROOT_DIR_NAME_APP ?= build
O0_BUILD_ROOT_DIR_NAME_LIB ?= lib

ifeq ($(O0_PRJ_TYPE), app)
  O0_BUILD_ROOT_DIR_NAME = $(O0_BUILD_ROOT_DIR_NAME_APP)
else
  O0_BUILD_ROOT_DIR_NAME = $(O0_BUILD_ROOT_DIR_NAME_LIB)
endif

O0_INCLUDE_DIR_NAME ?= include
O0_SRC_DIR_NAME ?= src

################################################################################

O0_INCLUDE_DIRS += $(O0_PRJ_DIR)/$(O0_INCLUDE_DIR_NAME)
O0_INCLUDE_DIRS += $(foreach LIB, $(O0_DEPS_TO_COMPILE), $(LIB)/$(O0_INCLUDE_DIR_NAME))
O0_INCLUDE_DIRS += $(foreach LIB, $(O0_DEPS_TO_LINK), $(LIB)/$(O0_INCLUDE_DIR_NAME))
O0_INCLUDE_DIRS += $(O0_ADDITIONAL_INCLIDE_DIRS)

O0_SRC_DIRS += $(O0_PRJ_DIR)/$(O0_SRC_DIR_NAME)
O0_SRC_DIRS += $(foreach LIB, $(O0_DEPS_TO_COMPILE), $(LIB)/$(O0_SRC_DIR_NAME))
O0_SRC_DIRS += $(O0_ADDITIONAL_SRC_DIRS)

O0_LIB_FILES_TO_LINK += $(foreach LIB, $(O0_DEPS_TO_LINK), $(LIB)/$(O0_BUILD_ROOT_DIR_NAME_LIB)/$(O0_TARGET_PLATFORM)/$(O0_BUILD_MODE)/lib$(notdir $(LIB)).a)
O0_LIB_FILES_TO_LINK += $(O0_ADDITIONAL_LIB_FILES)



O0_SRC_FILES := $(foreach DIR,$(O0_SRC_DIRS),$(shell find $(DIR) -name '*.$(O0_SRC_FILES_TYPE)'))

################################################################################

$(info $$O0_LIB_FILES_TO_LINK is [${O0_LIB_FILES_TO_LINK}])
$(info $$O0_SRC_DIRS is [${O0_SRC_DIRS}])
$(info $$O0_SRC_FILES is [${O0_SRC_FILES}])
$(info $$O0_INCLUDE_DIRS is [${O0_INCLUDE_DIRS}])

################################################################################

O0_BUILD_DIR_ROOT := $(O0_PRJ_DIR)/$(O0_BUILD_ROOT_DIR_NAME)
O0_BUILD_DIR := $(O0_BUILD_DIR_ROOT)/$(O0_TARGET_PLATFORM)/$(O0_BUILD_MODE)
O0_BUILD_INTERMEDIATE_FILES_DIR := $(O0_BUILD_DIR)_intermediate



O0_DEP_FILES := $(patsubst %.$(O0_SRC_FILES_TYPE), $(O0_BUILD_INTERMEDIATE_FILES_DIR)/%.d, $(O0_SRC_FILES))
O0_OBJ_FILES := $(patsubst %.$(O0_SRC_FILES_TYPE), $(O0_BUILD_INTERMEDIATE_FILES_DIR)/%.o, $(O0_SRC_FILES))

################################################################################

ifeq ($(O0_PRJ_TYPE), app)
  O0_BUILD_OUTPUT_FILE = $(O0_BUILD_DIR)/$(O0_PRJ_NAME)$(O0_LD_OUTPUT_FILE_EXTENSION)
  O0_RUN_TARGET_CMD = $(O0_BUILD_OUTPUT_FILE) $(O0_RUN_TARGET_CMD_FLAGS)
else
  O0_BUILD_OUTPUT_FILE = $(O0_BUILD_DIR)/lib$(O0_PRJ_NAME).a
endif

################################################################################