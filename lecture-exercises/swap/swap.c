#include <stdio.h>

void swap(int* p, int* q) {
  int t = *p;
  *p = *q;
  *q = t;
}

int main(void) {
  int a = 5;
  int b = 7;

  printf("Before: a = %d, b = %d", a, b);

  swap(&a, &b);

  printf("After: a = %d, b = %d", a, b);

  return 0;
}
