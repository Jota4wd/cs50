#include <cs50.h>
#include <stdio.h>

void ms_coleman_liau(int letters, int words, int sentence);
int ms_round(float nbr);
int ms_strlen(string str);

int main(void)
{
    string text = get_string("Text: ");
    int i = 0;
    int letters = 0;
    int words = 0;
    int in_word = 0;
    int sentences = 0;

    while (text[i] != '\0')
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            if (in_word == 0)
            {
                in_word = 1;
                words++;
            }
            letters++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
            sentences++;
        else if (text[i] == ' ')
            in_word = 0;
        i++;
    }
    ms_coleman_liau(letters, words, sentences);
    return (0);
}

void ms_coleman_liau(int letters, int words, int sentences)
{
    float l = (float) letters / words * 100;
    float s = (float) sentences / words * 100;
    float index = 0.0588 * l - 0.296 * s - 15.8;
    int rank = ms_round(index);

    if (rank > 16)
        printf("Grade 16+\n");
    else if (rank < 1)
        printf("Before Grade 1\n");
    else
        printf("Grade %d\n", rank);
}

int ms_round(float nbr)
{
    int interger = (int) nbr;
    float decimal = nbr - interger;

    if (decimal >= 0.5)
        return (interger + 1);
    else
        return (interger);
}
