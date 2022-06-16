#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include "headerResolver.h"

#ifndef Constants
#define MAX_DEPTH 8
#define MAX_PIXELS 17000000
#endif

void init_Quantizer(QUANTIZER *quant)
{
    (*quant) = malloc(sizeof(Quantizer));
    (*quant)->levels = malloc(sizeof(LEVELSNODE) * MAX_DEPTH);
    for (int i = 0; i < MAX_DEPTH; i++)
    {
        (*quant)->levels[i] = NULL;
    }
    initOctNode(&((*quant)->root), (*quant), 0);
}

void addColortoQuantizer(COLOR c, QUANTIZER quant)
{
    addColor(c, quant->root, 0, quant);
}

void addLevelNode(OCT_NODE OctNode, int level, QUANTIZER Quantizer)
{
    LEVELSNODE LevelsNode = malloc(sizeof(LevelsNode));
    LevelsNode->nodePtr = OctNode;
    LevelsNode->nextPtr = Quantizer->levels[level];
    Quantizer->levels[level] = LevelsNode;
}

void add_RGB_values_to_Quantizer(char *fileName, QUANTIZER Quantizer)
{   
    FILE *filePtr = fopen(fileName, "r");
    if (NULL == filePtr)
    {
        printf("file can't be opened \n");
    }
    char ch = '0';
    int n = 0;
    while (ch != EOF)
    {
        int arr[3];
        for (int i = 0; i < 3; i++)
        {
            n = 0;
            while (ch != ' ' && ch != EOF)
            {
                n = n * 10 + (ch - 48);
                ch = fgetc(filePtr);
            }
            ch = fgetc(filePtr);
            arr[i] = n;
        }
        COLOR c;
        init_color(&c, arr[0], arr[1], arr[2]);
        addColortoQuantizer(c, Quantizer);
    }
    fclose(filePtr);
}

OCT_NODE *getLeafNodesOfQuantizer(QUANTIZER Quantizer)
{
    return getLeafNodes(Quantizer->root);
}

COLOR *makePallete(int colorCount, QUANTIZER Quantizer)
{
    COLOR *pallete = malloc(sizeof(COLOR) * colorCount);
    OCT_NODE *leafNodes = getLeafNodesOfQuantizer(Quantizer);
    int leafCount = getSizeOfLeafNodeArray(leafNodes);
    int palleteIndex = 0;
    for (int currentLevel = MAX_DEPTH - 1; currentLevel >= 0; currentLevel--)
    {
        if (Quantizer->levels[currentLevel] != NULL)
        {
            LEVELSNODE ptr = Quantizer->levels[currentLevel];
            while (ptr != NULL)
            {
                int a = removeLeaves(ptr->nodePtr);
                leafCount -= a;
                if (leafCount <= colorCount)
                    break;
                ptr = ptr->nextPtr;
            }
            if (leafCount <= colorCount)
                break;
            Quantizer->levels[currentLevel] = NULL;
        }
    }
    int ptr1 = 0;
    leafNodes = getLeafNodesOfQuantizer(Quantizer);
    while (leafNodes[ptr1] != NULL)
    {
        if (palleteIndex >= colorCount)
            break;
        if (isLeaf(leafNodes[ptr1]))
            pallete[palleteIndex] = getColor(leafNodes[ptr1]);
        leafNodes[ptr1]->palleteIndex = palleteIndex;

        ptr1++;
        palleteIndex++;
    }
    return pallete;
}

int getPalleteIndexFromQuant(COLOR color, QUANTIZER Quantizer)
{
    return getPalleteIndex(color, 0, Quantizer->root);
}

void writePalleteToFile(char *fileName, COLOR *pallete)
{
    FILE *filePtr = fopen(fileName, "w");
    int i = 0;
    while (pallete[i] != NULL)
    {
        fprintf(filePtr, "%d ", pallete[i]->red);
        fprintf(filePtr, "%d ", pallete[i]->green);
        fprintf(filePtr, "%d ", pallete[i]->blue);
        i++;
    }
    fclose(filePtr);
}

void printColorPallete(COLOR *pallete)
{

    int i = 0;
    while (pallete[i] != NULL)
    {
        printf("%d ", pallete[i]->red);
        printf("%d ", pallete[i]->green);
        printf("%d ", pallete[i]->blue);
        i++;
    }
}

void printLevelsOfQuantizer(QUANTIZER Quantizer)
{
    for (int i = 0; i < MAX_DEPTH; i++)
    {
        LEVELSNODE ptr = Quantizer->levels[i];
        printf("%d \n\n", i);
        while (ptr != NULL)
        {
            printf("%d ", ptr->nodePtr->c->red);
            printf("%d ", ptr->nodePtr->c->green);
            printf("%d ", ptr->nodePtr->c->blue);
            printf(" -> %d ,  ", ptr->nodePtr->pixelCount);
            ptr = ptr->nextPtr;
        }
    }
}

void writeQuantizedImageToFile(QUANTIZER Quantizer, char* fileName, COLOR* pallete, char* imageFileName){

    FILE* filePtr1 = fopen(fileName, "w");
    if(filePtr1 == NULL) {
        printf("file cannot be opened1");
        return;
    }

    FILE* filePtr2 = fopen(imageFileName, "r");
    if(filePtr2 == NULL) {
        printf("file cannot be opened2");
        return;
    }
    char ch = '0';
    int n = 0;
    int palleteIndex = 0;
    while (ch != EOF)
    {
        int arr[3];
        for (int i = 0; i < 3; i++)
        {
            n = 0;
            while (ch != ' ' && ch != EOF)
            {
                n = n * 10 + (ch - 48);
                ch = fgetc(filePtr2);
            }
            ch = fgetc(filePtr2);
            arr[i] = n;
        }
        COLOR c;
        init_color(&c, arr[0], arr[1], arr[2]);
        palleteIndex = getPalleteIndexFromQuant(c, Quantizer);
        fprintf(filePtr1, "%d ",  pallete[palleteIndex]->red);
        fprintf(filePtr1, "%d ",  pallete[palleteIndex]->green);
        fprintf(filePtr1, "%d ",  pallete[palleteIndex]->blue);
    }
    fclose(filePtr1);
    fclose(filePtr2);
}

void QUANTIZE(char* imageName, int colorCount){
    QUANTIZER q;
    init_Quantizer(&q);
    openbmpfile(imageName, "temporary.txt");
    add_RGB_values_to_Quantizer("temporary.txt", q);
    COLOR *pallete = makePallete(colorCount, q);
    writeQuantizedImageToFile(q, "quantizedImage.txt", pallete, "temporary.txt");
}

