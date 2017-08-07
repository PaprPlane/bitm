#include <stdio.h>
#include "bitm.h";

int main() {
    FILE *fp = fopen("test.bmp", "r");
    Bitmap *bitmap = parse_bitmap(fp);
}
