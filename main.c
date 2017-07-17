#include <stdio.h>

struct Bitmap {
    unsigned int header_id[2];
};

void set_header_id(FILE *fp, struct Bitmap *bitmap) {
    int i;
    for(i = 0; i < 2; i++) {
        int byte = fgetc(fp);
        bitmap->header_id[i] = (unsigned)byte;
    }
}


int main() {
    FILE *fp = fopen("test.bmp", "r");
    fseek(fp,0,SEEK_END); //set the file pointer to the end of the file
    long lsize=0,i, j;
    lsize = ftell(fp);    //get the position of the file pointer
    rewind(fp);           //set the file pointer to the beginning of the file
    struct Bitmap bitmap;

    //read header data into bitmap struct
    set_header_id(fp, &bitmap);

    for(i = 0; i <= 2; i++) {
        printf("%x", bitmap.header_id[i]);
    }
    return 0;
}


