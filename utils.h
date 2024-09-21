#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

// Opens a file in the given mode and handles errors.
FILE* openFile(const char* fileName, const char* mode);

// Closes the file and handles any errors.
void closeFile(FILE* file);

// Allocates memory and checks for allocation failure.
void* allocateMemory(size_t size);

// Frees allocated memory.
void freeMemory(void* ptr);

#endif
