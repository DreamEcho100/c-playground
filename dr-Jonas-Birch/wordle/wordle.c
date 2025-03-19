// Stopped at [03:35:25]
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define TOTAL_WORDS_SIZE 5195
#define WORD_LENGTH 5
#define WORDS_FILE_PATH "wordlist.txt"

typedef struct s_words {
  char arr[TOTAL_WORDS_SIZE][WORD_LENGTH + 1];
  int n;
} Words;

#define ClrGreen "\033[32m"
#define ClrYellow "\033[33m"
#define ClrRed "\033[31m"
#define clrStop "\033[0m"

typedef enum { ResultRed = 4, ResultYellow = 2, ResultGreen = 1 } ResultColor;
typedef enum { ValOK = 0, ValBadInput = 1, ValNoSuchWord = 2 } ValStatus;
typedef struct game_config {
  bool continuation;
  bool hasWon;
  int rounds;
  bool corrects[WORD_LENGTH];
  char correctWord[WORD_LENGTH + 1];
  Words words;
  // int turns;
} GameConfig;

bool charInWord(const char target, const char *word);
char compareChar(GameConfig *gameConfig, const char guess, int index,
                 const char *word);
void compareWord(GameConfig *gameConfig, char *res, const char *guess,
                 const char *word);
void print_results(char *res, const char *guess, char *correct);
void seedWords(const char *filname, Words *words);
void seedRandomWord(GameConfig *gameConfig);
void readLine(char buf[WORD_LENGTH + 3]);
void gameLoop(GameConfig *gameConfig);
void prompt(GameConfig *gameConfig);
ValStatus validator(GameConfig *gameConfig, char *word);

// We can use `strchr(word, target) != NULL` instead
// The following is on;y for learning purposes
bool charInWord(const char target, const char *word) {
  while (*word) {
    if (target == *word) {
      return true;
    }
    word++;
  }

  return false;
}

char compareChar(GameConfig *gameConfig, const char guess, int index,
                 const char *word) {
  char correct = word[index];

  if (guess == correct) {
    gameConfig->corrects[index] = true;
    return ResultGreen;
  }

  gameConfig->corrects[index] = false;

  if (charInWord(guess, word)) {
    return ResultYellow;
  }

  return ResultRed;
}

void compareWord(GameConfig *gameConfig, char *res, const char *guess,
                 const char *word) {
  int i;
  for (i = 0; i < WORD_LENGTH; i++) {
    res[i] = compareChar(gameConfig, guess[i], i, word);
  }
}
void prompt(GameConfig *gameConfig) {

  printf("  ");
  for (int i = 0; i < WORD_LENGTH; i++) {
    printf("%c", gameConfig->corrects[i] ? 'o' : 'x');

    // if (gameConfig->corrects[i]) {
    //   printf("%c", gameConfig->corrects[i]);
    //   continue;
    // }

    // printf("-");
  }
  printf("\n\n> ");
  fflush(stdout);
}

void print_results(char *res, const char *guess, char *correct) {
  int i;

  for (i = 0; i < 5; i++) {
    switch (res[i]) {
    case ResultGreen:
      printf("%s%c%s", ClrGreen, guess[i], clrStop);
      break;
    case ResultYellow:
      printf("%s%c%s", ClrYellow, guess[i], clrStop);
      break;
    case ResultRed:
      printf("%s%c%s", ClrRed, guess[i], clrStop);
      break;
    default:
      printf("Unknown: %c\n", res[i]);
      break;
    }
  }
  printf("\n");

  // Alt:
  // ```c
  // const char *resultStrings[] = {"Red", "Yellow", NULL, NULL, "Green"};
  //
  // for (int i = 0; i < WORD_LENGTH; i++) {
  //   if (res[i] < 0 || res[i] > ResultGreen || resultStrings[res[i]] ==
  //   NULL)
  //   {
  //     printf("Unknown: %d\n", res[i]);
  //   } else {
  //     printf("%s\n", resultStrings[res[i]]);
  //   }
  // }
  // ```
}

#define READ_FILE_BUF_LINE_SIZE (WORD_LENGTH + 2)
// #define READ_FILE_BUF_WORD_SIZE 7
void seedWords(const char *filPath, Words *words) {
  char buf[READ_FILE_BUF_LINE_SIZE] = {0};
  FILE *fd = fopen(filPath, "r");

  if (!fd) {
    perror("fopen");
    return;
  }

  // nylon\n\0
  // 01234 5 6
  words->n = 0;
  while (fgets(buf, WORD_LENGTH + 2, fd) && words->n < TOTAL_WORDS_SIZE) {

    int size = strlen(buf);
    // printf("size: %d\n", size);
    // printf("WORD_LENGTH: %d\n", WORD_LENGTH);
    // break;

    if (size > 0 && buf[size - 1] == '\n') {
      buf[size - 1] = '\0'; // Remove newline
      size--;
    }

    if (size != WORD_LENGTH) { // Expecting only 5 letters
      printf("Skipping malformed word: '%s' (size: %d)\n", buf, size);
      continue;
    }

    // strncpy(words->arr[words->n], buf, WORD_LENGTH);
    memcpy(words->arr[words->n], buf, WORD_LENGTH);
    words->n++;
  }

  // Alt:
  // ```c
  // memset(buf, 0, READ_FILE_BUF_LINE_SIZE);
  // while (fgets(buf, WORD_LENGTH + 1, fd) && words->n < max) {
  //   int size = strlen(buf);
  //
  //   if (size < 1) {
  //     memset(buf, 0, READ_FILE_BUF_LINE_SIZE);
  //     continue;
  //   }
  //
  //   size--;
  //   buf[size] = 0;
  //
  //   if (size != 5) {
  //     memset(buf, 0, READ_FILE_BUF_LINE_SIZE);
  //     continue;
  //   }
  //
  //   int j = 0;
  //   for (; j < WORD_LENGTH; j++) {
  //     words->arr[words->n][j] = buf[j];
  //   }
  //   words->arr[words->n][WORD_LENGTH] = 0;
  //
  //   memset(buf, 0, READ_FILE_BUF_LINE_SIZE);
  //
  //   words->n++;
  // }
  // ```

  if (ferror(fd)) {
    perror("Error reading file");
  }

  fclose(fd);

  // words->arr = ret;
  if (words->n == 0) {
    fprintf(stderr, "No valid words loaded. Exiting.\n");
    exit(EXIT_FAILURE);
  }
}

void readLine(char buf[WORD_LENGTH + 3]) {
  int size;

  memset(buf, 0, WORD_LENGTH + 3);
  // fgets(buf, WORD_LENGTH + 2, stdin);
  if (!fgets(buf, WORD_LENGTH + 2, stdin)) {
    printf("\nInput closed. Exiting game.\n");
    exit(0);
  }

  size = strlen(buf);
  assert(size > 0);
  if (buf[size - 1] == '\n') {
    buf[size - 1] = '\0';
  }

  // char temp[WORD_LENGTH + 1];
  // if (sscanf(buf, "%5s", temp) == 1) {
  //   memcpy(buf, temp, WORD_LENGTH);
  // }
}

void seedRandomWord(GameConfig *gameConfig) {
  unsigned int seed = time(NULL);
  int randomIndex = rand_r(&seed) % gameConfig->words.n;
  strncpy(gameConfig->correctWord, gameConfig->words.arr[randomIndex],
          WORD_LENGTH);
}

ValStatus validator(GameConfig *gameConfig, char *word) {
  int n;
  int i;

  n = strlen(word);

  if (n != 5) {
    return ValBadInput;
  }

  bool isFound = false;

  for (i = 0; i < TOTAL_WORDS_SIZE; i++) {
    if (!strncmp(gameConfig->words.arr[i], word, WORD_LENGTH)) {
      isFound = true;
      break;
    }
  }

  if (isFound) {
    return ValOK;
  }

  return ValNoSuchWord;
}

void gameLoop(GameConfig *gameConfig) {
  char input[WORD_LENGTH + 3];
  char res[WORD_LENGTH] = {0};

  gameConfig->rounds++;

  readLine(input);
  compareWord(gameConfig, res, input, gameConfig->correctWord);
  prompt(gameConfig);

  gameConfig->hasWon = true;

  for (int i = 0; i < WORD_LENGTH; i++) {
    if (!gameConfig->corrects[i]) {
      gameConfig->hasWon = false;
    }
  }

  if (gameConfig->hasWon || gameConfig->rounds >= 4) {
    gameConfig->continuation = false;
    return;
  }
}

int main(int argc, char *argv[]) {
  // char wordsArr[WORDS_ARR_LV1_SIZE][WORDS_ARR_LV2_SIZE] = {0};

  GameConfig gameConfig = {
      .words = {.n = 0, .arr = {{0}}},
      .rounds = 0,
      .corrects = {false},
      .correctWord = {0},
      .continuation = true,
      .hasWon = false,
      // .turns = 0,
  };

  seedWords(WORDS_FILE_PATH, &gameConfig.words);

  assert(!(gameConfig.words.n < 0));

  seedRandomWord(&gameConfig);
  printf("cw: %s\n", gameConfig.correctWord);

  printf("-----\n\n> ");
  fflush(stdout);

  while (gameConfig.continuation) {
    gameLoop(&gameConfig);
  }

  printf("Correct word: %s\n", gameConfig.correctWord);
  if (gameConfig.hasWon) {
    printf("Congratulations! You won!\n");
  } else {
    printf("You lost. Better luck next time!\n");
  }

  return 0;
}
