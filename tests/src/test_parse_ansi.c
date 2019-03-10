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
#include <sqMinUnitC.h>
#include <test_parse_ansi.h>
#include <parse_ansi.h>

void testParseAnsiSetup(void) 
{
}

void testParseAnsiTeardown(void) 
{

}

MU_TEST(testParseAnsiEmpty) 
{
    mu_check(ansiParse('a') == ansiError);
}

MU_TEST(testParseAnsiUnknownEscapes)
{
    mu_check(ansiParse('\e') == ansiEntered);
    mu_check(ansiParse('_') == ansiError);
    mu_check(ansiParse('\e') == ansiEntered);
    mu_check(ansiParse('[') == ansiBrackOpen);
    mu_check(ansiParse('_') == ansiError);    
}

MU_TEST(testParseAnsiCursorUp)
{
    mu_check(ansiParse('\e') == ansiEntered);
    mu_check(ansiParse('[') == ansiBrackOpen);
    mu_check(ansiParse('A') == ansiCursorUp);
}

MU_TEST(testParseAnsiCursorForward)
{
    mu_check(ansiParse('\e') == ansiEntered);
    mu_check(ansiParse('[') == ansiBrackOpen);
    mu_check(ansiParse('C') == ansiCursorForward);
}

MU_TEST(testParseAnsiInvalidValidInvalid)
{
    mu_check(ansiParse('a') == ansiError);
    mu_check(ansiParse('\e') == ansiEntered);
    mu_check(ansiParse('[') == ansiBrackOpen);
    mu_check(ansiParse('C') == ansiCursorForward);
    mu_check(ansiParse('a') == ansiError);
}

MU_TEST_SUITE(testParseAnsi) 
{
    MU_SUITE_CONFIGURE(&testParseAnsiSetup, &testParseAnsiTeardown);
    MU_RUN_TEST(testParseAnsiEmpty);
    MU_RUN_TEST(testParseAnsiUnknownEscapes);
    MU_RUN_TEST(testParseAnsiCursorUp);
    MU_RUN_TEST(testParseAnsiCursorForward);
    MU_RUN_TEST(testParseAnsiInvalidValidInvalid);
}

void testParseAnsiSuite()
{
    MU_RUN_SUITE(testParseAnsi);
}