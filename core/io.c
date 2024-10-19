#include "io.h"
#include "utils.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define IO_READ_CHUCK_SIZE 2097152 /* 20MB */

File IoiceCreamReadFile(const char* filePath) {

    printf("File is read -> %s\n", filePath); 

    File file = {.inValid = false }; 

    FILE* fp = fopen(filePath, "rb"); 

    if (!fp || ferror(fp)) {
        printf("Reading file error %s error %d\n", filePath, errno); 
        exit(1); 
    }

    char* data = NULL; 
    char* tempBuffer; 
    usize size = 0; 
    usize used = 0; 
    usize n; 

    while (1) {

        if (used + IO_READ_CHUCK_SIZE + 1 > size) {

            size = used + IO_READ_CHUCK_SIZE + 1;

            if (size <= used) {
                printf("Filse read is to large %s\n", filePath); 
                free(data); 
                exit(1);
            }

            tempBuffer = realloc(data, size); 

            if (!tempBuffer) {
                printf("Memory allocation failure\n"); 
                free(data); 
                exit(1);
            }

            data = tempBuffer; 
        }

        n = fread(data + used, 1, IO_READ_CHUCK_SIZE, fp); 

        if (n == 0) 
            break; 

        used += n; 
    }

    if (ferror(fp)) {
        printf("Reading file error %s error %d\n", filePath, errno); 
        free(data); 
        exit(1); 
    }

    tempBuffer = realloc(data, used + 1);

    if (!tempBuffer) {
        printf("Memory allocation failure\n"); 
        free(data); 
        exit(1);
    }
    data = tempBuffer;  

    data[used] = '\0'; 
    
    file.data = data; 
    file.size = used; 
    file.inValid = true; 
    
    return file; 
}
int IoiceCreamWriteFile(void* buffer, usize data, const char* filePath) {

    FILE* fp = fopen(filePath, "wb");  
    
    printf("File is write -> %s\n", filePath); 

    if (!fp || ferror(fp)) {
        printf("Reading file error %s error %d\n", filePath, errno); 
    }

    usize chuck_written = fwrite(buffer, data, 1, fp); 

    if (chuck_written != 1) {
	    printf("Expected 1 chunk, got %zu.\n", chuck_written);
    }
    fclose(fp);
    return 0; 
}
