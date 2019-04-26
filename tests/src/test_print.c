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
#include <test_print.h>
#include <print.h>
#include <mock_datastreamchar.h>

static void testPrintSetup(void) 
{
    mockDsCharReset();
}

static void testPrintTeardown(void) 
{

}

MU_TEST(testPrintDigit) 
{
    char testZero[] = "0";
    char testNine[] = "9";
    char testA[] = "A";
    char testF[] = "F";
    char testOutput[4];
    mu_check(print_digit(&testDsChar, 0) == noError);
    mu_check(mockDsGetWrites(testOutput, 1) == noError);
    mu_check(mockDsGetWriteStatus() == queueEmpty);
    mu_check(memcmp(testOutput, testZero, 1) == 0);
}

MU_TEST(testPrintU8) 
{

}

MU_TEST_SUITE(testPrint) 
{
    MU_SUITE_CONFIGURE(&testPrintSetup, &testPrintTeardown);
    MU_RUN_TEST(testPrintDigit);
}

void testPrintSuite()
{
    MU_RUN_SUITE(testPrint);
}