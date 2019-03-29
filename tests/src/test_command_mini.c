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
#include <sqMinUnitC.h>
#include <test_command_mini.h>
#include <command_mini.h>

const char testcmd1[] = "abc";
const char testcmd2[] = "def";

commandEntry_t testlist[] = {
    {testcmd1, NULL},
    {testcmd2, NULL},
    {NULL, NULL},
    };

static void testCommandMiniSetup(void) 
{
    
}

static void testCommandMiniTeardown(void) 
{

}

MU_TEST(testCommandMiniNormal) 
{
    // emit working command
    // checkout output
}

MU_TEST(testCommandMiniFail) 
{
    // emit not working command
    // checkout output
}

MU_TEST_SUITE(testCommandMini) 
{
    MU_SUITE_CONFIGURE(&testCommandMiniSetup, &testCommandMiniTeardown);
    MU_RUN_TEST(testCommandMiniNormal);
    MU_RUN_TEST(testCommandMiniFail);
}

void testCommandMiniSuite()
{
    MU_RUN_SUITE(testCommandMini);
}