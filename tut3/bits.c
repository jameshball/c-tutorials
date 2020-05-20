#include <stdio.h>
#include <stdint.h>

void print_bits(uint32_t n) {
  uint32_t mask = 1 << 31;

  for (int i = 0; i < 32; i++) {
    printf("%d", (n & mask) != 0);

    if (i == 15) {
      printf(" ");
    }

    n >>= 1;
  }

  printf("\n");
}

void print_bits_16(uint16_t n) {
  uint16_t mask = 1 << 15;

  for (int i = 0; i < 16; i++) {
    printf("%d", (n & mask) != 0);
    mask >>= 1;
  }

  printf("\n");
}

int main(void) {
  uint32_t n = 1288243249;
  uint16_t first = n >> 16;
  uint16_t second = n;

  print_bits(n);
  print_bits_16(first);
  print_bits_16(second);
  
  int16_t signedFirst = first;
  printf("Signed: %d, Unsigned: %u\n", signedFirst, first);

  first <<= 1;
  signedFirst = first;
  printf("Signed: %d, Unsigned: %u\n", signedFirst, first);

  print_bits_16(first);
  print_bits_16(signedFirst);

  return 0;
}
