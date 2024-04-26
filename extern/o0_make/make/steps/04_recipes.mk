################################################################################

.DEFAULT_GOAL := all

.PHONY: all
all: build ;

################################################################################

include $(O0_MAKE_DIR)make/target_toolchains/$(O0_BUILD_FRAMEWORK)/$(O0_BUILD_FRAMEWORK)_toolchain_recipes.mk
include $(O0_MAKE_DIR)make/common/common_recipes_$(O0_PRJ_TYPE).mk

################################################################################

O0_PRE_BUILD_INTERNAL_RECIPE ?= pre_build_internal_default
O0_POST_BUILD_INTERNAL_RECIPE ?= post_build_internal_default

O0_BUILD_TARGET_DEPS += $(O0_PRE_BUILD_RECIPE)
O0_BUILD_TARGET_DEPS += $(O0_PRE_BUILD_INTERNAL_RECIPE)
O0_BUILD_TARGET_DEPS += deps_to_link
O0_BUILD_TARGET_DEPS += deps_to_compile
O0_BUILD_TARGET_DEPS += $(O0_BUILD_OUTPUT_FILE)
O0_BUILD_TARGET_DEPS += post_build_size
O0_BUILD_TARGET_DEPS += post_build_objdump
O0_BUILD_TARGET_DEPS += $(O0_POST_BUILD_INTERNAL_RECIPE)
O0_BUILD_TARGET_DEPS += $(O0_POST_BUILD_RECIPE)

.PHONY: build ;
build: $(O0_BUILD_TARGET_DEPS)

################################################################################

.PHONY: pre_build_default
pre_build_default: ;

.PHONY: post_build_default
post_build_default: ;

.PHONY: pre_build_internal_default
pre_build_internal_default: ;

.PHONY: post_build_internal_default
post_build_internal_default: ;

################################################################################

.PHONY: deps_to_link
deps_to_link: FORCE
	$(foreach DEP,$(O0_DEPS_TO_LINK),$(MAKE) -C $(DEP) \
		O0_BUILD_MODE=$(O0_BUILD_MODE) \
		O0_TARGET_PLATFORM=$(O0_TARGET_PLATFORM) \
		O0_TARGET_PLATFORM_TYPE=$(O0_TARGET_PLATFORM_TYPE) \
		O0_BUILD_FRAMEWORK=$(O0_BUILD_FRAMEWORK) \
		O0_TARGET_OS=$(O0_TARGET_OS);)

.PHONY: deps_to_compile
deps_to_compile: FORCE
	$(foreach DEP,$(O0_DEPS_TO_COMPILE),$(MAKE) -C $(DEP) \
		O0_BUILD_MODE=$(O0_BUILD_MODE) \
		O0_TARGET_PLATFORM=$(O0_TARGET_PLATFORM) \
		O0_TARGET_PLATFORM_TYPE=$(O0_TARGET_PLATFORM_TYPE) \
		O0_BUILD_FRAMEWORK=$(O0_BUILD_FRAMEWORK) \
		O0_TARGET_OS=$(O0_TARGET_OS);)

################################################################################

.PHONY: compile
compile: $(O0_OBJ_FILES) ;

$(O0_BUILD_INTERMEDIATE_FILES_DIR)/%.o: %.$(O0_SRC_FILES_TYPE) | $(O0_BUILD_INTERMEDIATE_FILES_DIR)
	@$(O0_MKDIR) $(@D)
	@$(O0_ECHO_N) "Compiling File: $< ..."
	@$(O0_CC) $(O0_CFLAGS) -c $< -o $@
	@$(O0_ECHO) $(O0_COLOR_GREEN)"done."$(O0_COLOR_RESET)

################################################################################

-include $(O0_DEP_FILES)

################################################################################

$(O0_BUILD_DIR) $(O0_BUILD_INTERMEDIATE_FILES_DIR):
	@$(O0_ECHO) "Creating Directory: $@"
	@$(O0_MKDIR) $@

################################################################################

.PHONY: post_build_size
post_build_size: $(O0_SIZE_INFO_OUTPUT_FILE) ;

$(O0_SIZE_INFO_OUTPUT_FILE): $(O0_BUILD_OUTPUT_FILE)
	@$(O0_ECHO_N) "Creating size info file: $(O0_SIZE_INFO_OUTPUT_FILE) .."
	@$(O0_SIZE_INFO) $(O0_SIZE_INFO_FLAGS) > $(O0_SIZE_INFO_OUTPUT_FILE)
	@$(O0_ECHO) $(O0_COLOR_GREEN)"done."$(O0_COLOR_RESET)
	@$(O0_CAT) $(O0_SIZE_INFO_OUTPUT_FILE)

.PHONY: post_build_objdump
post_build_objdump: $(O0_OBJDUMP_OUTPUT_FILE) ;

$(O0_OBJDUMP_OUTPUT_FILE): $(O0_BUILD_OUTPUT_FILE)
	@$(O0_ECHO_N) "Creating objdump: $(O0_OBJDUMP_OUTPUT_FILE) .."
	@$(O0_OBJDUMP) $(O0_OBJDUMP_FLAGS) > $(O0_OBJDUMP_OUTPUT_FILE)
	@$(O0_ECHO) $(O0_COLOR_GREEN)"done."$(O0_COLOR_RESET)

################################################################################

.PHONY: clean
clean: tidy
	@$(O0_ECHO) "Removing Directory: $(O0_BUILD_DIR)"
	@$(O0_RM) $(O0_BUILD_DIR)

.PHONY: tidy
tidy:
	@$(O0_ECHO) "Removing Directory: $(O0_BUILD_INTERMEDIATE_FILES_DIR)"
	@$(O0_RM) $(O0_BUILD_INTERMEDIATE_FILES_DIR)

.PHONY: clean_all
clean_all:
	@$(O0_ECHO) "Removing Directory: $(O0_BUILD_DIR_ROOT)"
	@$(O0_RM) $(O0_BUILD_DIR_ROOT)

.PHONY: clean_deps
clean_deps:
	$(foreach DEP,$(O0_DEPS_TO_COMPILE),$(MAKE) clean -C $(DEP);)
	$(foreach DEP,$(O0_DEPS_TO_LINK),$(MAKE) clean -C $(DEP);)

################################################################################
FORCE:
################################################################################