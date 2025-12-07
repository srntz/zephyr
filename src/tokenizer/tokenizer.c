#include "tokenizer.h"

#include <stdlib.h>

#include "error.h"
#include "stdbool.h"
#include "string.h"
#include "token/token.h"
#include "token/token_list.h"

bool is_at_end(Tokenizer *t);
char advance(Tokenizer *t);
void fillin_single_char_token(Token *tk, TokenType type, char* lexeme, int line);
Error scan_token(Tokenizer *t, Token *tk);

Error tokenizer_init(char* source, Tokenizer* t) {
	TokenList tkl;

	Error err = token_list_init(&tkl);
	if (is_error(&err)) {
		return err;
	}

	t->source = source;
	t->token_list = tkl;
	t->line = 1;
	t->current = 0;
	t->start = 0;

	return NOERR;
}

Error tokenizer_tokenize(Tokenizer* t) {
	while (is_at_end(t) == false) {
		Token tk;
		Error err;

		t->start = t->current;

		err = scan_token(t, &tk);
		if (is_error(&err)) {
			return err;
		}

		err = token_list_append(&t->token_list, tk);
		if (is_error(&err)) {
			return err;
		}
	}

	Error err = token_list_append(&t->token_list, (Token){.type = ENDOFF});
	if (is_error(&err)) {
		return err;
	}

	return NOERR;
}

Error scan_token(Tokenizer* t, Token *tk) {
	const char c = advance(t);

	switch (c) {
		case '+': {
			fillin_single_char_token(tk, PLUS, "+", t->line);
			break;
		}
		case '-': {
			fillin_single_char_token(tk, MINUS, "-", t->line);
			break;
		}
		case '*': {
			fillin_single_char_token(tk, STAR, "*", t->line);
			break;
		}
		case '/': {
			fillin_single_char_token(tk, SLASH, "/", t->line);
			break;
		}
		case '<': {
			fillin_single_char_token(tk, LESS, "<", t->line);
			break;
		}
		case '>': {
			fillin_single_char_token(tk, GREATER, ">", t->line);
			break;
		}
		case '(': {
			fillin_single_char_token(tk, LEFT_PAREN, "(", t->line);
			break;
		}
		case ')': {
			fillin_single_char_token(tk, RIGHT_PAREN, ")", t->line);
			break;
		}
		case '{': {
			fillin_single_char_token(tk, LEFT_BRACE, "{", t->line);
			break;
		}
		case '}': {
			fillin_single_char_token(tk, RIGHT_BRACE, "}", t->line);
			break;
		}
		case '.': {
			fillin_single_char_token(tk, DOT, ".", t->line);
			break;
		}
		case ',': {
			fillin_single_char_token(tk, COMMA, ", ", t->line);
			break;
		}
		case ';': {
			fillin_single_char_token(tk, SEMICOLON, ";", t->line);
			break;
		}
		case '!': {
			fillin_single_char_token(tk, BANG, "!", t->line);
			break;
		}
		case '=': {
			fillin_single_char_token(tk, EQUAL, "=", t->line);
			break;
		}
		default: {
			Error err;
			err.err_code = ERR_TOKENIZER_UNKNOWN_TOKEN;
			err.err_msg = "Unknown token";
			return err;
		}
	}

	return NOERR;
}

void fillin_single_char_token(Token *tk, TokenType type, char* lexeme, int line) {
	tk->type = type;
	tk->lexeme = lexeme;
	tk->literal = NULL;
	tk->line = line;
}

bool is_at_end(Tokenizer* t) {
	return (t->current >= strlen(t->source)) ? true : false;
}

char advance(Tokenizer *t) {
	const char c = t->source[t->current];
	t->current++;
	return c;
}

void tokenizer_free(Tokenizer* t) {
	if (t != NULL) {
		token_list_free(&t->token_list);
	}
}