#include <stdio.h>
#include <stdlib.h>
#include "decoder.h"


int main() {
    FILE *file = fopen("quran-simple.txt", "r");
    FILE* output_file = fopen("decoded_output.txt", "w");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    char line[4096]; // Buffer to hold each line (adjust size if needed)

    while (fgets(line, sizeof(line), file)) {
        // Remove trailing newline if present
        // line[strcspn(line, "\n")] = '\0';

        // Now you can process the line
        decode_line(line, output_file);
    }

    fclose(file);
    return 0;
}