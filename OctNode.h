#include "color.h"

typedef struct OctNode
{
    COLOR c;
    int pixelCount;
    int palleteIndex;
    struct OctNode **children;
} OctNode;
typedef OctNode *OCT_NODE;

void initOctNode();
int isLeaf(OCT_NODE OctNode);
void getLeafNodes(OCT_NODE OctNode, OCT_NODE **arr, int rear);
void addColor(COLOR color, OCT_NODE OctNode, int level, QUANTIZER Quantizer);
COLOR getColor(OCT_NODE OctNode);
int removeLeaves(OCT_NODE OctNode);
