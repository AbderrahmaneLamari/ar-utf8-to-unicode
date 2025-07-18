#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int utf8_to_codepoint(const unsigned char *s, int *bytes_consumed) {
    if ((s[0] & 0x80) == 0x00) {
        *bytes_consumed = 1;
        return s[0];
    } else if ((s[0] & 0xE0) == 0xC0) {
        *bytes_consumed = 2;
        return ((s[0] & 0x1F) << 6) |
               (s[1] & 0x3F);
    } else if ((s[0] & 0xF0) == 0xE0) {
        *bytes_consumed = 3;
        return ((s[0] & 0x0F) << 12) |
               ((s[1] & 0x3F) << 6) |
               (s[2] & 0x3F);
    } else if ((s[0] & 0xF8) == 0xF0) {
        *bytes_consumed = 4;
        return ((s[0] & 0x07) << 18) |
               ((s[1] & 0x3F) << 12) |
               ((s[2] & 0x3F) << 6) |
               (s[3] & 0x3F);
    }

    *bytes_consumed = 1;
    return -1; // Invalid sequence
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


void decode_line(const char *line, FILE* file) {
    int chapter = 0, aya = 0;
    const char *verse_start = NULL;

    // Use sscanf to get chapter and aya
    if (sscanf(line, "%d|%d|", &chapter, &aya) != 2) {
        fprintf(stderr, "❌ Invalid input format: %s\n", line);
        return;
    }

    // Now find the verse text part
    const char *third_pipe = strchr(line, '|'); // first '|'
    if (third_pipe) third_pipe = strchr(third_pipe + 1, '|'); // second '|'
    if (!third_pipe || *(third_pipe + 1) == '\0') {
        fprintf(stderr, "❌ Missing verse text: %s\n", line);
        return;
    }

    verse_start = third_pipe + 1;

    fprintf(file, "c:%d#a:%d", chapter, aya);

    const unsigned char *ptr = (const unsigned char *)verse_start;
    int i = 0;
    while (ptr[i]) {
        int bytes = 0;
        int cp = utf8_to_codepoint(&ptr[i], &bytes);
        if (cp == -1) {
            printf("\n⚠️ Invalid UTF-8 at byte %d\n", i);
            break;
        }
        fprintf(file, "U+%04X", cp);
        i += bytes;
    }
    fprintf(file, "\n");
}