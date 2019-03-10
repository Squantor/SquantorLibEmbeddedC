# platform settings for cortex M0
TOOLCHAIN_PREFIX = arm-none-eabi-
COMPILE_C_FLAGS += -mcpu=cortex-m0 -mthumb
COMPILE_CXX_FLAGS += -mcpu=cortex-m0 -mthumb
COMPILE_ASM_FLAGS += -mcpu=cortex-m0 -mthumb
DEFINES += -DCORE_M0