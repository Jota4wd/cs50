#include <cs50.h>
#include <stdio.h>

void ms_cipher(int key, char *str);
int ms_atoi(char *str);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return (1);
    }
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (argv[1][i] < '0' || argv[1][i] > '9')
        {
            printf("Usage: ./caesar key\n");
            return (1);
        }
    }

    string ptext = get_string("plaintext: ");
    int key = ms_atoi(argv[1]);

    ms_cipher(key, ptext);
    printf("ciphertext: %s\n", ptext);
    return (0);
}

void ms_cipher(int key, char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = (str[i] - 'A' + key) % 26 + 'A';
        else if (str[i] >= 'a' && str[i] <= 'z')
            str[i] = (str[i] - 'a' + key) % 26 + 'a';
    }
}

int ms_atoi(char *str)
{
    int result = 0;
    int signal = 1;

    while (*str)
    {
        if (*str == '-')
            signal *= -1;
        result = result * 10 + (*str - '0');
        str++;
    }
    return (result * signal);
}
