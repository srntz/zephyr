#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include "token_type.h"
#include "toolbox/string.h"
#include "toolbox/dynamic_reader/dynamic_reader.h"

char *EXEC_CONSOLE = "console";
char *EXEC_RUN = "run";

int console(int argc, char** argv) {
	printf("> ");

	DynamicReader dr = { .stream = stdin };
	DynamicReaderRV input = dyn_reader_read(&dr);
	while (input.err.type != DYN_READER_ERR_BUF_MALLOC_FAILED && input.value != NULL) {
		String* s = string_new(input.value);
		string_trim_newline(s);

		if (!strcmp(s->contents, "!quit")) {
			printf("\nClosing session...");
			dyn_reader_free_rv(&input);
			return 0;
		}

		printf("STRING CONTENTS: %s\n", s->contents);
		printf("STRING LEN: %d\n", s->length);

		dyn_reader_free_rv(&input);
		string_free(s);

		printf("> ");
		input = dyn_reader_read(&dr);
	}

	printf("\n\nClosing session...");
	exit(0);
}

int run(int argc, char** argv) {
	printf("Running files is not supported... yet.");
	exit(1);
}

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Usage:\n");
		return 0;
	}

	char** shifted_argv = NULL;
	int shifted_argc = 0;
	if (argc > 2) {
		shifted_argv = &argv[2];
		shifted_argc = argc - 2;
	}

	char* command = argv[1];
	if (strcmp(command, EXEC_CONSOLE) == 0) {
		console(shifted_argc, shifted_argv);
		return 0;
	}

	if (strcmp(command, EXEC_RUN) == 0) {
		run(shifted_argc, shifted_argv);
		return 0;
	}

	printf("Unknown command '%s'", command);
	return 0;
}