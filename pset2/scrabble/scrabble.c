#include <cs50.h>
#include <stdio.h>

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
char LETTERS[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                  'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

void ms_lowcase(string word);
int compute_score(string word);

int main(void)
{
    string player1 = get_string("Player1: ");
	string player2 = get_string("Player2: ");

	ms_lowcase(player1);
	ms_lowcase(player2);
	int score1 = compute_score(player1);
	int score2 = compute_score(player2);
	
	if (score1 > score2)
		printf("Player 1 wins!\n");
	else if (score2 > score1)
		printf("Player 2 wins!\n");
	else
		printf("Tie!");
	return (0);
}

int compute_score(string word)
{
	int i = 0;
	int score = 0;

	while (word[i] != '\0')
	{
		for (int j = 0; j < 26; j++)
		{
			if (word[i] == LETTERS[j])
			{
				score += POINTS[j];
				break ;
			}
		}
		i++;
	}
	return (score);
}

void ms_lowcase(string word)
{
	int i = 0;
	while (word[i] != '\0')
	{
		if (word[i] >= 'A' && word[i] <= 'Z')
			word[i] = word[i] + 32;
		i++;
	}
}
