#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

FILE* openFile(const char* fileName, const char* mode) {
    FILE* file = fopen(fileName, mode);
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s\n", fileName);
        exit(EXIT_FAILURE);
    }
    return file;
}

void closeFile(FILE* file) {
    if (fclose(file) != 0) {
        fprintf(stderr, "Error: Could not close file.\n");
    }
}

void* allocateMemory(size_t size) {
    void* ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void freeMemory(void* ptr) {
    free(ptr);
}
