#include <stdio.h>
#include "decoder.h"


int main(int argc, char** argv){

    if (argc < 2) {
        printf("Usage: %s <utf8_char>\n", argv[0]);
        return 1;
    }

    const char *utf8_char = argv[1];
    int codepoint = utf8_to_codepoint(utf8_char);
    if (codepoint != -1) {
        printf("Codepoint: U+%04X\n", codepoint);
    } else {
        printf("Invalid or unsupported UTF-8 character.\n");
    }
}