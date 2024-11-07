/* Fórmulas para o Efeito Sepia */
/* As fórmulas para calcular os novos valores de RGB ao aplicar o efeito sépia são as seguintes: */
/* Sepia Red: */
/* sepiaRed */
/* = */
/* 0.393 */
/* × */
/* originalRed */
/* + */
/* 0.769 */
/* × */
/* originalGreen */
/* + */
/* 0.189 */
/* × */
/* originalBlue */
/* sepiaRed=0.393×originalRed+0.769×originalGreen+0.189×originalBlue */
/* Sepia Green: */
/* sepiaGreen */
/* = */
/* 0.349 */
/* × */
/* originalRed */
/* + */
/* 0.686 */
/* × */
/* originalGreen */
/* + */
/* 0.168 */
/* × */
/* originalBlue */
/* sepiaGreen=0.349×originalRed+0.686×originalGreen+0.168×originalBlue */
/* Sepia Blue: */
/* sepiaBlue */
/* = */
/* 0.272 */
/* × */
/* originalRed */
/* + */
/* 0.534 */
/* × */
/* originalGreen */
/* + */
/* 0.131 */
/* × */
/* originalBlue */
/* sepiaBlue=0.272×originalRed+0.534×originalGreen+0.131×originalBlue */

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            int sepiaRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            int sepiaGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            int sepiaBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);

            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
        }
    }
}
