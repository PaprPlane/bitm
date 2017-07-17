#include <stdio.h>
int main() {
    FILE *fp = fopen("test.bmp", "r");
    fseek(fp,0,SEEK_END); //set the file pointer to the end of the file
    long lsize=0,i=0;
    lsize = ftell(fp);    //get the position of the file pointer
    rewind(fp);           //set the file pointer to the beginning of the file
    while(i < lsize) {
        int first = fgetc(fp);
        i++;
        printf("%x",(unsigned)first);
    }
    return 0;
}


