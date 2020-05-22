#include <stdio.h>
#include <stdlib.h>

int string_length(char *str) {
  char *str_orig = str;
  for (; *str != '\0'; str++);

  return str - str_orig;
}


