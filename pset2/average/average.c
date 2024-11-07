#include <cs50.h>
#include <stdio.h>

const int TOTAL = 3;

float ms_media(int len, int array[]);

int main(void)
{
    int notas[3];

    for (int i = 0; i < TOTAL; i++)
        notas[i] = get_int("Nota: ");

    printf("Media %.2f\n", ms_media(TOTAL, notas));
    return(0);
}

float ms_media(int len, int array[])
{
    int sum = 0;

    for (int i = 0; i < len; i++)
        sum += array[i];

    return (sum / (float)len);
}
