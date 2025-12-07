#include "token.h"
#include "token_list.h"
#include "error.h"
#include <malloc.h>

/*
	Initializes a new empty TokenList.

	The TokenList itself is owned by the callee but the internal buffer is allocated by this function.
	Calling token_list_free() is required before letting go of the token list to free this internal buffer.

	Returns ERR_ALLOC_FAILED if the function couldn't allocate the internal buffer.
*/
Error token_list_init(TokenList* out_tkl) {
	int buf_size = 16;
	int len = 0;

	Token* buff = malloc(sizeof(Token) * buf_size);
	if (buff == NULL) {
		Error err = { .err_code = ERR_ALLOC_FAILED, .err_msg = "Could not allocate the Token buffer" };
		return err;
	}

	out_tkl->contents = buff;
	out_tkl->len = len;
	out_tkl->buf_size = buf_size;

	return NOERR;
}

Error expand_buf(TokenList* tkl) {
	int new_buf_size = tkl->buf_size * 2;
	Token* new_buf = realloc(tkl->contents, sizeof(Token) * new_buf_size);
	if (new_buf == NULL) {
		Error err = { .err_code = ERR_ALLOC_FAILED, .err_msg = "Failed to allocate more space to the Token buffer." };
		return err;
	}
	tkl->contents = new_buf;
	tkl->buf_size = new_buf_size;
	return NOERR;
}

/*
	Appends a new Token to the list.

	Returns ERR_ALLOC_FAILED if the buffer failed to be expanded to fit the new token.
*/
Error token_list_append(TokenList* tkl, Token tk) {
	if (tkl->len == tkl->buf_size) {
		Error err = expand_buf(tkl);
		if (err.err_code != NO_ERR) {
			return err;
		}
	}
	tkl->contents[tkl->len] = tk;
	tkl->len += 1;
	return NOERR;
}

/*
	Grabs a Token at the given index.

	Returns ERR_INDEX_OUT_OF_BOUNDS if the given index violates the bounds of the buffer.
*/
Error token_list_get(TokenList* tkl, int index, Token *out_token) {
	if (index < 0 || index >= tkl->len) {
		Error err = {
			.err_code = ERR_INDEX_OUT_OF_BOUNDS,
			.err_msg = "Cannot access the Token at the given index"
		};
		return err;
	}
	out_token->type = tkl->contents[index].type;
	return NOERR;
}

/*
	De-allocates the internal buffer of a TokenList.
	This function MUST be called before the TokenList is de-allocated or goes out of scope.
*/
void token_list_free(TokenList* tkl) {
	if (tkl->contents != NULL) {
		free(tkl->contents);
	}
}