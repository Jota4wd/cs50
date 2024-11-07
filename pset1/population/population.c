#include <stdio.h>

int main(void)
{
	int start_s;
	int end_s;
	int years;

	start_s = 0;
	end_s = 0;
	years = 0;
	do
	{
		printf("Start size: ");
    	scanf("%d", &start_s);
	}
	while (start_s < 9);

	do
	{
		printf("End size: ");
		scanf("%d", &end_s);
	}
	while (end_s < start_s);

	while (start_s < end_s)
	{
		start_s += (start_s / 3) - (start_s / 4);
		years++;
	}

	printf("Years: %d\n", years);

	return (0);
}
