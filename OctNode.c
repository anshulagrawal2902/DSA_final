#include <stdlib.h>
#include <stdio.h>
#include "headerResolver.h"

#ifndef Constants
#define MAX_DEPTH 8
#define MAX_PIXELS 17000000
#endif

void initOctNode(OCT_NODE *OctNode, QUANTIZER Quantizer, int level)
{
    *OctNode = (OCT_NODE)malloc(sizeof(OctNode));
    init_color(&((*OctNode)->c), 0, 0, 0);
    (*OctNode)->children = (OCT_NODE *)malloc(sizeof(OCT_NODE) * 8);
    for (int i = 0; i < 8; i++)
    {
        (*OctNode)->children[i] = NULL;
    }
    addLevelNode((*OctNode), level, Quantizer);
}

int isLeaf(OCT_NODE OctNode)
{
    if (OctNode->pixelCount > 0)
        return 1;
    else
        return 0;
}

void getLeafNodes_recurr(OCT_NODE OctNode, OCT_NODE **arr, int *rear)
{
    if (OctNode->pixelCount > 0)
    {
        (*arr)[*rear] = OctNode;
        (*rear) += 1;
        return;
    }
    for (int i = 0; i < 8; i++)
    {
        if (OctNode->children[i] == NULL)
            continue;
        getLeafNodes_recurr(OctNode->children[i], arr, rear);
    }
}

OCT_NODE *getLeafNodes(OCT_NODE OctNode)
{
    OCT_NODE *arr = malloc(sizeof(OCT_NODE) * MAX_PIXELS);
    for (int i = 0; i < MAX_PIXELS; i++)
    {
        arr[i] = NULL;
    }
    int b = 0;
    getLeafNodes_recurr(OctNode, &arr, &b);
    return (arr);
}

void addColor(COLOR color, OCT_NODE OctNode, int level, QUANTIZER quant)
{
    if (level >= MAX_DEPTH)
    {
        addTwoColors(OctNode->c, color);
        OctNode->pixelCount++;
        return;
    }
    int index = getColorIndex(color, level);
    if (OctNode->children[index] == NULL)
    {
        initOctNode(&(OctNode->children[index]), quant, level);
    }
    addColor(color, OctNode->children[index], level + 1, quant);
}

COLOR getColor(OCT_NODE OctNode)
{
    COLOR c;
    init_color(&c, OctNode->c->red / OctNode->pixelCount,
               OctNode->c->green / OctNode->pixelCount,
               OctNode->c->blue / OctNode->pixelCount);
    return c;
}

int removeLeaves(OCT_NODE OctNode)
{
    int count = 0;
    for (int i = 0; i < 8; i++)
    {
        if (OctNode->children[i] == NULL)
            continue;
        addTwoColors(OctNode->c, OctNode->children[i]->c);
        OctNode->pixelCount += OctNode->children[i]->pixelCount;
        count++;
    }
    for (int i = 0; i < 8; i++)
    {
        OctNode->children[i] = NULL;
    }
    if (count == 0)
        return 0;
    return count - 1;
}

int getSizeOfLeafNodeArray(OCT_NODE *arr)
{
    int i = 0;
    while (arr[i] != NULL)
    {
        i++;
    }
    return i;
}

int getPalleteIndex(COLOR color, int level, OCT_NODE OctNode)
{
    if (isLeaf(OctNode))
        return OctNode->palleteIndex;
    int index = getColorIndex(color, level);
    if (OctNode->children[index] != NULL)
    {
        return getPalleteIndex(color, level + 1, OctNode->children[index]);
    }
    else
    {
        int i = 0;
        while (i < 8)
        {
            if (OctNode->children[i] != NULL)
            {
                return getPalleteIndex(color, level + 1, OctNode->children[i]);
            }
            i++;
        }
    }
}



