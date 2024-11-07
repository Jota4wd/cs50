#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char BASE[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
               'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

void ms_cipher(char *text, char *keys);
int check_key(const char *key);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Uso: ./substitution chave de substituição\n");
        return (1);
    }
    if (!check_key(argv[1]))
    {
        printf("Uso: ./substitution chave de substituição\n");
        return 1;
    }
    string ptext = get_string("plantext: ");
    ms_cipher(ptext, argv[1]);
    printf("ciphertext: %s\n", ptext);
    return (0);
}

void ms_cipher(char *text, char *keys)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (text[i] == BASE[j])
            {
                text[i] = tolower(keys[j]);
                break;
            }
            else if (text[i] == toupper(BASE[j]))
            {
                text[i] = toupper(keys[j]);
                break;
            }
        }
    }
}

int check_key(const char *key)
{
    int len = strlen(key);
    if (len != 26)
        return (0);

    int duplicate[26] = {0};
    for (int i = 0; i < len; i++)
    {
        if (!isalpha(key[i]))
            return (0);

        int index = tolower(key[i]) - 'a';
        if (duplicate[index])
            return (0);
        duplicate[index] = 1;
    }
    return (1);
}

