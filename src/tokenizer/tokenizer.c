#include "tokenizer.h"

#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "stdbool.h"
#include "string.h"
#include "token/token.h"
#include "token/token_list.h"

bool is_at_end(const Tokenizer *t);
char advance(Tokenizer *t);
char peek(const Tokenizer *t);
void append_single_char_token(Tokenizer *t, TokenType type, char* lexeme, int line);
Error unknown_token_error(const char *lexeme, size_t lexeme_len);
Error scan_token(Tokenizer *t);

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
		Error err;

		t->start = t->current;

		err = scan_token(t);
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

Error scan_token(Tokenizer* t) {
	const char c = advance(t);

	switch (c) {
		case '+': {
			append_single_char_token(t, PLUS, "+", t->line);
			break;
		}
		case '-': {
			append_single_char_token(t, MINUS, "-", t->line);
			break;
		}
		case '*': {
			append_single_char_token(t, STAR, "*", t->line);
			break;
		}
		case '/': {
			append_single_char_token(t, SLASH, "/", t->line);
			break;
		}
		case '<': {
			if (!is_at_end(t) && peek(t) == '=') {
				append_single_char_token(t, LESS_EQUAL, "<=", t->line);
				advance(t);
			} else {
				append_single_char_token(t, LESS, "<", t->line);
			}
			break;
		}
		case '>': {
			if (!is_at_end(t) && peek(t) == '=') {
				append_single_char_token(t, GREATER_EQUAL, ">=", t->line);
				advance(t);
			} else {
				append_single_char_token(t, GREATER, ">", t->line);
			}
			break;
		}
		case '(': {
			append_single_char_token(t, LEFT_PAREN, "(", t->line);
			break;
		}
		case ')': {
			append_single_char_token(t, RIGHT_PAREN, ")", t->line);
			break;
		}
		case '{': {
			append_single_char_token(t, LEFT_BRACE, "{", t->line);
			break;
		}
		case '}': {
			append_single_char_token(t, RIGHT_BRACE, "}", t->line);
			break;
		}
		case '.': {
			append_single_char_token(t, DOT, ".", t->line);
			break;
		}
		case ',': {
			append_single_char_token(t, COMMA, ", ", t->line);
			break;
		}
		case ';': {
			append_single_char_token(t, SEMICOLON, ";", t->line);
			break;
		}
		case '!': {
			if (!is_at_end(t) && peek(t) == '=') {
				append_single_char_token(t, BANG_EQUAL, "!=", t->line);
				advance(t);
			} else {
				append_single_char_token(t, BANG, "!", t->line);
			}
			break;
		}
		case '=': {
			if (!is_at_end(t) && peek(t) == '=') {
				append_single_char_token(t, EQUAL_EQUAL, "==", t->line);
				advance(t);
			} else {
				append_single_char_token(t, EQUAL, "=", t->line);
			}
			break;
		}
		case '&': {
			if (is_at_end(t) || peek(t) != '&') {
				return unknown_token_error(&c, 1);
			}
			append_single_char_token(t, AMPERSAND_AMPERSAND, "&&", t->line);
			advance(t);
			break;
		}
		case '|': {
			if (is_at_end(t) || peek(t) != '|') {
				return unknown_token_error(&c, 1);
			}
			append_single_char_token(t, PIPE_PIPE, "||", t->line);
			advance(t);
			break;
		}
		case ' ': {
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

Error unknown_token_error(const char *lexeme, const size_t lexeme_len) {
	const size_t buf_size = 50 + lexeme_len;
	char buf[buf_size];
	snprintf(buf, buf_size, "Unknown token '%s'", lexeme);
	return (Error){.err_code = ERR_TOKENIZER_UNKNOWN_TOKEN, .err_msg = buf};
}

void append_single_char_token(Tokenizer *t, const TokenType type, char* lexeme, const int line) {
	Token tk = {.type = type, .lexeme = lexeme, .line = line};
	token_list_append(&t->token_list, tk);
}

bool is_at_end(const Tokenizer* t) {
	return (t->current >= strlen(t->source)) ? true : false;
}

char advance(Tokenizer *t) {
	const char c = t->source[t->current];
	t->current++;
	return c;
}

char peek(const Tokenizer *t) {
	return t->source[t->current];
}

void tokenizer_free(Tokenizer* t) {
	if (t != NULL) {
		token_list_free(&t->token_list);
	}
}