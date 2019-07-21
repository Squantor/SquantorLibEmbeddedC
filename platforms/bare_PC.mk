# platform settings for PC's with GCC and NO standard libraries
TOOLCHAIN_PREFIX =
C_SOURCES += 
CXX_SOURCES +=
S_SOURCES +=

# the bare pc target needs its own libc include path
ifdef LIBC_INC
INCLUDES += -I$(LIBC_INC)
else
$(error for the bare_PC the libc include path needs to be defined LIBC_INC)
endif
COMPILE_C_FLAGS += -nostdlib -fomit-frame-pointer -fno-stack-protector -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-unroll-loops -fmerge-all-constants -fno-ident -mfpmath=sse -mfancy-math-387 -ffunction-sections -fdata-sections 
COMPILE_CXX_FLAGS +=
COMPILE_ASM_FLAGS += -c -x assembler-with-cpp
ALIBS +=
LINK_FLAGS += -static -nostdlib -z norelro --hash-style=sysv --build-id=none --gc-sections -nolibc
LINK_FLAGS_RELEASE += -s