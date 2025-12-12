#include "tokenizer/tokenizer.h"
#include "error/error.h"
#include "token/token_type.h"
#include "../spec_helpers.h"
#include <stdio.h>
#include <stdlib.h>

void init_tokenizer(char* source, Tokenizer *t);
void test_binary_ops(void);

int main(void) {
    IT("should correctly tokenize binary operators and ignore whitespace", &test_binary_ops);
}

void test_binary_ops(void) {
    char* s = "+  - <> ";
    TokenType expected_types[] = {PLUS, MINUS, LESS, GREATER};
    int expected_types_len = 4;

    Tokenizer t = {};
    init_tokenizer(s, &t);

    tokenizer_tokenize(&t);

    ASSERT_INT_EQ(t.token_list.len, 5);
    for (int i = 0; i < expected_types_len; i++) {
        ASSERT_INT_EQ(t.token_list.contents[i].type, expected_types[i]);
    }

    tokenizer_free(&t);
}

void init_tokenizer(char* source, Tokenizer *t) {
    Error err = tokenizer_init(source, t);
    if (is_error(&err)) {
        printf("%s", err.err_msg);
        exit(1);
    }
}