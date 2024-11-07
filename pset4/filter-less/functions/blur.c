void blur(int height, int width, RGBTRIPLE image[height][width])
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redSum = 0, greenSum = 0, blueSum = 0;
            int count = 0;

            // Verifica os pixels vizinhos
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Verifica se o pixel vizinho está dentro dos limites da imagem
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        redSum += image[ni][nj].rgbtRed;
                        greenSum += image[ni][nj].rgbtGreen;
                        blueSum += image[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calcula a média e arredonda
            temp[i][j].rgbtRed = round(redSum / (float)count);
            temp[i][j].rgbtGreen = round(greenSum / (float)count);
            temp[i][j].rgbtBlue = round(blueSum / (float)count);
        }
    }

    // Copia os valores da matriz temporária de volta para a imagem original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}
