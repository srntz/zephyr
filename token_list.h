#ifndef TOKEN_LIST_H
#define TOKEN_LIST_H

#include "token.h"

typedef struct {
	Token* contents;
	int len;
	int buf_size;
} TokenList;

TokenList token_list_init();
int token_list_append(TokenList* tkl, Token tk);
void token_list_free(TokenList* tkl);

#endif