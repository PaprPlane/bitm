//left of finding a solution for storing bytes other than char* so i dont need
//to assign 2d arrays for byte arrays
#include <stdio.h>
#include <string.h>

typedef struct Bitmap {
    unsigned short int header_id;
    unsigned int file_size;
    unsigned short int reserved_1; //these differ based upon creation program
    unsigned short int reserved_2;
    unsigned int pixel_offset;
} Bitmap;

int main() {
    FILE *fp = fopen("test.bmp", "r");
    Bitmap bitmap;

    //read header id
    fread(&bitmap.header_id, 2,1,fp);

    //set header size
    fread(&bitmap.file_size, 4,1,fp);

    //set reserved1
    fread(&bitmap.reserved_1, 2, 1, fp);

    //set reserved2
    fread(&bitmap.reserved_2, 2, 1, fp);

    //set pixel offset
    fread(&bitmap.pixel_offset, 4, 1, fp);

    printf("file size : %d\n reserved_1: %d\n reserved_2: %d\n pixel offset: %d\n", bitmap.file_size, bitmap.reserved_1, bitmap.reserved_2, bitmap.pixel_offset);
    return 0;
}


