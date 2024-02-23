#ifndef ERROR_H
#define ERROR_H

#include <stdbool.h>

extern bool had_error;

void error(int line, char* msg);
void report(int line, char* where, char* msg);

#endif
