#include <stdio.h>

void innocent(void) {
  for (int* p = (int*) &p; !(*p == 1 && (*p = 21)); p++);
}

int main(void) {
  const int one = 1;
  printf("Before : one + one = %d\n", one + one);

  innocent();

  printf("After: one + one = %d\n", one + one);

  if (one + one == 2) {
    printf("We live in a very boring, ordinary world.\n");
  }

  if (one + one == 42) {
    printf("Welcome to the answer to life, the universe and everything.\n");
  }

  return 0;
}
