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

MU_TEST(testCmdPromptSingleCmdRetrieve) 
{
    
}

MU_TEST_SUITE(testCmdPrompt) 
{
    MU_SUITE_CONFIGURE(&testCmdPromptSetup, &testCmdPromptTeardown);
    MU_RUN_TEST(testCmdPromptEmpty);
    MU_RUN_TEST(testCmdPromptSingleCmdRetrieve);
}

void testCmdPromptSuite()
{
    MU_RUN_SUITE(testCmdPrompt);
}