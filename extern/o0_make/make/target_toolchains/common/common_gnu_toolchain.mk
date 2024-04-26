# C Compiler (and more..)
ifeq ($(O0_SRC_FILES_TYPE),cpp)
	O0_CC := $(O0_GNU_TOOLCHAIN_PREFIX)g++
else
	O0_CC := $(O0_GNU_TOOLCHAIN_PREFIX)gcc
endif

# C++ Compiler (and more..)
O0_CXX := $(O0_GNU_TOOLCHAIN_PREFIX)g++

# GNU Linker - ld, but use CC for linking
#O0_LD := $(O0_GNU_TOOLCHAIN_PREFIX)ld
O0_LD := $(O0_CC)

# Create, modify, and extract from archives
O0_AR := $(O0_GNU_TOOLCHAIN_PREFIX)ar

# GNU assembler.
O0_AS := $(O0_GNU_TOOLCHAIN_PREFIX)as

# Copy and translate object files
O0_OBJCOPY := $(O0_GNU_TOOLCHAIN_PREFIX)objcopy

# Display information from object files
O0_OBJDUMP := $(O0_GNU_TOOLCHAIN_PREFIX)objdump

# List section sizes and total size of binary files
O0_SIZE_INFO := $(O0_GNU_TOOLCHAIN_PREFIX)size

# GNU Debugger
O0_DEBUGGER := $(O0_GNU_TOOLCHAIN_PREFIX)gdb

# Add index files to speed up GDB
O0_DEBUGGER_ADD_INDEX := $(O0_GNU_TOOLCHAIN_PREFIX)gdb-add-index

# Generate index to archive (library) contents.
O0_RANLIB := $(O0_GNU_TOOLCHAIN_PREFIX)ranlib

# List symbols from object files.
O0_NM := $(O0_GNU_TOOLCHAIN_PREFIX)nm

# List printable strings from files.
O0_STRINGS := $(O0_GNU_TOOLCHAIN_PREFIX)strings

# Discard symbols.
O0_STRIP := $(O0_GNU_TOOLCHAIN_PREFIX)strip

# Display the contents of ELF format files.
O0_READELF := $(O0_GNU_TOOLCHAIN_PREFIX)readelf

# Filter to demangle encoded C++ symbols.
O0_CPP_FILT := $(O0_GNU_TOOLCHAIN_PREFIX)c++filt

# Convert addresses to file and line.
O0_ADDR2LINE := $(O0_GNU_TOOLCHAIN_PREFIX)addr2line

# update ELF header and program property of ELF files
O0_ELF_EDIT := $(O0_GNU_TOOLCHAIN_PREFIX)elfedit

# The C Preprocessor
O0_PREPROC := $(O0_GNU_TOOLCHAIN_PREFIX)cpp

# Print code coverage information.
O0_GCOV := $(O0_GNU_TOOLCHAIN_PREFIX)gcov

# Offline tool to handle gcda counts
O0_GCOV_TOOL := $(O0_GNU_TOOLCHAIN_PREFIX)gcov-tool

# Display call graph profile data
O0_GPROF := $(O0_GNU_TOOLCHAIN_PREFIX)gprof

# Link, providing a custom BFD (Binary File Descriptor) library
O0_LD_BFD := $(O0_GNU_TOOLCHAIN_PREFIX)ld.bfd