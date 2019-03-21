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
#include <test_queue.h>
#include <queue.h>

#define TESTQUEUECHARSIZE   6
char testQueueCharBuf[TESTQUEUECHARSIZE];
queueChar_t testQueueChar = {
    TESTQUEUECHARSIZE,
    0,
    0,
    testQueueCharBuf,
    };

static void testQueueSetup(void) 
{
    queueInit(&testQueueChar);
}

static void testQueueTeardown(void) 
{

}

MU_TEST(testQueueEmpty) 
{
    char c;
    mu_check(queueDequeue(&testQueueChar, &c) == queueEmpty);
}

MU_TEST(testQueueEnqDeq) 
{
    char in = 'a';
    char out = 'q';
    for(int i = 0; i < TESTQUEUECHARSIZE-1; i++)
    {
        mu_check(queueEnqueue(&testQueueChar, in + i) == noError);
    }
    mu_check(queueState(&testQueueChar) == queueFull);
    mu_check(queueEnqueue(&testQueueChar, in) == queueFull);
    
    for(int i = 0; i < TESTQUEUECHARSIZE-1; i++)
    {
        mu_check(queueDequeue(&testQueueChar, &out) == noError);
        mu_check(out == in + i);
    }
    mu_check(queueDequeue(&testQueueChar, &out) == queueEmpty);
    // check if out has been unmodified
    mu_check(out == in + TESTQUEUECHARSIZE-2);
    
    // We do again a test, but now we will cross the max boundary
    mu_check(queueState(&testQueueChar) == queueEmpty);
    mu_check(queueEnqueue(&testQueueChar, in) == noError);
    mu_check(queueState(&testQueueChar) == queueNotEmpty);
    mu_check(queueDequeue(&testQueueChar, &out) == noError);   
    mu_check(queueState(&testQueueChar) == queueEmpty); 
    mu_check(queueDequeue(&testQueueChar, &out) == queueEmpty);
    mu_check(out == in);    
}

MU_TEST_SUITE(testQueue) 
{
    MU_SUITE_CONFIGURE(&testQueueSetup, &testQueueTeardown);
    MU_RUN_TEST(testQueueEmpty);
    MU_RUN_TEST(testQueueEnqDeq);
}

void testQueueSuite()
{
    MU_RUN_SUITE(testQueue);
}