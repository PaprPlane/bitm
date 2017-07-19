#include <stdio.h>

struct Bitmap {
    unsigned int header_id[2];
    unsigned int file_size;
};

void set_header_id(FILE *fp, struct Bitmap *bitmap) {
    int i;
    fseek(fp, 0, SEEK_SET);
    for(i = 0; i < 2; i++) {
        int byte = fgetc(fp);
        bitmap->header_id[i] = (unsigned)byte;
    }
    rewind(fp);
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
    bitmap.file_size = lsize;
    while(i < lsize) {
        printf("%x-", fgetc(fp));
        i++;
    }
//    printf("%ld\n", lsize);
//    for(i = 0; i < 4; i++) {
//        printf("%d\n", bitmap.file_size[i]);
//    }

    return 0;
}


