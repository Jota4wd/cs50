#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int	main(void)
{
	float	troco;
	int		centavos;
	int		moedas;
	char	buffer[100];

	moedas = 0;
	do
	{
		printf("Change owed: ");
		fgets(buffer, sizeof(buffer), stdin);
		char *endptr;
		troco = strtof(buffer, &endptr);
		if (endptr != buffer && *endptr == '\n' && troco > 0)
			break;
	} while (endptr == buffer || *endptr != '\n' || troco <= 0);

	centavos = round(troco * 100);
	while (centavos > 0)
	{
		if (centavos >= 25)
			centavos -= 25;
		else if (centavos >= 10)
			centavos -= 10;
		else if (centavos >= 5)
			centavos -= 5;
		else
			centavos -= 1;

		moedas++;
	}

	printf("%d\n", moedas);
	return (0);
}

/* formatado para uso da ide cs50 online

#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    float troco;
    int centavos;
    int moedas = 0;

    do
    {
        troco = get_float("Change owed: ");
    }
    while (troco <= 0);

    centavos = round(troco * 100);

    while (centavos > 0)
    {
        if (centavos >= 25)
            centavos -= 25;
        else if (centavos >= 10)
            centavos -= 10;
        else if (centavos >= 5)
            centavos -= 5;
        else
            centavos -= 1;
        moedas++;
    }

    printf("%d\n", moedas);

    return (0);
}
*/
