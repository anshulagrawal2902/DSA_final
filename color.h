typedef struct color
{
    int red;
    int green;
    int blue;

} Color;
typedef Color *COLOR;

int *getArray(COLOR c);
void init_color(COLOR *c, int r, int g, int b);
char *int_to_str(int a);
char *toString(COLOR c);
void addTwoColors(COLOR c1, COLOR c2);
COLOR normalized(COLOR c, int pixelCount);
int getColorIndex(COLOR color, int level);