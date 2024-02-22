#include <stdio.h>

#include "parser.h"

void run_file(char* file_path) {
	printf("File path -> %s", file_path);
}

void run_prompt() {}

int main(int argc, char *argv[]) {
	if (argc > 2) {
		printf("Usage: clox [script]");
		return 64;
	} else if (argc == 2) {
		// running a lox file
		char* path = argv[1];
		run_file(path);
	} else {
		// spawn a REPL or execute a code immidiately
		run_prompt();
	}
	
	return 0;
}
