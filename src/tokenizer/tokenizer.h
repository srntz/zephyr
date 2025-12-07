#ifndef ZEPHYR_TOKENIZER_H
#define ZEPHYR_TOKENIZER_H

#include "token/token_list.h"
#include <stddef.h>

typedef struct {
    char* source;
    TokenList token_list;
    size_t start;
    size_t current;
    int line;
} Tokenizer;

Error tokenizer_init(char* source, Tokenizer *t);
Error tokenizer_tokenize(Tokenizer *t);
void tokenizer_free(Tokenizer *t);

#endif //ZEPHYR_TOKENIZER_H