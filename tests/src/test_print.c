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
    mu_check(printDigit(&testDsChar, 0) == noError);
    mu_check(mockDsGetWrites(testOutput, 1) == noError);
    mu_check(mockDsGetWriteStatus() == queueEmpty);
    mu_check(memcmp(testOutput, testZero, 1) == 0);
    mu_check(printDigit(&testDsChar, 9) == noError);
    mu_check(mockDsGetWrites(testOutput, 1) == noError);
    mu_check(mockDsGetWriteStatus() == queueEmpty);
    mu_check(memcmp(testOutput, testNine, 1) == 0);
    mu_check(printDigit(&testDsChar, 0x0A) == noError);
    mu_check(mockDsGetWrites(testOutput, 1) == noError);
    mu_check(mockDsGetWriteStatus() == queueEmpty);
    mu_check(memcmp(testOutput, testA, 1) == 0);
    mu_check(printDigit(&testDsChar, 0x0F) == noError);
    mu_check(mockDsGetWrites(testOutput, 1) == noError);
    mu_check(mockDsGetWriteStatus() == queueEmpty);
    mu_check(memcmp(testOutput, testF, 1) == 0);
}

MU_TEST(testPrintHexU8) 
{
    char testA6[] = "A6";
    char testOutput[4];
    mu_check(printHexU8(&testDsChar, 0xA6) == noError);
    mu_check(mockDsGetWrites(testOutput, 2) == noError);
    mu_check(mockDsGetWriteStatus() == queueEmpty);
    mu_check(memcmp(testOutput, testA6, 2) == 0);
}

MU_TEST(testPrintHexU16) 
{
    char test1B2C[] = "1B2C";
    char testOutput[4];
    mu_check(printHexU16(&testDsChar, 0x1B2C) == noError);
    mu_check(mockDsGetWrites(testOutput, 4) == noError);
    mu_check(mockDsGetWriteStatus() == queueEmpty);
    mu_check(memcmp(testOutput, test1B2C, 4) == 0);
}

MU_TEST(testPrintHexU32) 
{
    char test3D4E5F67[] = "3D4E5F67";
    char testOutput[8];
    mu_check(printHexU32(&testDsChar, 0x3D4E5F67) == noError);
    mu_check(mockDsGetWrites(testOutput, 8) == noError);
    mu_check(mockDsGetWriteStatus() == queueEmpty);
    mu_check(memcmp(testOutput, test3D4E5F67, 8) == 0);
}

MU_TEST_SUITE(testPrint) 
{
    MU_SUITE_CONFIGURE(&testPrintSetup, &testPrintTeardown);
    MU_RUN_TEST(testPrintDigit);
    MU_RUN_TEST(testPrintHexU8);
    MU_RUN_TEST(testPrintHexU16);
    MU_RUN_TEST(testPrintHexU32);
}

void testPrintSuite()
{
    MU_RUN_SUITE(testPrint);
}