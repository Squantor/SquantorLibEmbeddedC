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
    .len = sizeof(testCmdPromptStringBuffer)-1,
    .head = 0,
    .tail = 0,
    .data = testCmdPromptStringBuffer,
    };

char testCmdlineParseString[128];
int testCmdlineParseCallCnt = 0;

result testCmdlineParse(char *cmdline)
{
    strncpy(testCmdlineParseString, cmdline, sizeof(testCmdlineParseString));
    testCmdlineParseCallCnt++;
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
    testCmdlineParseCallCnt = 0;
    memset(testCmdPromptStringBuffer, 0, sizeof(testCmdPromptStringBuffer));
    memset(testCmdlineParseString, 0, sizeof(testCmdlineParseString));
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
    char testcmd[] = "foo\r";
    char testcmdcall[] = "foo";
    char testcmdoutput[] = "foo\r";
    char testcmdout[11];
    mockDsPutReadsString(testcmd);
    mu_check(testCmdPromptLoop(10) == 5);
    mu_check(mockDsGetWrites(testcmdout, 4) == noError);
    mu_check(memcmp(testcmdout, testcmdoutput, 4) == 0); 
    mu_check(testCmdlineParseCallCnt == 1);
    mu_check(strncmp(testcmdcall, testCmdlineParseString, sizeof(testcmdcall)) == 0);
}

// input unhandled escape, should be empty
MU_TEST(testCmdPromptCmdlineBadEsc)
{
    char testcmd[] = "\e_";
    char testcmdout[11];
    mockDsPutReadsString(testcmd);
    mu_check(testCmdPromptLoop(10) == 7);
    mu_check(mockDsGetWrites(testcmdout, 1) == queueEmpty);
}

// input previous command request, should be empty
MU_TEST(testCmdPromptPreviousEmpty) 
{
    
}

// check if the command interpreter gets edited line
MU_TEST(testCmdPromptCmdlineEditInput) 
{
    char testcmd[] = "fa\booo\b\r";
    char testcmdcall[] = "foo";
    char testcmdoutput[] = "fa\b \booo\b \b\r";
    char testcmdout[15];
    mockDsPutReadsString(testcmd);
    mu_check(testCmdPromptLoop(10) == 1);
    mu_check(mockDsGetWrites(testcmdout, 12) == noError);
    mu_check(memcmp(testcmdout, testcmdoutput, 12) == 0); 
    mu_check(testCmdlineParseCallCnt == 1);
    mu_check(strncmp(testcmdcall, testCmdlineParseString, sizeof(testcmdcall)) == 0);
}

// check if we can get previous command
MU_TEST(testCmdPromptRetrieve) 
{
    char testcmd[] = "foo\r\e[A";
    char testcmdcall[] = "foo";
    char testcmdoutput[] = "foo\r";
    char testcmdout[11];
    mockDsPutReadsString(testcmd);
    mu_check(testCmdPromptLoop(10) == 2);
    mu_check(mockDsGetWrites(testcmdout, 4) == noError);
    mu_check(memcmp(testcmdout, testcmdoutput, 4) == 0); 
    mu_check(testCmdlineParseCallCnt == 1);
    mu_check(strncmp(testcmdcall, testCmdlineParseString, sizeof(testcmdcall)) == 0);
}

MU_TEST_SUITE(testCmdPrompt) 
{
    MU_SUITE_CONFIGURE(&testCmdPromptSetup, &testCmdPromptTeardown);
    MU_RUN_TEST(testCmdPromptEmpty);
    MU_RUN_TEST(testCmdPromptCmdlineEcho);
    MU_RUN_TEST(testCmdPromptCmdLineEdit);
    MU_RUN_TEST(testCmdPromptCmdlineInput);
    MU_RUN_TEST(testCmdPromptCmdlineEditInput);
    MU_RUN_TEST(testCmdPromptCmdlineBadEsc);
    MU_RUN_TEST(testCmdPromptPreviousEmpty);
    MU_RUN_TEST(testCmdPromptRetrieve);
    // see if we can fill buffer with commands and get last few commands
}

void testCmdPromptSuite()
{
    MU_RUN_SUITE(testCmdPrompt);
}