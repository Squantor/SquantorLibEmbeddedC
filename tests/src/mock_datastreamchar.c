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

#include <datastream.h>
#include <string.h>

#define MOCKDSCHARBUFSIZE   128

result mockDsCharWrite(const char *c);
result mockDsCharRead(char *c);

const char testDsCharName[] = "char stream";
datastreamChar_t testDsChar = 
{
    mockDsCharWrite,
    mockDsCharRead,
    testDsCharName,
};

char dsCharWriteBuf[MOCKDSCHARBUFSIZE];
int dsCharWriteBufIdx;
int dsCharWriteBufMax;
char dsCharReadBuf[MOCKDSCHARBUFSIZE];
int dsCharReadBufIdx;
int dsCharReadBufMax;

void mockDsCharReset()
{
    dsCharWriteBufIdx = dsCharReadBufIdx = 0;
    dsCharWriteBufMax = dsCharReadBufMax = 0;
    memset(dsCharWriteBuf, 0, sizeof(dsCharWriteBuf));
    memset(dsCharReadBuf, 0, sizeof(dsCharReadBuf));
}

result mockDsCharSetupWrite(int maxWrites)
{
    if(maxWrites < MOCKDSCHARBUFSIZE)
    {
        dsCharWriteBufMax = maxWrites;
        return noError;
    }
    else
        return error;
}

result mockDsCharSetupRead(char *buf, size_t size)
{
    if(size > MOCKDSCHARBUFSIZE)
        return error;
    memcpy(dsCharReadBuf, buf, size);
    dsCharReadBufMax = (int) size;
    return noError;
}


result mockDsCharWrite(const char *c)
{
    if(dsCharWriteBufIdx == dsCharWriteBufMax)
        return streamFull;
    dsCharWriteBuf[dsCharWriteBufIdx] = *c;
    dsCharWriteBufIdx++;
    return noError;
}

result mockDsCharRead(char *c)
{
    if(dsCharReadBufIdx == dsCharReadBufMax)
        return streamEmtpy;
    *c = dsCharReadBuf[dsCharReadBufIdx];
    dsCharReadBufIdx++;
    return noError;
}