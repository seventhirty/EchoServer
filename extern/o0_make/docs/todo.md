- C++ support
- link libraries
- proper intermediate dirs for extern src

* check intermediate dirs when using deps
* test additional extern deps (+ interm dirs)

* O0_CFLAGS_WARNING_FLAGS ?= -w -Werror -Wall -pedantic-errors -Wshadow -Wextra
* other uart flags -> macros: HOST_SERIAL_MONITOR_BITS_COUNT..
* FORCE needed?

* test monitor
* desktop debug

* error output on invalid input (ex.: using "gnu_desktop" with an "mcu" target)

* cpp; mixing c and cpp

* test, check
* install
* lint, analysis
* gen_doc
* help, 

* docs, comments, intro and instructions (must be called from main prj makefile or with -C (check!))

* avr: simulator
* avr: debug simulator

* arm - nucleo
* arm - blue pill, black pill

* esp32 idf

# https://www.nongnu.org/avr-libc/user-manual/overview.html

# avrusb: AVR USB
# AVaRICE is a back-end program to AVR GDB and interfaces to the Atmel JTAG In-Circuit Emulator (ICE), to provide emulation capabilities.
# freeice: Free AVR ICE / GDB-Serializer
# avr-run*
# simavr
# simulavr: # SimulAVR is an AVR simulator used as a back-end with AVR GDB.
# uisp: AVR In-System Programmer
# MFile - simple Makefile generator
# avr-insight Insight is GDB plus a GUI written in Tcl/Tk
# SRecord is a collection of powerful tools for manipulating EPROM load files. 


