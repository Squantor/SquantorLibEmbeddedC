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
#include <string.h>

const char testcmd1[] = "abc";
const char testcmd2[] = "def";

int handleCmd1Count;
int handleCmd2Count;
char handleCmd1Arg[16];
char handleCmd2Arg[16];

result testHandleCmd1(const char *argument)
{
    handleCmd1Count++;
    if(argument != NULL)
        strncpy(handleCmd1Arg, argument, sizeof(handleCmd1Arg));
    return noError;
}

result testHandleCmd2(const char *argument)
{
    handleCmd2Count++;
    if(argument != NULL)
        strncpy(handleCmd2Arg, argument, sizeof(handleCmd2Arg));
    return resultEnd;
}

commandEntry_t testlist[] = {
    {testcmd1, testHandleCmd1},
    {testcmd2, testHandleCmd2},
    {NULL, NULL},
    };

static void testCommandMiniSetup(void) 
{
    handleCmd1Count = 0;
    handleCmd2Count = 0;
    memset(handleCmd1Arg, 0, sizeof(handleCmd1Arg));
    memset(handleCmd2Arg, 0, sizeof(handleCmd2Arg));
}

static void testCommandMiniTeardown(void) 
{
    
}

MU_TEST(testCommandMiniNormal)
{
    mu_check(commandInterpret(testlist, "abc") == noError);
    mu_check(handleCmd1Count == 1);
    mu_check(commandInterpret(testlist, "def") == resultEnd);
    mu_check(handleCmd2Count == 1);
}

MU_TEST(testCommandMiniNormalArg)
{
    mu_check(commandInterpret(testlist, "abc 123") == noError);
    mu_check(handleCmd1Count == 1); 
    mu_check(strncmp(handleCmd1Arg, "123", sizeof(handleCmd1Arg)) == 0);
    mu_check(commandInterpret(testlist, "def 0x1234") == resultEnd);
    mu_check(handleCmd2Count == 1); 
    mu_check(strncmp(handleCmd2Arg, "0x1234", sizeof(handleCmd2Arg)) == 0);
}

MU_TEST(testCommandMiniFail) 
{
    mu_check(commandInterpret(testlist, "ghi") == commandNotFound);
    mu_check(handleCmd1Count == 0);
    mu_check(handleCmd2Count == 0);
}

MU_TEST_SUITE(testCommandMini) 
{
    MU_SUITE_CONFIGURE(&testCommandMiniSetup, &testCommandMiniTeardown);
    MU_RUN_TEST(testCommandMiniNormal);
    MU_RUN_TEST(testCommandMiniNormalArg);
    MU_RUN_TEST(testCommandMiniFail);
}

void testCommandMiniSuite()
{
    MU_RUN_SUITE(testCommandMini);
}