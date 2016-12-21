//
// Created by ikononenko on 19.12.16.
//

#ifndef MBMPREADER_BMP_H
#define MBMPREADER_BMP_H

struct __bitmap_file_header {
    unsigned short  type;
    unsigned int    size;
    unsigned short  reserved1, reserved2;
    unsigned int    offBits;
};

struct __bitmap_info {
    unsigned int    size;
    unsigned int    width, height;
    unsigned short  planes, bitCount;
    unsigned int    compression, sizeImage;
    unsigned int    xPelsPerMeter, yPelsPerMeter;
    unsigned int    crlUsed, crlImportant;
};

typedef struct __bitmap_file_header     __bitmap_file_header_t;
typedef struct __bitmap_info            __bitmap_info_t;

#endif //MBMPREADER_BMP_H
