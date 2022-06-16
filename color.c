#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerResolver.h"

void init_color(COLOR *c, int r, int g, int b)
{
    (*c) = (COLOR)malloc(sizeof(Color));
    (*c)->red = r;
    (*c)->green = g;
    (*c)->blue = b;
}

int *getArray(COLOR c)
{
    int *arr = (int *)malloc(sizeof(int));
    // arr[0] = c->red;
    // arr[1] = c->green;
    // arr[2] = c->blue;
    // arr[3] = arr[0] + arr[1] + arr[2];
    return arr;
}

char *int_to_str(int a)
{
    char *temp = (char *)malloc(sizeof(char) * 100);
    sprintf(temp, "%d", a);
    return temp;
}

char *toString(COLOR c)
{
    char *str = malloc(sizeof(char) * 100);
    char *r = int_to_str(c->red);
    char *g = int_to_str(c->green);
    char *b = int_to_str(c->blue);
    int i = 0;
    for (int j = 0; j < strlen(r); j++)
    {
        str[i] = r[j];
        i++;
    }
    for (int j = 0; j < strlen(g); j++)
    {
        str[i] = g[j];
        i++;
    }
    for (int j = 0; j < strlen(b); j++)
    {
        str[i] = b[j];
        i++;
    }
    return str;
}

COLOR normalized(COLOR c, int pixelCount)
{
    COLOR col = (COLOR)malloc(sizeof(Color));
    col->red = c->red / pixelCount;
    col->green = c->green / pixelCount;
    col->blue = c->blue / pixelCount;
    return col;
}

void addTwoColors(COLOR c1, COLOR c2)
{
    c1->red = c1->red + c2->red;
    c1->green = c1->green + c2->green;
    c1->blue = c1->blue + c2->blue;
}

int getColorIndex(COLOR color, int level)
{
    int index = 0;
    int mask = 0b10000000 >> level;
    if (color->red & mask)
        index = index | 0b100;
    if (color->green & mask)
        index = index | 0b010;
    if (color->blue & mask)
        index = index | 0b001;

    return index;
}
