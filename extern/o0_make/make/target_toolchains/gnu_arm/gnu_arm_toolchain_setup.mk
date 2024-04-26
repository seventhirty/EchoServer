O0_GNU_TOOLCHAIN_PREFIX := arm-none-eabi-
include $(O0_MAKE_DIR)make/target_toolchains/common/common_gnu_toolchain.mk
include $(O0_MAKE_DIR)make/target_toolchains/$(O0_BUILD_FRAMEWORK)/target_platforms/$(O0_TARGET_PLATFORM).mk

O0_FLASH := st-flash





O0_CFLAGS += -DSTM32F401xE

O0_LFLAGS += -TDevice/gcc.ld

# O0_CFLAGS += -DF_CPU=$(O0_TARGET_CPU_FREQUENCY_HZ) 
# O0_CFLAGS += -DBAUD=$(O0_MONITOR_BAUD_RATE_BPS) 
# O0_CFLAGS += -mmcu=$(O0_TARGET_MCU)
O0_CFLAGS  = -ggdb -O0
O0_CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork -Wl,--gc-sections
O0_CFLAGS += -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -std=gnu90 -ffunction-sections -fdata-sections



# DEFS = 

# CFLAGS  = -ggdb -O0
# CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork -Wl,--gc-sections
# CFLAGS += -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -std=gnu90 -ffunction-sections -fdata-sections

# WFLAGS += -Wall -Wextra -Warray-bounds -Wno-unused-parameter

# LFLAGS = -TDevice/gcc.ld


# -mcpu=cortex-m4 main.c -c
#arm-none-eabi-objcopy -O binary firmware.elf firmware.bin
#st-flash --reset write firmware.bin 0x8000000



# CFLAGS  ?=  -W -Wall -Wextra -Werror -Wundef -Wshadow -Wdouble-promotion \
#             -Wformat-truncation -fno-common -Wconversion \
#             -g3 -Os -ffunction-sections -fdata-sections -I. \
#             -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 $(EXTRA_CFLAGS)
# LDFLAGS ?= -Tlink.ld -nostartfiles -nostdlib --specs nano.specs -lc -lgcc -Wl,--gc-sections -Wl,-Map=$@.map
# SOURCES = main.c 

# build: firmware.elf

# firmware.elf: $(SOURCES)
# 	arm-none-eabi-gcc $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $@

# 	firmware.bin: firmware.elf
# 	arm-none-eabi-objcopy -O binary $< $@

# flash: firmware.bin
# 	st-flash --reset write $< 0x8000000