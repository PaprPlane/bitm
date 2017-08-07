//left of finding a solution for storing bytes other than char* so i dont need
//to assign 2d arrays for byte arrays
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned short int header_id;
    unsigned int file_size;
    unsigned short int reserved_1; //these differ based upon creation program
    unsigned short int reserved_2;
    unsigned int pixel_offset;
} BitmapHeader;

typedef struct {
    unsigned int header_size;
    unsigned int width;
    unsigned int height;
    unsigned short int color_planes;
    unsigned short int depth;
    unsigned int compression;
    unsigned int image_size;
    unsigned int hor_res;
    unsigned int ver_res;
    unsigned int num_colors;
    unsigned int important_num_colors;
} InfoHeader;

typedef struct {
    unsigned char b,g,r;
} Color;

typedef struct {
    BitmapHeader bitmapHeader;
    InfoHeader infoHeader;
    Color color_array[];
} Bitmap;

Bitmap * parse_bitmap(FILE *fp) {
    BitmapHeader bitmapHeader;
    InfoHeader infoHeader;

    //read header id
    fread(&bitmapHeader.header_id, 2,1,fp);

    //set header size
    fread(&bitmapHeader.file_size, 4,1,fp);

    //set reserved1
    fread(&bitmapHeader.reserved_1, 2, 1, fp);

    //set reserved2
    fread(&bitmapHeader.reserved_2, 2, 1, fp);

    //set pixel offset
    fread(&bitmapHeader.pixel_offset, 4, 1, fp);

    //read the info header into the InfoHeader struct
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
    memcpy(bitmap->color_array, color_array, (sizeof(color_array)/sizeof(unsigned char)));
    return bitmap;
}


