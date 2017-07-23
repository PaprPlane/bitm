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

int bitConv(int * byte_sequence) {
    int accum, i = 0;
    int byte_sequence_length = sizeof(byte_sequence)/sizeof(int);
    for(i = 0; i < byte_sequence_length; ++i) {
        accum += (int)byte_sequence[i];
    }
    return accum;
}

int * read_byte_sequence(FILE *fp, int offset, int sequence_length, int * byte_buffer) {
    int i;
    fseek(fp, offset, SEEK_SET);
    for(i = 0; i < sequence_length; i++) {
        char temp_buffer[sequence_length][sequence_length*4];
        sprintf(temp_buffer[i], "%04lx",fgetc(fp));
        byte_buffer[i] =
    }
    rewind(fp);
    return byte_buffer;
}

void set_header_id(FILE *fp, struct Bitmap *bitmap) {
    int i;
    int byte_sequence_length = 2;
    int byte_offset = 0;
    int byte_buffer[byte_sequence_length][byte_sequence_length*4];
    memcpy(bitmap->header_id,read_byte_sequence(fp, byte_offset, byte_sequence_length, byte_buffer), byte_sequence_length);
}



void set_file_size(FILE *fp, Bitmap *bitmap) {
    int i;
    int file_size = 0;
    int byte_offset = 2;
    int byte_sequence_length = 4;
    int byte_buffer[byte_sequence_length][];
    memcpy(byte_buffer, read_byte_sequence(fp, byte_offset, byte_sequence_length, byte_buffer), byte_sequence_length);

    for(i = 0; i < byte_sequence_length; ++i) {
        printf("\n FILE SIZE ACCUM ADD %d", (int)byte_buffer[i]);
        file_size += (int)byte_buffer[i];
    }
    printf("\nFILE SIZE : %d\n", file_size);
    bitmap->file_size = file_size;
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
    fseek(fp,0,SEEK_END); //set the file pointer to the end of the file
    long lsize=0;
    int i = 0;
    lsize = ftell(fp);    //get the position of the file pointer
    rewind(fp);           //set the file pointer to the beginning of the file
    Bitmap bitmap;

    //read header id
    set_header_id(fp, &bitmap);

    //set header size
    set_file_size(fp, &bitmap);

    //read reserved fields
    //set_reserved(fp, &bitmap);
    printf("%d", i);
    printf("%d", bitmap.file_size);
    return 0;
}


