#ifndef TOKEN_H
#define TOKEN_H

#include "token_type.h"

typedef struct {
	TokenType type;
	char** lexeme;
	char** literal;
	int line;
} Token;

#endif