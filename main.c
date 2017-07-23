#include <stdio.h>

struct Bitmap {
    unsigned int header_id[2];
    unsigned int file_size;
    unsigned int reserved_1[2]; //these differ based upon creation program
    unsigned int reserved_2[2];
};

int bitConv(int * bytes) {

}

void set_header_id(FILE *fp, struct Bitmap *bitmap) {
    int i;
    fseek(fp, 0, SEEK_SET);
    for(i = 0; i < 2; i++) {
        int byte = fgetc(fp);
        bitmap->header_id[i] = (unsigned)byte;
    }
    rewind(fp);
}

void set_reserved(FILE *fp, struct Bitmap *bitmap) {
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
    struct Bitmap bitmap;

    //read header id
    set_header_id(fp, &bitmap);

    //set header size
    bitmap.file_size = lsize;

    //read reserved fields
    //set_reserved(fp, &bitmap);
    printf("%d", i);
    while(i < lsize) {
        printf("%x-", fgetc(fp));
        i++;
    }

    return 0;
}


