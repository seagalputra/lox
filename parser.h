#ifndef PARSER_H
#define PARSER_H

struct token {};
typedef struct token token;

struct token* scan_tokens(char* src);

#endif // !PARSER_H
