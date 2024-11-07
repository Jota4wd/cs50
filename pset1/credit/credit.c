#include <cs50.h>
#include <stdio.h>

int ms_digits(long nbr);
int ms_luhn(long nbr);
int ms_operadoras(long nbr);

int main(void)
{
	long nbr;
	int luhn;
	int operadora;

	do
	{
		nbr = get_long("cartao: ");
	}
	while (nbr < 1);
	luhn = ms_luhn(nbr);
	operadora = ms_operadoras(nbr);
	if (luhn == 0 || operadora == 0)
		printf("INVALID\n");
	else if (operadora == 1)
		printf("AMEX\n");
	else if (operadora == 2)
		printf("MASTERCARD\n");
	else if (operadora == 3)
		printf("VISA\n");
	return (0);
}

int ms_digits(long nbr)
{
	int qty;

	qty = 0;
	while (nbr > 0)
	{
		qty++;
		nbr /= 10;
	}
	return (qty);
}

int ms_luhn(long nbr)
{
	int multiplos;
	int simples;
	int digit;
	int total;

	multiplos = 0;
	simples = 0;
	while (nbr > 0)
	{
		simples += nbr % 10;
		nbr = nbr / 10;
		digit = (nbr % 10) * 2;
		if (digit > 9)
			digit = (digit % 10) + ((digit / 10) % 10);
		multiplos += digit;
		nbr = nbr / 10;
	}
	total = multiplos + simples;
	if (total % 10 == 0)
		return (1);
	else
		return (0);
}

int ms_operadoras(long nbr)
{
	int len;

	len = ms_digits(nbr);
	while (nbr >= 100)
		nbr /= 10;
	if ((nbr == 34 || nbr == 37) && len == 15)
		return (1);
	else if ((nbr >= 51 && nbr <= 55) && len == 16)
		return (2);
	else if ((nbr >= 40 && nbr <= 49) && (len == 13 || len == 16))
		return (3);
	else
		return (0);
}
