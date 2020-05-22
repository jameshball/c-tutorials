#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pointer_arithmetic.h"

char* create_command(size_t size) {
  char* command = calloc(size, sizeof(char));
  
  assert(command != NULL && "Cannot have NULL pointer.");

  return command;
}

char** create_commands(int n) {
  char** commands = calloc(n, sizeof(char*));

  assert(commands != NULL && "Cannot have NULL pointer.");

  for (int i = 0; i < n; i++) {
    commands[i] = NULL;
  }

  return commands;
}

char* get_command(size_t size) {
  printf("> ");
  char* command = create_command(size);
  fgets(command, size, stdin);

  for (int i = 0; command[i] != '\0'; i++) {
    if (command[i] == '\n') {
      command[i] = '\0';
      break;
    }
  }

  return command;
}

char** get_commands(int n, size_t size) {
  char** commands = create_commands(n);

  for (int i = 0; i < n; i++) {
    commands[i] = get_command(size);
  }

  return commands;
}

void print_commands(char **commands, int n) {
  for (int i = 0; i < n; i++) {
    printf("%s\n", commands[i]);
  }
}

void free_commands(char **commands, int n) {
  for (int i = 0; i < n; i++) {
    free(commands[i]);
  }

  free(commands);
}

int main(int argc, char **argv) {
  int n;
  size_t size;
  sscanf(argv[1], "%d", &n);
  sscanf(argv[2], "%lu", &size);

  char** commands = get_commands(n, size);
  print_commands(commands, n);
  print_command_lengths(commands, n);
  print_command_concat(commands, n);
  free_commands(commands, n);
}
