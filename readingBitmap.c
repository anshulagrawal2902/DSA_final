#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"readingBitmap.h"

image_Array readImage(FILE* fp,int h,int w, char* toTXT)
{
    FILE *fw = fopen(toTXT,"w");
    image_Array pic;
    int i;
    pic.pixel_array=(pixel**)malloc(h*sizeof(void*));
    pic.height=h;
    pic.width=w;
    for(i=h-1; i>=0; i--)
    {
        pic.pixel_array[i]=(pixel*)malloc(w*sizeof(pixel));
        fread(pic.pixel_array[i], w, sizeof(pixel), fp);
    }
    for(int i=0; i<h; i++) {
        for(int j=0; j<w; j++) {
            fprintf(fw, "%d %d %d ", pic.pixel_array[i][j].red, pic.pixel_array[i][j].green, pic.pixel_array[i][j].blue);
        }
        // fprintf(fw, "\n");
    }
    fclose(fw);
    return pic;
}



void openbmpfile(char* fileName, char* toTXT)
{
    FILE *fp=fopen(fileName,"rb");
    BITMAPHEADER header;
    BITMAPINFOHEADER dib;
    image_Array img;
    fread(header.name,2,1,fp);
    fread(&header.size,3*sizeof(int),1,fp);
    fread(&dib,sizeof(BITMAPINFOHEADER),1,fp);
    fseek(fp,header.image_offset,SEEK_SET);
    img=readImage(fp,dib.height,dib.width, toTXT);
}

