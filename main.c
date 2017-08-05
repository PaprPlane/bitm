//left of finding a solution for storing bytes other than char* so i dont need
//to assign 2d arrays for byte arrays
#include <stdio.h>
#include <string.h>

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

int main() {
    FILE *fp = fopen("test.bmp", "r");
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

    printf("file size : %d\n reserved_1: %d\n reserved_2: %d\n pixel offset: %d\n", bitmapHeader.file_size, bitmapHeader.reserved_1, bitmapHeader.reserved_2, bitmapHeader.pixel_offset);

    //read the info header into the InfoHeader struct
    fread(&infoHeader, sizeof(InfoHeader), 1, fp);


    printf("header_size: %d\n", infoHeader.header_size);
    printf("width: %d\n", infoHeader.width);
    printf("height: %d\n", infoHeader.height);
    printf("color_planes: %d\n", infoHeader.color_planes);
    printf("depth: %d\n", infoHeader.depth);
    printf("compression: %d\n", infoHeader.compression);
    printf("image_size: %d\n", infoHeader.image_size);
    printf("hor_res: %d\n", infoHeader.hor_res);
    printf("ver_res: %d\n", infoHeader.ver_res);
    printf("num_colors: %d\n", infoHeader.num_colors);
    printf("important_num_colors: %d\n", infoHeader.important_num_colors);

    return 0;
}


