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
#include <string.h>
#include <sqMinUnitC.h>
#include <test_cmdprompt.h>
#include <cmdline_prompt.h>
#include <mock_datastreamchar.h>

char testCmdPromptStringBuffer[128];
t_queueString testCmdPromptStringQueue = {
    .len = 128-1,
    .head = 0,
    .tail = 0,
    .data = testCmdPromptStringBuffer,
    };

result testCmdlineParse(char *cmdline)
{
    return noError;
}

int testCmdPromptLoop(int timeout)
{
    int counts = timeout;
    result r;
    do {
        r = cmdlinePromptProcess(&testDsChar, testCmdlineParse);
        counts--;
    } while(r == noError && (counts > 0));
    return counts;
}

static void testCmdPromptSetup(void) 
{
    mockDsCharReset();
    testCmdPromptStringQueue.head = 0;
    testCmdPromptStringQueue.tail = 0;
    cmdlinePromptInit(&testCmdPromptStringQueue);
}

static void testCmdPromptTeardown(void) 
{

}

MU_TEST(testCmdPromptEmpty) 
{
    mu_check(testCmdPromptLoop(10) == 9);
}

// check if prompt echo works
MU_TEST(testCmdPromptCmdlineEcho) 
{
    char testcmd[] = "foo";
    char testoutput[3] = "baz";
    mockDsPutReadsString(testcmd);
    mu_check(testCmdPromptLoop(10) == 6);
    mu_check(mockDsGetWrites(testoutput, sizeof(testoutput)) == noError);
    mu_check(memcmp(testcmd, testoutput, 3) == 0);
}
// check line editing
MU_TEST(testCmdPromptCmdLineEdit)
{
    char testcmd[] = "fa\booo\b";
    char testcmdexpect[11] = "fa\b \booo\b \b";
    char testcmdout[11];
    mockDsPutReadsString(testcmd);
    mu_check(testCmdPromptLoop(10) == 2);
    mu_check(mockDsGetWrites(testcmdout, sizeof(testcmdout)) == noError);
    mu_check(memcmp(testcmdout, testcmdexpect, 11) == 0);    
}

// check if the command interpreter gets called
MU_TEST(testCmdPromptCmdlineInput) 
{
    
}

// see if we can get previous command
MU_TEST(testCmdPromptCmdlineRetrieve) 
{
    
}

MU_TEST_SUITE(testCmdPrompt) 
{
    MU_SUITE_CONFIGURE(&testCmdPromptSetup, &testCmdPromptTeardown);
    MU_RUN_TEST(testCmdPromptEmpty);
    MU_RUN_TEST(testCmdPromptCmdlineEcho);
    MU_RUN_TEST(testCmdPromptCmdLineEdit);
    MU_RUN_TEST(testCmdPromptCmdlineInput);
    // line editing, check handler for correctness
    // input unhandled escape, should be empty
    // input previous command request, should be empty
    MU_RUN_TEST(testCmdPromptCmdlineRetrieve);
    // see if we can fill buffer with commands and get last few commands
}

void testCmdPromptSuite()
{
    MU_RUN_SUITE(testCmdPrompt);
}