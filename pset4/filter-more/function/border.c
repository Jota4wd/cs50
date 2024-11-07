// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    // Máscaras de Sobel para detecção de bordas
    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] = {
        {1, 2, 1},
        {0, 0, 0},
        {-1, -2, -1}
    };

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redX = 0, greenX = 0, blueX = 0;
            int redY = 0, greenY = 0, blueY = 0;

            // Aplica a máscara de Sobel
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Verifica se o pixel vizinho está dentro dos limites da imagem
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        redX += image[ni][nj].rgbtRed * Gx[di + 1][dj + 1];
                        greenX += image[ni][nj].rgbtGreen * Gx[di + 1][dj + 1];
                        blueX += image[ni][nj].rgbtBlue * Gx[di + 1][dj + 1];

                        redY += image[ni][nj].rgbtRed * Gy[di + 1][dj + 1];
                        greenY += image[ni][nj].rgbtGreen * Gy[di + 1][dj + 1];
                        blueY += image[ni][nj].rgbtBlue * Gy[di + 1][dj + 1];
                    }
                }
            }

            // Calcula a magnitude da borda
            int red = round(sqrt(redX * redX + redY * redY));
            int green = round(sqrt(greenX * greenX + greenY * greenY));
            int blue = round(sqrt(blueX * blueX + blueY * blueY));

            // Limita os valores a 255
            temp[i][j].rgbtRed = (red > 255) ? 255 : red;
            temp[i][j].rgbtGreen = (green > 255) ? 255 : green;
            temp[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
        }
    }

    // Copia os valores das bordas de volta para a imagem original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}
