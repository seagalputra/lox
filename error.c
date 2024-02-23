#include "error.h"

#include <stdio.h>

void error(int line, char* msg) {
	report(line, "", msg);
}

void report(int line, char* where, char* msg) {
	fprintf(stderr, "[line %d] Error %s: %s", line, where, msg);
	had_error = true;
}
