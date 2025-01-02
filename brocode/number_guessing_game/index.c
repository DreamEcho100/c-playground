#include <stdio.h>

#include "../get_random_int/index.h"

void number_guessing_game()
{
	int random_num = get_random_int() % 100;
	int guessed_num = 0;

	printf("Guess the number!\n");
	printf("Enter your guess: \n");
	while (random_num != guessed_num)
	{
		printf("_(Remember, the number is between 0 and 100.)_\n");
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