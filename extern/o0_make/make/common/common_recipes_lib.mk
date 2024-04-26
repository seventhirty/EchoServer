################################################################################

$(O0_BUILD_OUTPUT_FILE): $(O0_OBJ_FILES) | $(O0_BUILD_DIR)
	@$(O0_ECHO) "Building static lib.."
	@$(O0_AR) -r $@ $^
	@$(O0_ECHO) $(O0_COLOR_GREEN)"Building static lib finished succesfully."$(O0_COLOR_RESET)

.PHONY: build_static_lib
build_static_lib: compile ;

################################################################################