#include "string.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const int STRING_STD_BUFF_SIZE = 64;

char string_get_char(String s, int i) {
	if (i >= 0 && i < s.length) {
		return s.contents[i];
	}
	return '\0';
}

String* string_new(char* arr) {
	String* s = malloc(sizeof(String));
	if (s == NULL) {
		return NULL;
	}

	int len = strlen(arr);

	// Create a buffer with a default size (STRING_STD_BUFF_SIZE) or a size that's
	// big enough to store the given string.
	int buff_size_from_input = sizeof(char) * len + 1;
	int buff_size = buff_size_from_input > STRING_STD_BUFF_SIZE ? buff_size_from_input : STRING_STD_BUFF_SIZE;
	char* m_arr = malloc(buff_size);
	if (m_arr == NULL) {
		return NULL;
	}

	strcpy(m_arr, arr);

	s->contents = m_arr;
	s->length = len;
	s->buff_size = buff_size;
	return s;
}

String *string_append(String* s, char* to_append) {
	int length = strlen(to_append);
	// Increase the size of the buffer to be able to carry the concatenated string + the null terminator.
	while (s->length + length + 1 > s->buff_size) {
		s->buff_size = s->buff_size * 2;
		char* tmp = realloc(s->contents, s->buff_size);
		if (tmp == NULL) {
			printf("Could not reallocate space for string.");
			exit(1);
		}
		s->contents = tmp;
	}

	strcpy(s->contents + s->length, to_append);
	s->length = s->length + length;

	return s;
}

int string_trim_newline(String* s) {
	if (s->length > 0 && s->contents[s->length - 1] == '\n') {
		s->contents[s->length - 1] = '\0';
		return 1;
	}
	return 0;
}

void string_free(String* s) {
	free(s->contents);
	free(s);
}