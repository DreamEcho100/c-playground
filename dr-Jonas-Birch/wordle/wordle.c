#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ResultGreen 1
#define ResultYellow 2
#define ResultRed 4

typedef char Result;
typedef Result Results[5];

bool isIn(char, char *);
Result compareChar(char, int, char *);
void compareWord(Results *, char *, char *);

bool isIn(char target, char *word) {
  while (*word) {
    if (target == *word) {
      return true;
    }
    word++;
  }

  return false;
}

Result compareChar(char guess, int index, char *word) {
  char correct = word[index];

  if (guess == correct) {
    return ResultGreen;
  }

  if (isIn(guess, word)) {
    return ResultYellow;
  }

  return ResultRed;
}

void compareWord(Results *res, char *guess, char *word) {
  int i;
  for (i = 0; i < 5; i++) {
    (*res)[i] = compareChar(guess[i], i, word);
  }
}

void Example_print_results(Results res) {
  int i;

  for (i = 0; i < 5; i++) {
    switch (res[i]) {
    case ResultGreen:
      printf("%s\n", "Green");
      break;
    case ResultYellow:
      printf("%s\n", "Yellow");
      break;
    case ResultRed:
      printf("%s\n", "Red");
      break;
    default:
      printf("Unknown: %c\n", res[i]);
      break;
    }
  }
}

int main(int argc, char *argv[]) {
  char *correct;
  char *guess;

  if (argc < 3) {
    fprintf(stderr, "USAGE: %s CORRECTWORD GUESSWORD\n", argv[0]);
    return -1;
  }

  correct = argv[1];
  guess = argv[2];

  if (strlen(correct) != 5 || strlen(guess) != 5) {
    fprintf(stderr, "ERROR: Both words must be exactly 5 letters long.\n");
    return -1;
  }

  Results res;
  compareWord(&res, guess, correct);
  Example_print_results(res);

  return 0;
}
