#include <stdio.h>
#include <ctype.h>

#define GUESS_LENGTH 4
#define CODES_LENGTH 5

int another_game(void) {
  char answer[256];

  do {
    printf("Do you want to play another game?\n");
    scanf("%s", answer);
  } while (!(tolower(answer[0]) == 'y' || tolower(answer[0]) == 'n'));

  return answer[0] == 'y';
}

void read_guess(int guess[GUESS_LENGTH]) {
  printf("Enter your guess:\n");
  scanf("%i %i %i %i", &guess[0], &guess[1], &guess[2], &guess[3]);
}

int black_score(int guess[GUESS_LENGTH], int code[GUESS_LENGTH]) {
  int score = 0;

  for (int i = 0; i < GUESS_LENGTH; i++) {
    if (code[i] == guess[i]) {
      score++;
    }
  }

  return score;
}

int white_score(int guess[GUESS_LENGTH], int code[GUESS_LENGTH]) {
  int score = 0;

  for (int i = 0; i < GUESS_LENGTH; i++) {
    for (int j = 0; j < GUESS_LENGTH; j++) {
      if (i != j && code[i] == guess[j]) {
        score++;
      }
    }
  } 

  return score;
}

void print_score(int guess[GUESS_LENGTH], int code[GUESS_LENGTH]) {
  printf("(%i,%i)\n", black_score(guess, code), white_score(guess, code));
}

int main(void) {
  int codes[CODES_LENGTH][GUESS_LENGTH] = {{1, 8, 9, 2}, {2, 4, 6, 8}, {1, 9, 8, 3}, {7, 4, 2, 1}, {4, 6, 8, 9}};

  for (int i = 0; i < CODES_LENGTH; i++) {
    int guess[GUESS_LENGTH];
    read_guess(guess);

    while (black_score(guess, codes[i]) != GUESS_LENGTH) {
      print_score(guess, codes[i]);
      read_guess(guess);
    }

    printf("You have guessed correctly!\n");
    if (i < CODES_LENGTH - 1) {
      if (!another_game()) {
        return 0;
      }
    }
  }  

  return 0;
}
