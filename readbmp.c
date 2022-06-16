#include<stdio.h>
#include<stdlib.h>
#include<math.h>
// #include<stdbool.h>

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


image_Array readImage(FILE* fp,int h,int w)
{
    FILE *fw = fopen("writebmp.txt","w");
    // printf("df");
    image_Array pic;
    int i;
    pic.pixel_array=(pixel**)malloc(h*sizeof(void*));
    pic.height=h;
    pic.width=w;
    for(i=h-1; i>=0; i--)
    {
        // printf("fvx");
        pic.pixel_array[i]=(pixel*)malloc(w*sizeof(pixel));
        fread(pic.pixel_array[i], w, sizeof(pixel), fp);
    }
    for(int i=0; i<h; i++) {
        for(int j=0; j<w; j++) {
            fprintf(fw, "%d %d %d ", pic.pixel_array[i][j].red, pic.pixel_array[i][j].green, pic.pixel_array[i][j].blue);
        }
        fprintf(fw, "\n");
    }
    fclose(fw);
    return pic;
}



void openbmpfile()
{
    FILE *fp=fopen("MARBLES.BMP","rb");
    // FILE *fcompr = fopen("comprmatrix.txt", "r");
    BITMAPHEADER header;
    BITMAPINFOHEADER dib;
    image_Array img;
    // fread(&header,sizeof(BITMAPHEADER),1,fp);
    //printf("%d\n",sizeof(header));
    fread(header.name,2,1,fp);
    fread(&header.size,3*sizeof(int),1,fp);
    fread(&dib,sizeof(BITMAPINFOHEADER),1,fp);

    fseek(fp,header.image_offset,SEEK_SET);
    // printf("%d", dib.width);
    img=readImage(fp,dib.height,dib.width);
    

    
}

int main()
{
    openbmpfile();
    return 0;
}