#ifndef ABDERRAHMANE_S_BEST_DECODER_H
#define ABDERRAHMANE_S_BEST_DECODER_H

#include "decoder.c"

int utf8_to_codepoint(const unsigned char *s, int *bytes_consumed);
int* string_decoder(const char* utf8_string, int *out_length);

#endif