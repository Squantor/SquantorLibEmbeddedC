# MIT License

# Copyright (c) 2020 Bart Bilos

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# squantorLibEmbeddedC library files
#
# Version: 20200427

# library files and includes
FILES += squantorLibEmbeddedC/src/ansi/parse_ansi.c \
squantorLibEmbeddedC/src/queue/queue_string.c \
squantorLibEmbeddedC/src/queue/queue_char.c \
squantorLibEmbeddedC/src/queue/queue_uint8.c \
squantorLibEmbeddedC/src/cmdline/cmdline_prompt.c \
squantorLibEmbeddedC/src/prompt/prompt_mini.c \
squantorLibEmbeddedC/src/command/command_mini.c \
squantorLibEmbeddedC/src/datastream/dswritechar.c \
squantorLibEmbeddedC/src/datastream/dsreadchar.c \
squantorLibEmbeddedC/src/datastream/dsputs.c \
squantorLibEmbeddedC/src/print/print_digit.c \
squantorLibEmbeddedC/src/print/print_hex_u8.c \
squantorLibEmbeddedC/src/print/print_hex_u16.c \
squantorLibEmbeddedC/src/print/print_hex_u32.c \
squantorLibEmbeddedC/src/print/print_dec_u16.c \
squantorLibEmbeddedC/src/print/print_decnz_u16.c \
squantorLibEmbeddedC/src/print/print_dec_u32.c \
squantorLibEmbeddedC/src/print/print_bin_u32.c \
squantorLibEmbeddedC/src/parse/parsedigit.c

INCLUDES += -IsquantorLibEmbeddedC/inc -IsquantorLibEmbeddedC/inc_internal


