# platform settings for cortex M0
TOOLCHAIN_PREFIX = arm-none-eabi-

# the cortex M0 platform needs its own libc include path
ifdef LIBC_INC
INCLUDES += -I$(LIBC_INC)
else
$(error for the bare_PC the libc include path needs to be defined LIBC_INC)
endif

COMPILE_C_FLAGS += -mcpu=cortex-m0 -mthumb
COMPILE_CXX_FLAGS += -mcpu=cortex-m0 -mthumb
COMPILE_ASM_FLAGS += -mcpu=cortex-m0 -mthumb
DEFINES += -DCORE_M0