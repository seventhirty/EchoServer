################################################################################

SHELL := bash
.ONESHELL:
.SHELLFLAGS := -eu -o pipefail -c
.DELETE_ON_ERROR:
MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-builtin-rules
#MAKEFLAGS += --no-builtin-variables
#.SUFFIXES:

################################################################################

include $(O0_MAKE_DIR)make/steps/00_host_env_setup.mk
include $(O0_MAKE_DIR)make/steps/01_target_toolchain_setup.mk
include $(O0_MAKE_DIR)make/steps/02_prj_structure_setup.mk
include $(O0_MAKE_DIR)make/steps/03_flags.mk
include $(O0_MAKE_DIR)make/steps/04_recipes.mk

################################################################################