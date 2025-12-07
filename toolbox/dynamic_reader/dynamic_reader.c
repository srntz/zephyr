#include "dynamic_reader.h"
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

DynamicReaderError init_error(DynamicReaderErrorType type, char* message) {
	DynamicReaderError dre = { .type = type, .message = message };
	return dre;
}

/*
Reads a line from the stream passed within DynamicReader. The function can read
lines with lengths up to INT_MAX.
The callee is responsible for freeing the value returned by the function (see dyn_reader_free_rv).
*/
DynamicReaderRV dyn_reader_read(DynamicReader* dr) {
	DynamicReaderRV rv = { .value = NULL, .err = init_error(DYN_READER_NO_ERR, "")};

	int size = 5;
	size_t len = 0;

	char* buff = malloc(sizeof(char) * size);
	if (buff == NULL) {
		rv.err = init_error(
			DYN_READER_ERR_BUF_MALLOC_FAILED, 
			"Failed to allocate memory for the string buffer."
		);
		goto error;
	}

	// fgets() intakes buffer count as 'int' but strlen() returns 'size_t'.
	// This block returns an error if len is not safe to cast to 'int'.
	if (len > INT_MAX) {
		rv.err = init_error(
			DYN_READER_ERR_BUF_OVERFLOW, 
			"Buffer length exceeded the maximum value of 'int'."
		);
		goto error;
	}

	// read max of size - len bytes and write them to the empty portion of the buffer.
	if (fgets(buff + len, size - (int)len, dr->stream) == NULL) {
		if (errno == EINTR) {
			rv.err = init_error(
				DYN_READER_INTERRUPT, 
				"SIGINT Found."
			);
		}
		else {
			rv.err = init_error(
				DYN_READER_UNCAUGHT, 
				"Uncaught error occured."
			);
		}
		goto error;
	}

	len = strlen(buff);

	// increase the buffer size and read the remaining bytes from the stream until
	// the end of line.
	while (len <= size && buff[len - 1] != '\n' && buff[len - 1] != '\0') {
		size *= 2;
		char* new_buff = realloc(buff, size);
		if (new_buff == NULL) {
			char message_buff[100];
			sprintf(message_buff, "Failed to reallocate memory for the string buffer with size '%d'", size);
			rv.err = init_error(DYN_READER_ERR_BUF_REALLOC_FAILED, message_buff);
			goto error;
		}
		buff = new_buff;
		if (len > INT_MAX) {
			rv.err = init_error(
				DYN_READER_ERR_BUF_OVERFLOW, 
				"Buffer length exceeded the maximum value of 'int'."
			);
			goto error;
		}
		if (fgets(buff + len, size - (int)len, stdin) == NULL) {
			if (errno == EINTR) {
				rv.err = init_error(
					DYN_READER_INTERRUPT,
					"SIGINT Found."
				);
			}
			else {
				rv.err = init_error(
					DYN_READER_UNCAUGHT,
					"Uncaught error occured."
				);
			}
			goto error;
		}
		len = strlen(buff);
	}

	rv.value = buff;
	return rv;

error:
	free(buff);
	return rv;
}

/*
Frees the memory allocated to the fields of the given DynamicReaderRV.
*/
void dyn_reader_free_rv(DynamicReaderRV* rv) {
	if (rv->value != NULL) {
		free(rv->value);
	}
}