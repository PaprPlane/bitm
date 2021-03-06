#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitm.h"

Bitmap * parse_bitmap(FILE *fp) {
    fseek(fp, 0, SEEK_SET);
    BitmapHeader bitmapHeader;
    InfoHeader infoHeader;

    fread(&bitmapHeader.header_id, 2,1,fp);

    fread(&bitmapHeader.file_size, 4,1,fp);

    fread(&bitmapHeader.reserved_1, 2, 1, fp);

    fread(&bitmapHeader.reserved_2, 2, 1, fp);

    fread(&bitmapHeader.pixel_offset, 4, 1, fp);

    fread(&infoHeader, sizeof(InfoHeader), 1, fp);


    //read pixel data
    int pixel_count = infoHeader.height * infoHeader.width;
    int i,j = 0;
    Color color_array[pixel_count];
    fseek(fp, bitmapHeader.pixel_offset, SEEK_SET);
    for(i = 0; i < pixel_count/4; i+=4) {
        Color color;
        fread(&color, sizeof(Color), 1, fp);
        color_array[j] = color;
        j++;
    }

    //create the bitmap struct
    Bitmap *bitmap = malloc(sizeof(Bitmap) + (sizeof(color_array)/sizeof(unsigned char)));
    bitmap->bitmapHeader = bitmapHeader;
    bitmap->infoHeader = infoHeader;
    bitmap->colorSize = (sizeof(color_array)/sizeof(unsigned char)) -1;
    memcpy(bitmap->color_array, color_array, (sizeof(color_array)/sizeof(unsigned char)));
    return bitmap;
}


