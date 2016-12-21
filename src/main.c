//
// Created by ikononenko on 19.12.16.
//

#pragma pack(push)
#pragma pack(1)

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <bmp.h>
#include <unistd.h>
#include <memory.h>

#define BMP_IMG_PATH        "logos/volf.bmp"
#define BMP_BFH_SIZE        14
#define BMP_BIF_SIZE        40

int main(int argc, char **argv)
{
//    printf("CLion hello world!\n");
    int                     fd,saveFD=-1,i,j;
    ssize_t                 rdBtCnt;
    __bitmap_file_header_t  fbHeader;
    __bitmap_info_t         fbInfo;

    if (argc < 2)
    {
        perror("Invalid call. Usage: %s </bmp/file/path.bmp> [</out/file/path>]");
        return EXIT_FAILURE;
    }

    if ((fd = open(argv[1],O_RDONLY)) == -1){
        perror("Can't open bmp image file");
        return EXIT_FAILURE;
    }
    if (argc == 3)
    {
        char    *saveFilePath = argv[2];

        if((saveFD =open(saveFilePath,O_RDWR | O_CREAT | O_TRUNC, 0644)) == -1)
        {
            perror("Can't open file to save BMP as text");
            return EXIT_FAILURE;
        }
        dup2(saveFD, fileno(stdout));
    }

    rdBtCnt = read(fd, &fbHeader, BMP_BFH_SIZE);
    if( rdBtCnt != BMP_BFH_SIZE || sizeof(fbHeader) != BMP_BFH_SIZE)
    {
        printf("Invalid file format!\n Read bytes: %d\n BITMAPFILEHEADER size:%d\n", (int)rdBtCnt, (int)sizeof(fbHeader) );
        return EXIT_FAILURE;
    }

    printf("Pixels data on %d bytes offset\n\n", fbHeader.offBits);

    rdBtCnt = read(fd, &fbInfo, BMP_BIF_SIZE);
    if( rdBtCnt != BMP_BIF_SIZE || sizeof(fbInfo) != BMP_BIF_SIZE)
    {
        printf("Invalid file format!\n Read bytes: %d\n BITMAPINFO size:%d\n", (int)rdBtCnt, (int)sizeof(fbInfo) );
        return EXIT_FAILURE;
    }

    printf("-=Image info=-\n");
    printf("Size:\t%d \n", fbInfo.size);
    printf("Bit count:\t%d \n", fbInfo.sizeImage);
    printf("Width:\t%d \n", fbInfo.width);
    printf("Height:\t%d \n\n", fbInfo.height);

    size_t  freeSpace = fbInfo.width;
    putchar(' ');
    for(i =0; i< freeSpace; i++)
    {
        putchar('-');
        putchar('-');
    }
    putchar('\n');

    void * dtImg = malloc(fbInfo.sizeImage);
    lseek(fd, fbHeader.offBits,SEEK_SET);
    rdBtCnt = read(fd,dtImg, fbInfo.sizeImage);
    size_t readDataCount = sizeof(dtImg);
    if( rdBtCnt != fbInfo.sizeImage )//|| readDataCount != fbInfo.sizeImage)
    {
        printf("Invalid file format!\n Read bytes: %d\n PIXELSDATA size:%d\n", (int)rdBtCnt, (int)readDataCount );
        return EXIT_FAILURE;
    }

    size_t lineSize = fbInfo.width*2+1;
    for(i = fbInfo.height-1; i>=0; i--)
    {
        void * buffer = malloc(lineSize);
        putchar('|');
        fflush(stdout);
        for (j = 0; j < fbInfo.width ; j++) {
            char point = ~1;
            int flag = (*(char * )(&dtImg[j+(i*fbInfo.width)]) & point);
            int ch = flag ? '@' : ' ';
            int separator = flag ? '-' : ' ';
            memset(buffer+j*2,ch,1);
            memset(buffer+j*2+1,separator,1);
        }
        memset(buffer+fbInfo.width*2,'|',1);
        memset(buffer+lineSize,'\n',1);
        write(fileno(stdout),buffer,lineSize+1);
        free(buffer);
    }



    free(dtImg);

    putchar(' ');
    for(i =0; i< freeSpace; i++)
    {
        putchar('-');
        putchar('-');
    }
    putchar('\n');


    return EXIT_SUCCESS;
}