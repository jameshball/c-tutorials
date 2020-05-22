#include <stdio.h>
#include <stdlib.h>
#include "pointer_arithmetic.h"

int string_length(char *str) {
  char *str_orig = str;
  for (; *str != '\0'; str++);

  return str - str_orig + 1;
}

char *string_cat(char *str1, char *str2) {
  char *concat = calloc(string_length(str1) + string_length(str2) - 1, sizeof(char));

  int i;

  for (i = 0; i < string_length(str1) - 1; i++) {
    concat[i] = str1[i];
  }

  for (int j = 0; j < string_length(str2); j++) {
    concat[i + j] = str2[j];
  }

  return concat;
}

void print_command_lengths(char **commands, int n) {
  for (int i = 0; i < n; i++) {
    printf("%s: %d\n", commands[i], string_length(commands[i]));
  }
}

void print_command_concat(char **commands, int n) {
  char *concat = commands[0];

  for (int i = 1; i < n; i++) {
    concat = string_cat(concat, commands[i]);
  }

  printf("%s\n", concat);
}
