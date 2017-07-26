//left of finding a solution for storing bytes other than char* so i dont need
//to assign 2d arrays for byte arrays
#include <stdio.h>
#include <string.h>

typedef struct Bitmap {
    unsigned int header_id[2];
    unsigned int file_size;
    unsigned int reserved_1[2]; //these differ based upon creation program
    unsigned int reserved_2[2];
} Bitmap;

int * read_byte_sequence(FILE *fp, int offset, int sequence_length, int * byte_buffer) {
    int i;
    fseek(fp, offset, SEEK_SET);

    for(i = 0; i < sequence_length; i++) {

        byte_buffer[i] = fgetc(fp);

    }

    rewind(fp);
    return byte_buffer;
}

void set_header_id(FILE *fp, struct Bitmap *bitmap) {
    int i;
    int byte_sequence_length = 2;
    int byte_offset = 0;
    int byte_buffer[byte_sequence_length];
    memcpy(bitmap->header_id,read_byte_sequence(fp, byte_offset, byte_sequence_length, byte_buffer), byte_sequence_length);
}


void set_reserved(FILE *fp, Bitmap *bitmap) {
    int i;
    int byte_offset = 6;
    int field_length = 2;

    fseek(fp, byte_offset, SEEK_SET);
    for(i = 0; i < byte_offset; i++) {
        int byte = fgetc(fp);
        bitmap->reserved_1[i] = byte;
    }
    for(i = 0; i < byte_offset+field_length; i++) {
        int byte = fgetc(fp);
        bitmap->reserved_2[i] = byte;
    }
    rewind(fp);
}

int main() {
    FILE *fp = fopen("test.bmp", "r");
    Bitmap bitmap;

    //read header id
    set_header_id(fp, &bitmap);

    //set header size
    fseek(fp, 2, SEEK_SET);
    fread(&bitmap.file_size, 4,1,fp);

    printf("file size : %d\n", bitmap.file_size);
    return 0;
}


