#ifndef STRING_H
#define STRING_H

typedef struct {
	char* contents;
	int buff_size;
	int length;
} String;

String* string_new(char* arr);

char string_get_char(String s, int i);
String* string_append(String* s, char* to_append);
void string_free(String* s);
int string_trim_newline(String* s);

#endif // !STRING_H

