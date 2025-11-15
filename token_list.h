#ifndef TOKEN_LIST_H
#define TOKEN_LIST_H

#include "token.h"
#include "error.h"

typedef struct {
	Token* contents;
	int len;
	int buf_size;
} TokenList;

Error token_list_init(TokenList* out_tkl);
Error token_list_append(TokenList* tkl, Token tk);
void token_list_free(TokenList* tkl);

#endif