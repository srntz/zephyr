#ifndef ERROR_H
#define ERROR_H

#include <stdbool.h>

typedef enum {
	NO_ERR,
	ERR_ALLOC_FAILED,
	ERR_INDEX_OUT_OF_BOUNDS,
} ErrorCode;

typedef struct {
	ErrorCode err_code;
	char* err_msg;
} Error;

#define NOERR ((Error){0, NULL});

bool is_error(Error* err);

#endif