void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}
