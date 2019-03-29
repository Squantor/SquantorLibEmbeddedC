# project settings
BIN_NAME = libsqlibembeddedc
C_SOURCES = src/ansi/parse_ansi.c \
src/queue/queue_string.c \
src/queue/queue_char.c src/queue/queue_uint8.c \
src/cmdline/cmdline_prompt.c src/prompt/prompt_mini.c \
src/command/command_mini.c \
src/datastream/dswritechar.c src/datastream/dsreadchar.c \
src/datastream/dsputs.c
INCLUDES = -Iinc -Iinc_internal
COMPILE_C_FLAGS += -std=gnu11 -Wall -Wextra -Werror -Wno-main -fno-common -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections 
COMPILE_CXX_FLAGS += -std=c++17 -Wall -Wextra -Werror -Wno-main -fno-common -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions 
COMPILE_ASM_FLAGS += -c -x assembler-with-cpp
LINK_FLAGS += -flto -nostdlib -Xlinker --gc-sections -Xlinker -print-memory-usage
