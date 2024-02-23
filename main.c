#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "parser.h"

#define RL_BUFSIZE 1024

void exit_handler(int signum) {
  exit(signum);
}

void run_file(char* file_path) {
  FILE* src = NULL;
  char* buff = NULL;
  unsigned long fsize;
  
  src = fopen(file_path, "rb");
  if (src == NULL) {
  	fprintf(stderr, "lox: unable to open file");
  	exit(EXIT_FAILURE);
  }

  // calculate the size of the inputted file
  fseek(src, 0, SEEK_END);
  fsize = ftell(src);
  rewind(src);

  buff = (char*)malloc(fsize);
  if (buff == NULL) {
  	fprintf(stderr, "lox: allocation error\n");
  	fclose(src);
  	exit(EXIT_FAILURE);
  }

  if (fread(buff, 1, fsize, src) != fsize) {
  	fprintf(stderr, "lox: error reading file\n");
  	fclose(src);
  	free(buff);
  	exit(EXIT_FAILURE);
  }

  fclose(src);

  // TODO: do something with the saved buffer
  printf("Contents of the file:\n%s\n", buff);

  free(buff);
}

char* read_line() {
  int bufsize = RL_BUFSIZE;
  int pos = 0;
  int c;
  char* buff = malloc(sizeof(char) * bufsize);

  if (!buff) {
    fprintf(stderr, "lox: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    c = getchar();

    if (c == EOF || c == '\n') {
      buff[pos] = '\0';

      return buff;
    } else {
      buff[pos] = c;
    }

    pos++;

    if (pos >= bufsize) {
      // incline the size of the buffer
      bufsize += RL_BUFSIZE;
      buff = realloc(buff, bufsize);

      if (!buff) {
        fprintf(stderr, "lox: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

void run_prompt() {
  // do loop for getting user input
  char* buff = NULL;
  
  do {
    printf("lox> ");
    buff = read_line();

    printf("User input -> %s\n", buff);

    free(buff);
  } while (signal(SIGTERM, exit_handler) != SIG_ERR);
}

int main(int argc, char *argv[]) {
  if (argc > 2) {
    printf("Usage: clox [script]\n");
    return 64;
  } else if (argc == 2) {
    // running a lox file
    char* path = argv[1];
    run_file(path);
  } else {
    // spawn a REPL or execute a code immidiately
    run_prompt();
  }
  
  return EXIT_SUCCESS;
}
