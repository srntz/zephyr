#include "token_list.h"
#include <stdlib.h>

TokenList token_list_init() {
	int buf_size = 16;
	int len = 0;
	Token* buff = malloc(sizeof(Token) * buf_size);
	TokenList tkl = { .contents = buff, .len = len, .buf_size = buf_size };
	return tkl;
}

int expand_buf(TokenList* tkl) {
	int new_buf_size = tkl->buf_size * 2;
	Token* new_buf = realloc(tkl->contents, sizeof(Token) * new_buf_size);
	if (new_buf == NULL) {
		return 1;
	}
	tkl->contents = new_buf;
	tkl->buf_size = new_buf_size;
	return 0;
}

int token_list_append(TokenList* tkl, Token tk) {
	if (tkl->len == tkl->buf_size) {
		int out = expand_buf(tkl);
		if (out != 0) {
			return 0;
		}
	}
	tkl->contents[tkl->len] = tk;
	tkl->len += 1;
	return 1;
}

Token* token_list_get(TokenList* tkl, int index) {
	if (index >= tkl->len) {
		return NULL;
	}
	return &(tkl->contents)[index];
}

void token_list_free(TokenList* tkl) {
	if (tkl->contents != NULL) {
		free(tkl->contents);
	}
}