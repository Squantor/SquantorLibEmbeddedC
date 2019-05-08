/*
MIT License

Copyright (c) 2019 Bart Bilos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
/*
*/
#include <rt0/syscall.h>
#include <test_parse_ansi.h>
#include <test_queue_string.h>
#include <test_cmdprompt.h>
#include <test_queue.h>
#include <test_dsputs.h>
#include <test_command_mini.h>
#include <test_prompt_mini.h>
#include <test_print.h>
#include <test_dswrite.h>
#include <test_dsread.h>
#include <test_parse.h>

int minunitRun; /* tests run */
int minunitFailures; /* tests failed */
int minunitAsserts; /* asserts run */

int sysWrite( int f, const char* d, int l )
{
   int ret = syscall3( SYS_write, f, ( long )( d ), l );

   return( ret );
}

int str_len( const char *string )
{
   int length = 0;
   while( *string ) { string++; length++; }
   return( length );
}

void println( const char* string )
{
   sysWrite( 1, string, str_len( string ) );
   sysWrite( 1, "\n", 1 );
}

int main() 
{
    // sort test modules on dependencies
    testParseAnsiSuite();
    testQueueSuite();
    testQueueStringSuite();
    testDsReadSuite();
    testDsWriteSuite();
    testdsPutsSuite();
    testCmdPromptSuite();
    testPromptMiniSuite();
    testCommandMiniSuite();
    testPrintSuite();
    testParseSuite();
    if(minunitFailures != 0)
        println("Test failures occured!");
    else
        println("All tests passed.");
    return 0;
}
