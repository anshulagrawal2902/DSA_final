#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerResolver.h"

int main()
{
    QUANTIZER q;
    init_Quantizer(&q);
    add_RGB_values_to_Quantizer("image1.txt", q);
    printf("original number of colores in the image %d ", getSizeOfLeafNodeArray(getLeafNodes(q->root)));
    COLOR *pallete = makePallete(100, q);
    writeQuantizedImageToFile(q, "Qimage1.txt", pallete, "image1.txt");
    
}

