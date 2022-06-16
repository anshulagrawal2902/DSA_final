#include "OctNode.h"
typedef struct Quantizer
{

    OCT_NODE root;
} Quantizer;
typedef Quantizer *QUANTIZER;
void init_Quantizer(QUANTIZER *Quantizer);
void addColortoQuantizer(COLOR c, QUANTIZER q);