#include <stdio.h>
#include <stdlib.h>
#include "decoder.h"
int main(int argc, char *argv[]) {
    
    if(argc < 2) {
        printf("Usage: %s <utf8_string>\n", argv[0]);
        return 1;
    }
    const char *str = argv[1];
    int length = 0;


    int *codepoints = string_decoder(str, &length);
    if (!codepoints) {
        printf("Error decoding string.\n");
        return 1;
    }

    for (int i = 0; i < length; i++) {
        printf("U+%04X\n", codepoints[i]);
    }

    free(codepoints);
    return 0;
}
