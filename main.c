#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "parser.h"

#define RL_BUFSIZE 1024

void exit_handler(int signum) {
  exit(signum);
}

void run_file(char* file_path) {
  printf("File path -> %s\n", file_path);
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
