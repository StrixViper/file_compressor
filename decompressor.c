#include <stdio.h>
#include <stdlib.h>
#include "decompressor.h"
#include "utils.h"

void decompressFile(const char* inputFile, const char* outputFile) {
    FILE* inFile = openFile(inputFile, "rb");
    FILE* outFile = openFile(outputFile, "wb");

    if (!inFile || !outFile) {
        printf("Error: Unable to open files for decompression.\n");
        return;
    }

    // Perform decompression (Inverse of Run-Length Encoding)
    unsigned char currentChar;
    unsigned char count;

    while (fread(&currentChar, sizeof(unsigned char), 1, inFile)) {
        if (fread(&count, sizeof(unsigned char), 1, inFile)) {
            for (int i = 0; i < count; i++) {
                fwrite(&currentChar, sizeof(unsigned char), 1, outFile);
            }
        }
    }

    closeFile(inFile);
    closeFile(outFile);
}
