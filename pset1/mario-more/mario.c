#include <stdio.h>

int	main(void)
{
	int	altura;

	do
	{
		printf("altura: ");
		scanf("%d", &altura);
	}
	while (altura < 1 || altura > 8);
	for (int linha = 1; linha <= altura; linha++)
	{
		for (int espaco = altura - linha; espaco > 0; espaco--)
			printf(" ");
		for (int tijolo = 0; tijolo < linha; tijolo++)
			printf("#");
		printf("  ");
		for (int tijolo = 0; tijolo < linha; tijolo++)
			printf("#");
		printf("\n");
	}
	return (0);
}
