#include <stdio.h>
#include <stdlib.h>
#include "compressor.h"
#include "utils.h"

void compressFile(const char* inputFile, const char* outputFile) {
    FILE* inFile = openFile(inputFile, "rb");
    FILE* outFile = openFile(outputFile, "wb");

    if (!inFile || !outFile) {
        printf("Error: Unable to open files for compression.\n");
        return;
    }

    // Perform compression here (Example: Run-Length Encoding)
    unsigned char currentChar, nextChar;
    int count = 0;

    while (fread(&currentChar, sizeof(unsigned char), 1, inFile)) {
        count = 1;
        while (fread(&nextChar, sizeof(unsigned char), 1, inFile) && nextChar == currentChar) {
            count++;
            if (count == 255) break; // Prevent overflow
        }
        fwrite(&currentChar, sizeof(unsigned char), 1, outFile);
        fwrite(&count, sizeof(unsigned char), 1, outFile);
        if (nextChar != currentChar) {
            fseek(inFile, -1, SEEK_CUR); // Go back one step
        }
    }

    closeFile(inFile);
    closeFile(outFile);
}
