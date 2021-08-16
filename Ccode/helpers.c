#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculates the mean of RGB in each pixel
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);

            // replace the initial number of R, G, B to the mean of RGB of each pixel
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
    //
    return;
}

// Reflect image horizontally

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    if (width % 2 == 0)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width / 2; j++)
            {
                // apply swap function to 2 pixels horizontally symmetric
                RGBTRIPLE tmp = image[i][j];
                image[i][j] = image[i][width - j - 1];
                image[i][width - j - 1] = tmp;
            }
        }
    }
    else
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < (width - 1) / 2; j++)
            {
                // apply swap function to 2 pixels horizontally symmetric
                RGBTRIPLE tmp = image[i][j];
                image[i][j] = image[i][width - j - 1];
                image[i][width - j - 1] = tmp;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE ximage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ximage[i][j] = image[i][j];
        }
    }
    for (int x = 1; x < height - 1; x++)
    {
        for (int y = 1; y < width - 1; y++)
        {
            // calculate the mean of each pixel's neighbor pixels
            image[x][y].rgbtRed = round((ximage[x][y].rgbtRed + ximage[x - 1][y - 1].rgbtRed + ximage[x][y - 1].rgbtRed +
                                         ximage[x - 1][y].rgbtRed + ximage[x + 1][y].rgbtRed + ximage[x + 1][y + 1].rgbtRed +
                                         ximage[x][y + 1].rgbtRed + ximage[x - 1][y + 1].rgbtRed +
                                         ximage[x + 1][y - 1].rgbtRed) / 9.0);
            image[x][y].rgbtGreen = round((ximage[x][y].rgbtGreen + ximage[x - 1][y - 1].rgbtGreen +
                                           ximage[x][y - 1].rgbtGreen + ximage[x - 1][y].rgbtGreen +
                                           ximage[x + 1][y].rgbtGreen + ximage[x + 1][y + 1].rgbtGreen +
                                           ximage[x][y + 1].rgbtGreen + ximage[x - 1][y + 1].rgbtGreen + 
                                           ximage[x + 1][y - 1].rgbtGreen) / 9.0);
            image[x][y].rgbtBlue = round((ximage[x][y].rgbtBlue + ximage[x - 1][y - 1].rgbtBlue +
                                          ximage[x][y - 1].rgbtBlue + ximage[x - 1][y].rgbtBlue + ximage[x + 1][y].rgbtBlue +
                                          ximage[x + 1][y + 1].rgbtBlue + ximage[x][y + 1].rgbtBlue +
                                          ximage[x - 1][y + 1].rgbtBlue + ximage[x + 1][y - 1].rgbtBlue) / 9.0);
        }
    }
    image[0][0].rgbtRed = round((ximage[0][0].rgbtRed + ximage[1][0].rgbtRed + ximage[1][1].rgbtRed +
                                 ximage[0][1].rgbtRed) / 4.0);
    image[0][0].rgbtGreen = round((ximage[0][0].rgbtGreen + ximage[1][0].rgbtGreen + ximage[1][1].rgbtGreen +
                                   ximage[0][1].rgbtGreen) / 4.0);
    image[0][0].rgbtBlue = round((ximage[0][0].rgbtBlue + ximage[1][0].rgbtBlue + ximage[1][1].rgbtBlue +
                                  ximage[0][1].rgbtBlue) / 4.0);
    image[height - 1][width - 1].rgbtRed = round((ximage[height - 1][width - 1].rgbtRed +
                                                  ximage[height - 2][width - 2].rgbtRed +
                                                  ximage[height - 2][width - 1].rgbtRed +
                                                  ximage[height - 1][width - 2].rgbtRed) / 4.0);
    image[height - 1][width - 1].rgbtGreen = round((ximage[height - 1][width - 1].rgbtGreen +
                                                    ximage[height - 2][width - 2].rgbtGreen +
                                                    ximage[height - 2][width - 1].rgbtGreen +
                                                    ximage[height - 1][width - 2].rgbtGreen) / 4.0);
    image[height - 1][width - 1].rgbtBlue = round((ximage[height - 1][width - 1].rgbtBlue +
                                                   ximage[height - 2][width - 2].rgbtBlue +
                                                   ximage[height - 2][width - 1].rgbtBlue +
                                                   ximage[height - 1][width - 2].rgbtBlue) / 4.0);
    image[height - 1][0].rgbtRed = round((ximage[height - 1][0].rgbtRed + ximage[height - 2][0].rgbtRed +
                                          ximage[height - 2][1].rgbtRed + ximage[height - 1][1].rgbtRed) / 4.0);
    image[height - 1][0].rgbtGreen = round((ximage[height - 1][0].rgbtGreen + ximage[height - 2][0].rgbtGreen +
                                            ximage[height - 2][1].rgbtGreen + ximage[height - 1][1].rgbtGreen) / 4.0);
    image[height - 1][0].rgbtBlue = round((ximage[height - 1][0].rgbtBlue + ximage[height - 2][0].rgbtBlue +
                                           ximage[height - 2][1].rgbtBlue + ximage[height - 1][1].rgbtBlue) / 4.0);
    image[0][width - 1].rgbtRed = round((ximage[0][width - 1].rgbtRed + ximage[0][width - 2].rgbtRed +
                                         ximage[1][width - 2].rgbtRed + ximage[1][width - 1].rgbtRed) / 4.0);
    image[0][width - 1].rgbtGreen = round((ximage[0][width - 1].rgbtGreen + ximage[0][width - 2].rgbtGreen +
                                           ximage[1][width - 2].rgbtGreen + ximage[1][width - 1].rgbtGreen) / 4.0);
    image[0][width - 1].rgbtBlue = round((ximage[0][width - 1].rgbtBlue + ximage[0][width - 2].rgbtBlue +
                                          ximage[1][width - 2].rgbtBlue + ximage[1][width - 1].rgbtBlue) / 4.0);
    for (int i = 1; i < width - 1; i++)
    {
        image[0][i].rgbtRed = round((ximage[0][i].rgbtRed + ximage[0][i - 1].rgbtRed + ximage[0][i + 1].rgbtRed +
                                     ximage[1][i - 1].rgbtRed + ximage[1][i].rgbtRed + ximage[1][i + 1].rgbtRed) / 6.0);
        image[0][i].rgbtGreen = round((ximage[0][i].rgbtGreen + ximage[0][i - 1].rgbtGreen + ximage[0][i + 1].rgbtGreen +
                                       ximage[1][i - 1].rgbtGreen + ximage[1][i].rgbtGreen + ximage[1][i + 1].rgbtGreen) / 6.0);
        image[0][i].rgbtBlue = round((ximage[0][i].rgbtBlue + ximage[0][i - 1].rgbtBlue + ximage[0][i + 1].rgbtBlue +
                                      ximage[1][i - 1].rgbtBlue + ximage[1][i].rgbtBlue + ximage[1][i + 1].rgbtBlue) / 6.0);
    }
    for (int i = 1; i < width - 1; i++)
    {
        image[height - 1][i].rgbtRed = round((ximage[height - 1][i].rgbtRed + ximage[height - 1][i - 1].rgbtRed +
                                              ximage[height - 1][i + 1].rgbtRed + ximage[height - 2][i - 1].rgbtRed +
                                              ximage[height - 2][i].rgbtRed + ximage[height - 2][i + 1].rgbtRed) / 6.0);
        image[height - 1][i].rgbtGreen = round((ximage[height - 1][i].rgbtGreen + ximage[height - 1][i - 1].rgbtGreen +
                                                ximage[height - 1][i + 1].rgbtGreen + ximage[height - 2][i - 1].rgbtGreen +
                                                ximage[height - 2][i].rgbtGreen + ximage[height - 2][i + 1].rgbtGreen) / 6.0);
        image[height - 1][i].rgbtBlue = round((ximage[height - 1][i].rgbtBlue + ximage[height - 1][i - 1].rgbtBlue +
                                               ximage[height - 1][i + 1].rgbtBlue + ximage[height - 2][i - 1].rgbtBlue +
                                               ximage[height - 2][i].rgbtBlue + ximage[height - 2][i + 1].rgbtBlue) / 6.0);
    }
    for (int i = 1; i < height - 1; i++)
    {
        image[i][0].rgbtRed = round((ximage[i][0].rgbtRed + ximage[i - 1][0].rgbtRed + ximage[i + 1][0].rgbtRed +
                                     ximage[i - 1][1].rgbtRed + ximage[i][1].rgbtRed + ximage[i + 1][1].rgbtRed) / 6.0);
        image[i][0].rgbtGreen = round((ximage[i][0].rgbtGreen + ximage[i - 1][0].rgbtGreen + ximage[i + 1][0].rgbtGreen +
                                       ximage[i - 1][1].rgbtGreen + ximage[i][1].rgbtGreen + ximage[i + 1][1].rgbtGreen) / 6.0);
        image[i][0].rgbtBlue = round((ximage[i][0].rgbtBlue + ximage[i - 1][0].rgbtBlue + ximage[i + 1][0].rgbtBlue +
                                      ximage[i - 1][1].rgbtBlue + ximage[i][1].rgbtBlue + ximage[i + 1][1].rgbtBlue) / 6.0);
    }
    for (int i = 1; i < height - 1; i++)
    {
        image[i][width - 1].rgbtRed = round((ximage[i][width - 1].rgbtRed + ximage[i - 1][width - 1].rgbtRed +
                                             ximage[i + 1][width - 1].rgbtRed + ximage[i - 1][width - 2].rgbtRed +
                                             ximage[i][width - 2].rgbtRed + ximage[i + 1][width - 2].rgbtRed) / 6.0);
        image[i][width - 1].rgbtGreen = round((ximage[i][width - 1].rgbtGreen + ximage[i - 1][width - 1].rgbtGreen +
                                               ximage[i + 1][width - 1].rgbtGreen + ximage[i - 1][width - 2].rgbtGreen +
                                               ximage[i][width - 2].rgbtGreen + ximage[i + 1][width - 2].rgbtGreen) / 6.0);
        image[i][width - 1].rgbtBlue = round((ximage[i][width - 1].rgbtBlue + ximage[i - 1][width - 1].rgbtBlue +
                                              ximage[i + 1][width - 1].rgbtBlue + ximage[i - 1][width - 2].rgbtBlue +
                                              ximage[i][width - 2].rgbtBlue + ximage[i + 1][width - 2].rgbtBlue) / 6.0);
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE xy[height + 2][width + 2];
    
    // set data for xy
    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            xy[i][j].rgbtRed = image[i - 1][j - 1].rgbtRed;
            xy[i][j].rgbtGreen = image[i - 1][j - 1].rgbtGreen;
            xy[i][j].rgbtBlue = image[i - 1][j - 1].rgbtBlue;
        }
    }
    for (int i = 1; i < height + 1; i++)
    {
        xy[i][0].rgbtRed = 0;
        xy[i][0].rgbtGreen = 0;
        xy[i][0].rgbtBlue = 0;
    }
    for (int i = 1; i < height + 1; i++)
    {
        xy[i][width + 1].rgbtRed = 0;
        xy[i][width + 1].rgbtGreen = 0;
        xy[i][width + 1].rgbtBlue = 0;
    }
    for (int i = 1; i < width + 1; i++)
    {
        xy[0][i].rgbtRed = 0;
        xy[0][i].rgbtGreen = 0;
        xy[0][i].rgbtBlue = 0;
    }
    for (int i = 1; i < width + 1; i++)
    {
        xy[height + 1][i].rgbtRed = 0;
        xy[height + 1][i].rgbtGreen = 0;
        xy[height + 1][i].rgbtBlue = 0;
    }
    xy[0][0].rgbtRed = 0;
    xy[0][0].rgbtGreen = 0;
    xy[0][0].rgbtBlue = 0;
    xy[height + 1][0].rgbtRed = 0;
    xy[height + 1][0].rgbtGreen = 0;
    xy[height + 1][0].rgbtBlue = 0;
    xy[height + 1][width + 1].rgbtRed = 0;
    xy[height + 1][width + 1].rgbtGreen = 0;
    xy[height + 1][width + 1].rgbtBlue = 0;
    xy[0][width + 1].rgbtRed = 0;
    xy[0][width + 1].rgbtGreen = 0;
    xy[0][width + 1].rgbtBlue = 0;
    
    int red[height][width];
    int green[height][width];
    int blue[height][width];
    
    // uses data from xy to apply edges
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red[i][j] = round(sqrt(((-1) * (xy[i][j].rgbtRed) + (-2) * (xy[i + 1][j].rgbtRed) + (-1) * (xy[i + 2][j].rgbtRed) +
                                    1 * (xy[i][j + 2].rgbtRed) + 2 * (xy[i + 1][j + 2].rgbtRed) + 1 * (xy[i + 2][j + 2].rgbtRed)) *
                                   ((-1) * (xy[i][j].rgbtRed) + (-2) * (xy[i + 1][j].rgbtRed) + (-1) * (xy[i + 2][j].rgbtRed) +
                                    1 * (xy[i][j + 2].rgbtRed) + 2 * (xy[i + 1][j + 2].rgbtRed) + 1 * (xy[i + 2][j + 2].rgbtRed)) +
                                   ((-1) * (xy[i][j].rgbtRed) + (-2) * (xy[i][j + 1].rgbtRed) + (-1) * (xy[i][j + 2].rgbtRed) +
                                    1 * (xy[i + 2][j].rgbtRed) + 2 * (xy[i + 2][j + 1].rgbtRed) + 1 * (xy[i + 2][j + 2].rgbtRed)) *
                                   ((-1) * (xy[i][j].rgbtRed) + (-2) * (xy[i][j + 1].rgbtRed) + (-1) * (xy[i][j + 2].rgbtRed) +
                                    1 * (xy[i + 2][j].rgbtRed) + 2 * (xy[i + 2][j + 1].rgbtRed) + 1 * (xy[i + 2][j + 2].rgbtRed))));
            green[i][j] = round(sqrt(((-1) * (xy[i][j].rgbtGreen) + (-2) * (xy[i + 1][j].rgbtGreen) + (-1) *
                                      (xy[i + 2][j].rgbtGreen) + 1 * (xy[i][j + 2].rgbtGreen) + 2 * (xy[i + 1][j + 2].rgbtGreen) +
                                      1 * (xy[i + 2][j + 2].rgbtGreen)) * ((-1) * (xy[i][j].rgbtGreen) + (-2) *
                                      (xy[i + 1][j].rgbtGreen) + (-1) * (xy[i + 2][j].rgbtGreen) + 1 * (xy[i][j + 2].rgbtGreen) +
                                      2 * (xy[i + 1][j + 2].rgbtGreen) + 1 * (xy[i + 2][j + 2].rgbtGreen)) + ((-1) *
                                      (xy[i][j].rgbtGreen) + (-2) * (xy[i][j + 1].rgbtGreen) + (-1) * (xy[i][j + 2].rgbtGreen) +
                                      1 * (xy[i + 2][j].rgbtGreen) + 2 * (xy[i + 2][j + 1].rgbtGreen) + 1 *
                                      (xy[i + 2][j + 2].rgbtGreen)) * ((-1) * (xy[i][j].rgbtGreen) + (-2) *
                                      (xy[i][j + 1].rgbtGreen) + (-1) * (xy[i][j + 2].rgbtGreen) + 1 * (xy[i + 2][j].rgbtGreen) +
                                      2 * (xy[i + 2][j + 1].rgbtGreen) + 1 * (xy[i + 2][j + 2].rgbtGreen))));
            blue[i][j] = round(sqrt(((-1) * (xy[i][j].rgbtBlue) + (-2) * (xy[i + 1][j].rgbtBlue) + (-1) * (xy[i + 2][j].rgbtBlue) +
                                     1 * (xy[i][j + 2].rgbtBlue) + 2 * (xy[i + 1][j + 2].rgbtBlue) + 1 *
                                     (xy[i + 2][j + 2].rgbtBlue)) * ((-1) * (xy[i][j].rgbtBlue) + (-2) * (xy[i + 1][j].rgbtBlue) +
                                     (-1) * (xy[i + 2][j].rgbtBlue) + 1 * (xy[i][j + 2].rgbtBlue) + 2 * (xy[i + 1][j + 2].rgbtBlue) +
                                     1 * (xy[i + 2][j + 2].rgbtBlue)) + ((-1) * (xy[i][j].rgbtBlue) + (-2) *
                                     (xy[i][j + 1].rgbtBlue) + (-1) * (xy[i][j + 2].rgbtBlue) + 1 * (xy[i + 2][j].rgbtBlue) + 2 *
                                     (xy[i + 2][j + 1].rgbtBlue) + 1 * (xy[i + 2][j + 2].rgbtBlue)) * ((-1) * (xy[i][j].rgbtBlue) +
                                     (-2) * (xy[i][j + 1].rgbtBlue) + (-1) * (xy[i][j + 2].rgbtBlue) + 1 * (xy[i + 2][j].rgbtBlue) +
                                     2 * (xy[i + 2][j + 1].rgbtBlue) + 1 * (xy[i + 2][j + 2].rgbtBlue))));
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (red[i][j] > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = red[i][j];
            }
            if (green[i][j] > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = green[i][j];
            }
            if (blue[i][j] > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = blue[i][j];
            }
        }
    }
    return;
}
