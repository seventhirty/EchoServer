################################################################################

-include $(O0_MAKE_DIR)make/target_toolchains/$(O0_BUILD_FRAMEWORK)/target_platforms/$(O0_TARGET_PLATFORM)_toolchain_recipes.mk

################################################################################

O0_POST_BUILD_INTERNAL_RECIPE := post_build
O0_POST_BUILD_OUTPUT_FILE := $(O0_BUILD_DIR)/$(O0_PRJ_NAME).hex

.PHONY: post_build
post_build: $(O0_POST_BUILD_OUTPUT_FILE) ;

$(O0_POST_BUILD_OUTPUT_FILE): $(O0_BUILD_OUTPUT_FILE)
	@$(O0_ECHO) "Post-Build.."
	@$(O0_ECHO) "Creating file: $@"
	$(O0_OBJCOPY) $(O0_BUILD_OUTPUT_FILE) $@
	@$(O0_ECHO) $(O0_COLOR_GREEN)"Post-Build finished succesfully."$(O0_COLOR_RESET)

################################################################################
