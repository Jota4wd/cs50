#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_person
{
	string name;
	string phone;
} t_person;

void ms_insertion_sort(t_person *list, int len);

int main(int argc, char **argv)
{
	int len;

	if (argc > 2)
	{
		printf("usage: ./phonebook length");
		return (1);
	}
	else if (argc == 2)
		len = atoi(argv[1]);
	else
		len = get_int("length list: ");
	if (len <= 0)
	{
		printf("usage: ./phonebook length");
		return (1);
	}

	t_person phonebook[len];
	for (int i = 0; i < len; i++)
	{
		phonebook[i].name = get_string("Name: ");
		phonebook[i].phone = get_string("Phone: ");
	}
	ms_insertion_sort(phonebook, len);
	for (int i = 0; i < len; i++)
		printf("%s -> %s.\n", phonebook[i].name, phonebook[i].phone);
	return (0);
}

void ms_insertion_sort(t_person *list, int len)
{
	t_person temp;

	for (int i = 1; i < len; i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (strcmp(list[j].name, list[j - 1].name) < 0)
			{
				temp = list[j - 1];
				list[j - 1] = list[j];
				list[j] = temp;
			}
			else
				break ;
		}
	}
}

