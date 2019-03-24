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
#include <datastream.h>
#include <test_dsputs.h>
#include <mock_datastreamchar.h>

static void testdsPutsSetup(void) 
{
    mockDsCharReset();
}

static void testdsPutsTeardown(void) 
{

}

MU_TEST(testdsPutsNormal) 
{
    char testInput[] = "abc";
    char testOutput[] = "abc\n";
    char testBuffer[12];
    mu_check(dsPuts(&testDsChar, testInput) == noError);
    mu_check(mockDsGetWrites(testBuffer, 4) == noError);
    mu_check(mockDsGetWriteStatus() == queueEmpty);
    mu_check(memcmp(testOutput, testBuffer, 4) == 0);
}

MU_TEST_SUITE(testdsPuts) 
{
    MU_SUITE_CONFIGURE(&testdsPutsSetup, &testdsPutsTeardown);
    MU_RUN_TEST(testdsPutsNormal);
}

void testdsPutsSuite()
{
    MU_RUN_SUITE(testdsPuts);
}