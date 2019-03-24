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
#ifndef DATASTREAM_H
#define DATASTREAM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <results.h>
#include <stddef.h>
#include <stdint.h>

typedef struct datastreamChar
{
    result (*write)(const char *c);
    result (*read)(char *c);
    const char *name;
} datastreamChar_t;

typedef struct datastreamUint8
{
    result (*write)(const uint8_t *c);
    result (*read)(uint8_t *c);
    const char *name;
} datastreamUint8_t;

typedef struct datastreamUint16
{
    result (*write)(const uint16_t *c);
    result (*read)(uint16_t *c);
    const char *name;
} datastreamUint16_t;

#define dsWriteElement(stream, e) _Generic((stream), \
    datastreamChar_t * : dsWriteChar, \
    datastreamUint8_t * : dsWriteUint8, \
    datastreamUint16_t * : dsWriteUint16 \
    )(stream, e)
    
#define dsReadElement(stream, e) _Generic((stream), \
    datastreamChar_t * : dsReadChar, \
    datastreamUint8_t * : dsReadUint8, \
    datastreamUint16_t * : dsReadUint16 \
    )(stream, e)

/* write c to stream*/
result dsWriteChar(datastreamChar_t *stream, const char c);
/* reads from stream into c */
result dsReadChar(datastreamChar_t *stream, char *c);
/* write e to stream*/
result dsWriteUint8(datastreamUint8_t *stream, const uint8_t c);
/* reads from stream into e */
result dsReadUint8(datastreamUint8_t *stream, uint8_t *c);
/* write e to stream*/
result dsWriteUint16(datastreamUint16_t *stream, const uint16_t c);
/* reads from stream into e */
result dsReadUint16(datastreamUint16_t *stream, uint16_t *c);
/* write string ala puts to char stream */
result dsPuts(const datastreamChar_t *stream, char *restrict s);


#ifdef __cplusplus
}
#endif

#endif