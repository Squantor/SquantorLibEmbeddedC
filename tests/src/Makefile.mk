# project settings
BIN_NAME = sqlibembeddedC_tests
C_SOURCES += src/sqlibembeddedc_tests.c \
src/mock_datastreamchar.c \
src/test_parse_ansi.c src/test_queue_string.c \
src/test_cmdprompt.c src/test_prompt_mini.c \
src/test_command_mini.c \
src/test_dswrite.c src/test_dsread.c \
src/test_queue_char.c \
src/test_dsputs.c \
src/test_print.c
CXX_SOURCES +=
S_SOURCES +=
INCLUDES = -Iinc -I../inc -IsquantorLibC/inc
COMPILE_C_FLAGS += -std=gnu11 -Wall -Wextra
COMPILE_CXX_FLAGS += -std=c++17 -Wall -Wextra
COMPILE_ASM_FLAGS += -c -x assembler-with-cpp
LINK_FLAGS +=
LIBS += -lsqlibembeddedc -lsqlibc
RLIBDIR = -L"../bin/$(PLATFORM)/release" -L"squantorLibC/bin/$(PLATFORM)/release"
RLIBS = 
DLIBDIR = -L"../bin/$(PLATFORM)/debug" -L"squantorLibC/bin/$(PLATFORM)/debug"
DLIBS =
