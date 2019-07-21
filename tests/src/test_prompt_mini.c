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
#include <test_prompt_mini.h>
#include <prompt_mini.h>
#include <mock_datastreamchar.h>
#include <string.h>

char testPromptMiniBuffer[10];

result testPromptMiniHandler(char *const command);

promptData_t testPromptMiniData = 
{
    testPromptMiniBuffer,
    0,
    sizeof(testPromptMiniBuffer),
    testPromptMiniHandler,
};

char testPromptMiniHandlerbuf[10];

result testPromptMiniHandler(char *const command)
{
    strcpy(testPromptMiniHandlerbuf, command); 
    // return non standard value to check if everything is corrently passed
    return resultEnd;
}

int testPromptMiniLoop(int timeout)
{
    int counts = timeout;
    result r;
    do {
        r = promptProcess(&testPromptMiniData, &testDsChar);
        counts--;
    } while(r == noError && (counts > 0));
    return counts;
}

static void testPromptMiniSetup(void) 
{
     mockDsCharReset();
     testPromptMiniData.bufferIndex = 0;
}

static void testPromptMiniTeardown(void) 
{
}

MU_TEST(testPromptMiniEmpty) 
{
    mu_check(mockDsPutReadsString("\n") == noError);
    mu_check(promptProcess(&testPromptMiniData, &testDsChar) == promptError);
}

MU_TEST(testPromptMiniNormal) 
{
    mu_check(mockDsPutReadsString("abcde\n") == noError);
    mu_check(testPromptMiniLoop(5) == 0);
    mu_check(promptProcess(&testPromptMiniData, &testDsChar) == resultEnd);
    mu_check(strcmp(testPromptMiniHandlerbuf, "abcde") == 0);
}

MU_TEST_SUITE(testPromptMini) 
{
    MU_SUITE_CONFIGURE(&testPromptMiniSetup, &testPromptMiniTeardown);
    // test empty command
    MU_RUN_TEST(testPromptMiniEmpty);
    // test normal flow  
    MU_RUN_TEST(testPromptMiniNormal);
}

void testPromptMiniSuite()
{
    MU_RUN_SUITE(testPromptMini);
}