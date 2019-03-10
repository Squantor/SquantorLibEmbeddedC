# project settings
BIN_NAME = sqlibembeddedC_tests
C_SOURCES += src/sqlibembeddedc_tests.c \
src/test_parse_ansi.c
CXX_SOURCES +=
S_SOURCES +=
INCLUDES = -Iinc -I../inc
COMPILE_C_FLAGS += -std=gnu11 -Wall -Wextra
COMPILE_CXX_FLAGS += -std=c++17 -Wall -Wextra
COMPILE_ASM_FLAGS += -c -x assembler-with-cpp
LINK_FLAGS +=
RLIBDIR = -L"../bin/$(PLATFORM)/release"
RLIBS = -lsqlibembeddedc
DLIBDIR = -L"../bin/$(PLATFORM)/debug"
DLIBS = -lsqlibembeddedc
