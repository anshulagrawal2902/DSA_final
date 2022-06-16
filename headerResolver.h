
//COLOR STRUCT
typedef struct color
{
    int red;
    int green;
    int blue;

} Color;
typedef Color *COLOR;

//OCTNODE STRUCT
typedef struct OctNode
{
    COLOR c;
    int pixelCount;
    int palleteIndex;
    struct OctNode **children;
} OctNode;
typedef OctNode *OCT_NODE;

//LEVELSNODE STRUCT
typedef struct LevelsNode
{
    OCT_NODE nodePtr;
    struct LevelsNode *nextPtr;
} LevelsNode;
typedef LevelsNode *LEVELSNODE;

//QUANTIZER STRUCT
typedef struct Quantizer
{
    LEVELSNODE *levels;
    OCT_NODE root;
} Quantizer;
typedef Quantizer *QUANTIZER;

//COLOR FUNCTIONS
int *getArray(COLOR c);
void init_color(COLOR *c, int r, int g, int b);
char *int_to_str(int a);
char *toString(COLOR c);
void addTwoColors(COLOR c1, COLOR c2);
COLOR normalized(COLOR c, int pixelCount);
int getColorIndex(COLOR color, int level);

//OCTNODE FUNCTIONS
void initOctNode(OCT_NODE *OctNode, QUANTIZER Quantizer, int level);
int isLeaf(OCT_NODE OctNode);
OCT_NODE *getLeafNodes(OCT_NODE OctNode);
void addColor(COLOR color, OCT_NODE OctNode, int level, QUANTIZER Quantizer);
COLOR getColor(OCT_NODE OctNode);
int removeLeaves(OCT_NODE OctNode);
int getSizeOfLeafNodeArray(OCT_NODE *arr);
int getPalleteIndex(COLOR color, int level, OCT_NODE OctNode);

//QUANTIZER FUNCTIONS
void init_Quantizer(QUANTIZER *Quantizer);
void addColortoQuantizer(COLOR c, QUANTIZER q);
void addLevelNode(OCT_NODE OctNode, int level, QUANTIZER Quantizer);
OCT_NODE *getLeafNodesOfQuantizer(QUANTIZER Quantizer);
COLOR *makePallete(int colorCount, QUANTIZER Quantizer);
void writePalleteToFile(char *fileName, COLOR *pallete);
void printLevelsOfQuantizer(QUANTIZER Quantizer);
void printColorPallete(COLOR *pallete);
void writeQuantizedImageToFile(QUANTIZER Quantizer, char* fileName, COLOR* pallete, char* imageFileName);
void QUANTIZE(char* imageName, int colorCount);

//UTILS FUNCTIONS
void add_RGB_values_to_Quantizer(char *fileName, QUANTIZER Quantizer);
void openbmpfile(char* imageName, char* writeImageToFileName);


//reading Bitmap
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
