#include "token.h"
#include "token_list.h"
#include "token_type.h"
#include "string.h"
#include "stdbool.h"

typedef struct {
	char* source;
	TokenList token_list;
	int start;
	int current;
	int line;
} Tokenizer;

Tokenizer tokenizer_init(char* source) {
	Tokenizer t = { .source = source, .token_list = token_list_init(), .start = 0, .current = 0, .line = 1 };
	return t;
}

bool tokenizer_is_at_end(Tokenizer* t) {
	return (t->start >= strlen(t->source)) ? true : false;
}

Token tokenizer_scan_token(Tokenizer* t) {
	TokenType type = ENDOFF;
	Token tk = { .type = ENDOFF };
	return tk;
}

TokenList* tokenizer_tokenize(Tokenizer* t) {
	while (tokenizer_is_at_end(t) == false) {
		t->start = t->current;
		tokenizer_scan_token(t);
	}

	TokenType eof_type = ENDOFF;
	Token eof_token = { .type = eof_type };
	int err = token_list_append(&t->token_list, eof_token);
	if (err != 0) {
		return NULL;
	}
	return &t->token_list;
}