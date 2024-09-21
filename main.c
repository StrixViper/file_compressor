#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Utility functions
void handleFileError(FILE *file, const char *fileName) {
    if (file == NULL) {
        printf("Error: Could not open file %s\n", fileName);
        exit(1);
    }
}

// Function declarations
void compressFile(const char *inputFileName, const char *outputFileName);
void decompressFile(const char *inputFileName, const char *outputFileName);

// Compression logic (Run-Length Encoding with handling single characters)
void compressFile(const char *inputFileName, const char *outputFileName) {
    FILE *inputFile = fopen(inputFileName, "r");
    handleFileError(inputFile, inputFileName);

    FILE *outputFile = fopen(outputFileName, "w");
    handleFileError(outputFile, outputFileName);

    int count;
    char currentChar, nextChar;

    // Reading the first character
    currentChar = fgetc(inputFile);

    while (currentChar != EOF) {
        count = 1;
        nextChar = fgetc(inputFile);

        // Count consecutive occurrences of the same character
        while (nextChar == currentChar && nextChar != EOF) {
            count++;
            nextChar = fgetc(inputFile);
        }

        // If the count is greater than 1, write character and count to the compressed file
        if (count > 1) {
            fprintf(outputFile, "%c%d", currentChar, count);
        } else {
            // If no repetition, just write the character
            fprintf(outputFile, "%c", currentChar);
        }

        // Update current character
        currentChar = nextChar;
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("File compressed successfully!\n");
}

// Decompression logic
void decompressFile(const char *inputFileName, const char *outputFileName) {
    FILE *inputFile = fopen(inputFileName, "r");
    handleFileError(inputFile, inputFileName);

    FILE *outputFile = fopen(outputFileName, "w");
    handleFileError(outputFile, outputFileName);

    char currentChar;
    int count;

    // Read character and its count and write decompressed output
    while ((currentChar = fgetc(inputFile)) != EOF) {
        // Check if the next character is a digit (indicating a count for repeated characters)
        if (isdigit(fpeek(inputFile))) {
            fscanf(inputFile, "%d", &count);
            for (int i = 0; i < count; i++) {
                fputc(currentChar, outputFile);
            }
        } else {
            // No count means just one occurrence of the character
            fputc(currentChar, outputFile);
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("File decompressed successfully!\n");
}

// Peek into the next character of the file without advancing the file pointer
int fpeek(FILE *stream) {
    int c = fgetc(stream);
    ungetc(c, stream);
    return c;
}

// Main function
int main() {
    int choice;
    char inputFileName[100], outputFileName[100];

    printf("File Compressor/Decompressor\n");
    printf("1. Compress a file\n");
    printf("2. Decompress a file\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter the input file name to compress: ");
            scanf("%s", inputFileName);
            printf("Enter the output file name for the compressed file: ");
            scanf("%s", outputFileName);
            compressFile(inputFileName, outputFileName);
            break;

        case 2:
            printf("Enter the input file name to decompress: ");
            scanf("%s", inputFileName);
            printf("Enter the output file name for the decompressed file: ");
            scanf("%s", outputFileName);
            decompressFile(inputFileName, outputFileName);
            break;

        default:
            printf("Invalid choice. Please enter 1 or 2.\n");
            break;
    }

    return 0;
}
