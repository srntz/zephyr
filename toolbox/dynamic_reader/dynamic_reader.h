#ifndef DYNAMIC_READER_H
#define DYNAMIC_READER_H
#include <stdio.h>

typedef struct {
	FILE *stream;
} DynamicReader;

typedef enum {
	DYN_READER_NO_ERR = 0,
	DYN_READER_ERR_BUF_MALLOC_FAILED,
	DYN_READER_ERR_BUF_REALLOC_FAILED,
	DYN_READER_ERR_BUF_OVERFLOW,
	DYN_READER_INTERRUPT,
	DYN_READER_UNCAUGHT
} DynamicReaderErrorType;

typedef struct {
	DynamicReaderErrorType type;
	char* message;
} DynamicReaderError;

typedef struct {
	char* value;
	DynamicReaderError err;
} DynamicReaderRV;

DynamicReaderRV dyn_reader_read(DynamicReader* dr);
void dyn_reader_free_rv(DynamicReaderRV* rv);

#endif