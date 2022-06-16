#include<stdio.h>
#include <stdint.h>
#include<stdlib.h>

typedef struct BITMAPHEADER
{
    char name[2];
    unsigned int size;
    int garbage;
    unsigned int image_offset;
}BITMAPHEADER;

typedef struct BITMAPINFOHEADER
{
    unsigned int header_size;
    unsigned int width;
    unsigned int height;
    unsigned short int colorplanes;
    unsigned short int bitsperpixel;
    unsigned int compression;
    unsigned int image_size;
}BITMAPINFOHEADER;

typedef struct pixel
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
}pixel;

typedef struct image_Array
{
    int height;
    int width;
    pixel** pixel_array;
}image_Array;


void openbmpfile(char* fileName, char* toTXT);
image_Array readImage(FILE* fp,int h,int w, char* toTXT);
