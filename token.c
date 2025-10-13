#include "token_type.h"

typedef struct {
	TokenType type;
	char** lexeme;
	char** literal;
	int line;
} Token;