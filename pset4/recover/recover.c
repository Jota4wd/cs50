#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usage: ./recover file.raw\n");
        return 1;
    }

    FILE *infile = fopen(argv[1], "r");

    if (infile == NULL)
    {
        fprintf(stderr, "nao foi possivel abrir %s.\n", argv[1]);
        return 1;
    }

    char filename[8];
    int jpg_count = 0;
    FILE *outfile = NULL;
    BYTE buffer[BLOCK_SIZE];

    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, infile) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && (buffer[3] & 0xF0) == 0xE0)
        {
            if (outfile != NULL)
                fclose(outfile);

            sprintf(filename, "%03d.jpg", jpg_count++);
            outfile = fopen(filename, "w");
        }

        if (outfile != NULL)
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, outfile);
    }

    if (outfile != NULL)
        fclose(outfile);

    fclose(infile);
    return 0;
}
