#include <stdio.h>
#include <stdlib.h>

char *create_command(size_t size) {
  return (char*) calloc(size, sizeof(char));
}

char **create_commands(int n) {
  char **commands = calloc(n, sizeof(char*));

  for (int i = 0; i < n; i++) {
    commands[i] = NULL;
  }

  return commands;
}

char *get_command(size_t size) {
  printf("> ");
  char *command = create_command(size);
  scanf("%s", command);

  return command;
}

char **get_commands(int n, size_t size) {
  char **commands = create_commands(n);

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
  sscanf(argv[1], "%d", &n);
  size_t size;
  sscanf(argv[2], "%lu", &size);

  char **commands = get_commands(n, size);
  print_commands(commands, n);
  free_commands(commands, n);
}
