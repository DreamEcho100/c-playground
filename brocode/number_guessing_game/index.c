#include <stdio.h>

#include "../get_random_int/index.h"

void number_guessing_game()
{
	int min = 1;
	int max = 100;
	// The number to guess is between 1 and 100
	// If we don't add 1 to the max, the number to guess will be between 0 and 99
	// Because get_random_int() % max will return a number between 0 and max - 1
	int random_num = (get_random_int() % max) + min;
	int guessed_num = 0;

	printf("Guess the number!\n");
	printf("Enter your guess: \n");
	while (random_num != guessed_num)
	{
		printf("_(Remember, the number is between %d and %d.)_\n", min, max);
		scanf("%d", &guessed_num);
		if (guessed_num < random_num)
		{
			printf(":(, you guessed too low\n");
		}
		else if (guessed_num > random_num)
		{
			printf(":(, you guessed too high\n");
		}
		else if (guessed_num == random_num)
		{
			printf(":), Congratulations! You guessed the number!\n");
			break;
		}
		printf("Try again!\n");
	}
}