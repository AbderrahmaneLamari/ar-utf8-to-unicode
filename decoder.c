#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>

int utf8_to_codepoint(const unsigned char *s, int *bytes_consumed) {
    if ((s[0] & 0x80) == 0x00) {

        *bytes_consumed = 1;
        return s[0];
    } else if ((s[0] & 0xE0) == 0xC0) {

        *bytes_consumed = 2;
        return ((s[0] & 0x1F) << 6) | (s[1] & 0x3F);
    } else if ((s[0] & 0xF0) == 0xE0) {
        
        *bytes_consumed = 3;
        return ((s[0] & 0x0F) << 12) | ((s[1] & 0x3F) << 6) | (s[2] & 0x3F);
    }

    *bytes_consumed = 1;
    return -1; // Invalid or unsupported sequence
}

int* string_decoder(const char* utf8_string, int *out_length) {
    int capacity = 16; // Start with some space
    int *codepoints = malloc(capacity * sizeof(int));
    if (!codepoints) return NULL;

    int length = 0;
    int i = 0;

    while (utf8_string[i] != '\0') {
        int bytes = 0;
        int cp = utf8_to_codepoint((const unsigned char *)&utf8_string[i], &bytes);

        if (cp == -1) {
            free(codepoints);
            return NULL;
        }

        if (length >= capacity) {
            capacity *= 2;
            int *new_codepoints = realloc(codepoints, capacity * sizeof(int));
            if (!new_codepoints) {
                free(codepoints);
                return NULL;
            }
            codepoints = new_codepoints;
        }

        codepoints[length++] = cp;
        i += bytes;
    }

    *out_length = length;
    return codepoints;
}
