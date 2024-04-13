#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to perform run-length encoding
char* encode(char* input) {
    int length = strlen(input);
    char* encoded = (char*)malloc(9 * length * sizeof(char)); // Maximum possible length after encoding
    int count = 1;
    int index = 0;

    // Iterate through the input string
    for (int i = 0; i < length; i++) {
        // If the current character is the same as the next character, increment count
        if (input[i] == input[i + 1]) {
            count++;
        } else {
            // If the current character is different from the next character, encode it
            while (count > 255) {
                encoded[index++] = input[i];
                // Encode the count of repeating characters in binary bytes with leading zeros
                for (int j = 7; j >= 0; j--) {
                    encoded[index++] = ((255 >> j) & 1) + '0'; // Encode count as 255
                }
                count -= 255;
            }
            encoded[index++] = input[i];
            // Encode the count of repeating characters in binary bytes with leading zeros
            for (int j = 7; j >= 0; j--) {
                encoded[index++] = ((count >> j) & 1) + '0';
            }
            count = 1;
        }
    }

    encoded[index] = '\0'; // Add null terminator to mark the end of the encoded string
    return encoded;
}

int main() {
    // Open input file
    FILE *input_file = fopen("input_file2.txt", "r");
    if (input_file == NULL) {
        fprintf(stderr, "Error opening input_file\n");
        return 1;
    }

    // Read input from file
    char input[10000]; // Assuming a maximum line length of 1000 characters
    fgets(input, sizeof(input), input_file);
    fclose(input_file);

    // Perform run-length encoding
    char* encoded = encode(input);

    // Open output file
    FILE *output_file = fopen("output_file2.txt", "w");
    if (output_file == NULL) {
        fprintf(stderr, "Error opening output_file\n");
        free(encoded); // Free memory allocated for encoded string
        return 1;
    }

    // Write encoded output to file
    fprintf(output_file, "%s\n", encoded);
    fclose(output_file);

    printf("Original string: %s\n", input);
    printf("\nEncoded string: %s\n", encoded);
    printf("\nOriginal string length=%d",strlen(input));
    printf("\nEncoded string length=%d",strlen(encoded));
    printf("\n");

    free(encoded); // Free memory allocated for encoded string

    return 0;
}
