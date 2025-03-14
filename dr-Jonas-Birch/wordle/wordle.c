// Stopped at [02:38:28]
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define TOTAL_WORDS_SIZE 5195
#define WORD_LENGTH 6 // including the `\0` at the end
#define WORDS_FILE_PATH "wordlist.txt"

typedef char Result;
typedef Result Results[WORD_LENGTH];
typedef struct s_words {
  char arr[TOTAL_WORDS_SIZE][WORD_LENGTH];
  int n;
} Words;

typedef enum { ResultRed = 4, ResultYellow = 2, ResultGreen = 1 } ResultColor;

bool charInWord(const char target, const char *word);
Result compareChar(const char guess, int index, const char *word);
void compareWord(Results *res, const char *guess, const char *word);
void Example_print_results(Results res);
void seedWords(const char *filname, Words *words);
void seedRandomWord(char *randomWord, Words *words);

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

Result compareChar(const char guess, int index, const char *word) {
  char correct = word[index];

  if (guess == correct) {
    return ResultGreen;
  }

  if (charInWord(guess, word)) {
    return ResultYellow;
  }

  return ResultRed;
}

void compareWord(Results *res, const char *guess, const char *word) {
  int i;
  for (i = 0; i < WORD_LENGTH; i++) {
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

  // Alt:
  // ```c
  // const char *resultStrings[] = {"Red", "Yellow", NULL, NULL, "Green"};
  //
  // for (int i = 0; i < WORD_LENGTH; i++) {
  //   if (res[i] < 0 || res[i] > ResultGreen || resultStrings[res[i]] == NULL)
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

  int i = 0;
  while (fgets(buf, WORD_LENGTH + 1, fd) && i < TOTAL_WORDS_SIZE) {

    int size = strlen(buf);
    // printf("size: %d\n", size);
    // printf("WORD_LENGTH: %d\n", WORD_LENGTH);
    // break;

    if (size > 0 && buf[size - 1] == '\n') {
      buf[size - 1] = '\0'; // Remove newline
    }

    if (size != WORD_LENGTH) { // Expecting only 5 letters
      printf("Skipping malformed word: '%s' (size: %d)\n", buf, size);
      continue;
    }

    // strncpy(words->arr[i], buf, WORD_LENGTH);
    memcpy(words->arr[i], buf, WORD_LENGTH);
    i++;
  }

  // Alt:
  // ```c
  // memset(buf, 0, READ_FILE_BUF_LINE_SIZE);
  // while (fgets(buf, WORD_LENGTH + 1, fd) && i < max) {
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
  //     words->arr[i][j] = buf[j];
  //   }
  //   words->arr[i][WORD_LENGTH] = 0;
  //
  //   memset(buf, 0, READ_FILE_BUF_LINE_SIZE);
  //
  //   i++;
  // }
  // ```

  if (ferror(fd)) {
    perror("Error reading file");
  }

  fclose(fd);

  // words->arr = ret;
  words->n = i;
}

void seedRandomWord(char *randomWord, Words *words) {
  unsigned int seed = time(NULL);
  int randomIndex = rand_r(&seed) % TOTAL_WORDS_SIZE;
  strncpy(randomWord, words->arr[randomIndex], WORD_LENGTH);
}

int main(int argc, char *argv[]) {
  // char wordsArr[WORDS_ARR_LV1_SIZE][WORDS_ARR_LV2_SIZE] = {0};
  Words words = {
      .arr = {{0}},
      .n = 0,
  };
  // Alt: `memset(&words, 0, sizeof(Words));`

  seedWords(WORDS_FILE_PATH, &words);

  if (!words.n) {
    printf("Failed\n");
  } else {
    printf("n: %d\n", words.n);
    printf("nr: 100: '%s'\n", words.arr[99]);

    char randomWord[WORD_LENGTH];
    seedRandomWord(randomWord, &words);
    printf("Random word: %s\n", randomWord);
  }

  return 0;
}
