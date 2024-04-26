################################################################################

ifeq ($(OS),Windows_NT)
  ifeq ($(win32),1)
    O0_HOST_OS := win32
  else
    O0_HOST_OS := win64
  endif
else ifeq ($(shell uname -s),Darwin)
  O0_HOST_OS := macos
else ifeq ($(shell uname -s),Linux)
  O0_HOST_OS := linux
else
  $(error o0_Make: host OS not recognized.)
endif

################################################################################

O0_RM ?= rm -rf
O0_MKDIR = mkdir -p
O0_ECHO_N := echo -ne
O0_ECHO := echo -e
O0_CAT := cat

################################################################################

O0_COLOR_RESET  := '\033[0m'
O0_COLOR_BLACK  := '\033[0;30m'
O0_COLOR_RED    := '\033[0;31m'
O0_COLOR_GREEN  := '\033[0;32m'
O0_COLOR_YELLOW := '\033[0;33m'
O0_COLOR_BLUE   := '\033[0;34m'
O0_COLOR_PURPLE := '\033[0;35m'
O0_COLOR_CYAN   := '\033[0;36m'
O0_COLOR_WHITE  := '\033[0;37m'

################################################################################