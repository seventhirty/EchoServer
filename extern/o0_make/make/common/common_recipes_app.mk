################################################################################

$(O0_BUILD_OUTPUT_FILE): $(O0_OBJ_FILES) | $(O0_BUILD_DIR)
	@$(O0_ECHO) "Linking.."
	@$(O0_LD) $(O0_LDFLAGS) -o $@ $^ $(O0_LIB_FILES_TO_LINK)
	@$(O0_ECHO) $(O0_COLOR_GREEN)"Linking finished succesfully."$(O0_COLOR_RESET)

.PHONY: link
link: compile ;

################################################################################

.PHONY: run
run: build
	@$(O0_ECHO) "Running target:"
	$(O0_RUN_TARGET_CMD)

.PHONY: monitor
monitor: run
	@$(O0_ECHO) "Running monitor:"
	$(O0_HOST_SERIAL_MONITOR) $(O0_HOST_SERIAL_MONITOR_FLAGS)

# .PHONY: debug
# debug: build
# 	$(O0_DEBUG_TARGET_CMD)

# debug_with_monitor ?

################################################################################