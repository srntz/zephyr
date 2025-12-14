#include "tokenizer/tokenizer.h"
#include "error/error.h"
#include "token/token_type.h"
#include "../spec_helpers.h"
#include <stdio.h>
#include <stdlib.h>

void init_tokenizer(char* source, Tokenizer *t);
void test_token_types(char *source, TokenType expected_types[], int expected_types_len);

void test_binary_ops(void);
void test_bang_tokens(void);
void test_tokens_starting_with_less(void);
void test_tokens_starting_with_greater(void);
void test_tokens_starting_with_equal(void);
void test_token_ampersand_ampersand(void);
void test_token_ampersand_unknown(void);
void test_token_pipe_pipe(void);
void test_token_pipe_unknown(void);

int main(void) {
    IT("should correctly tokenize binary operators and ignore whitespace", &test_binary_ops);
    IT("should correctly tokenize tokens starting with '!'", &test_bang_tokens);
    IT("should correctly tokenize tokens starting with '<'", &test_tokens_starting_with_less);
    IT("should correctly tokenize tokens starting with '<'", &test_tokens_starting_with_greater);
    IT("should correctly tokenize tokens starting with '='", &test_tokens_starting_with_equal);
    IT("should correctly tokenize '&&'", &test_token_ampersand_ampersand);
    IT("should return an unknown token error when '&' is encountered", &test_token_ampersand_unknown);
    IT("should correctly tokenize '||'", &test_token_pipe_pipe);
    IT("should return an unknown token error when '|' is encountered", &test_token_pipe_unknown);
}

void test_binary_ops(void) {
    char* s = "+  - <> ";
    TokenType expected_types[] = {PLUS, MINUS, LESS, GREATER};
    int expected_types_len = 4;

    test_token_types(s, expected_types, expected_types_len);
}

void test_bang_tokens(void) {
    char *s = "  !  !=  ";
    TokenType expected_types[] = {BANG, BANG_EQUAL};
    int expected_types_len = 2;

    test_token_types(s, expected_types, expected_types_len);
}

void test_tokens_starting_with_less(void) {
    char *s = "  <=   <  ";
    TokenType expected_types[] = {LESS_EQUAL, LESS};
    int expected_types_len = 2;

    test_token_types(s, expected_types, expected_types_len);
}

void test_tokens_starting_with_greater(void) {
    char *s = "  >=   >  ";
    TokenType expected_types[] = {GREATER_EQUAL, GREATER};
    int expected_types_len = 2;

    test_token_types(s, expected_types, expected_types_len);
}

void test_tokens_starting_with_equal(void) {
    char *s = "  ==   =  ";
    TokenType expected_types[] = {EQUAL_EQUAL, EQUAL};
    const int expected_types_len = 2;

    test_token_types(s, expected_types, expected_types_len);
}

void test_token_ampersand_ampersand(void) {
    char *s = "  && ";
    TokenType expected_types[] = {AMPERSAND_AMPERSAND};
    const int expected_types_len = 1;

    test_token_types(s, expected_types, expected_types_len);
}

void test_token_ampersand_unknown(void) {
    char *s = "  & ";
    Tokenizer t = {};
    init_tokenizer(s, &t);

    Error err = tokenizer_tokenize(&t);
    ASSERT_BOOL_EQ(is_error(&err), true);
    ASSERT_INT_EQ(err.err_code, ERR_TOKENIZER_UNKNOWN_TOKEN);
}

void test_token_pipe_pipe(void) {
    char *s = "  || ";
    TokenType expected_types[] = {PIPE_PIPE};
    const int expected_types_len = 1;

    test_token_types(s, expected_types, expected_types_len);
}

void test_token_pipe_unknown(void) {
    char *s = "  | ";
    Tokenizer t = {};
    init_tokenizer(s, &t);

    Error err = tokenizer_tokenize(&t);
    ASSERT_BOOL_EQ(is_error(&err), true);
    ASSERT_INT_EQ(err.err_code, ERR_TOKENIZER_UNKNOWN_TOKEN);
}

void test_token_types(char *source, TokenType expected_types[], const int expected_types_len) {
    Tokenizer t = {};
    init_tokenizer(source, &t);

    Error err = tokenizer_tokenize(&t);
    ASSERT_BOOL_EQ(is_error(&err), false);

    ASSERT_INT_EQ(t.token_list.len, expected_types_len + 1);
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