#ifndef BITMAP
#define BITMAP

typedef struct BitmapHeader_t
{
    unsigned short int header_id;
    unsigned int file_size;
    unsigned short int reserved_1;
    unsigned short int reserved_2;
    unsigned int pixel_offset;
} BitmapHeader;

typedef struct InfoHeader_t
{
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

typedef struct Color_t {
    unsigned char b,r,g;
} Color;

typedef struct Bitmap_t {
    BitmapHeader bitmapHeader;
    InfoHeader infoHeader;
    Color color_array[];
} Bitmap;

Bitmap * parse_bitmap(FILE *);

#endif
