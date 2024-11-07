void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int inicio = 0;
        int fim = width - 1;

        while (inicio < fim)
        {
            // Troca os pixels
            RGBTRIPLE temp = image[i][inicio];
            image[i][inicio] = image[i][fim];
            image[i][fim] = temp;

            // Move os índices
            inicio++;
            fim--;
        }
    }
}
