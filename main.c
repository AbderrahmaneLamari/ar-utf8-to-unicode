#include <stdio.h>

int utf8_to_codepoint(const char *utf8_char) {
    unsigned char byte1 = utf8_char[0];
    unsigned char byte2 = utf8_char[1];

    // Check for valid 2-byte UTF-8 sequence: 110xxxxx 10xxxxxx
    if ((byte1 & 0xE0) == 0xC0 && (byte2 & 0xC0) == 0x80) {
        int codepoint = ((byte1 & 0x1F) << 6) | (byte2 & 0x3F);
        return codepoint;
    }

    // Handle other cases if needed (e.g., 3-byte Arabic Extended)
    return -1; // Invalid or unsupported
}

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