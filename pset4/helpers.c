#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //Use to for loops for cycle though each pixle in each row of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Calculate the average of the red green and blue pixle vales
            float ave = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            //Set all pixels to the average value
            image[i][j].rgbtBlue = round(ave);
            image[i][j].rgbtGreen = round(ave);
            image[i][j].rgbtRed = round(ave);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Use two for loops to cycle through left half of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            //Copy RGB triple from LHS into a temp
            RGBTRIPLE temp = image[i][j];
            //Set LHS pixel equal to RHS pixel
            image[i][j] = image[i][width - 1 - j];

            //Set LHS pixel equal to temp
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Declare an empty image the same size as the input image
    //This will prevent modifying the original image while calculating averages
    RGBTRIPLE newImage[height][width];

    //Use for loops to calculate the averages of each pixel from the surounding pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Declare variable to sum up total for each surounding pixels for each color (RGB)
            unsigned long sumBlue = 0;
            unsigned long sumGreen = 0;
            unsigned long sumRed = 0;
            float aveBlue = 0.0;
            float aveGreen = 0.0;
            float aveRed = 0.0;

            //For top row excluding corners
            if (i == 0 && (j != 0 && j != width - 1))
            {
                for (int k = 0; k < 2; k++)
                {
                    for (int l = 0; l < 3; l++)
                    {
                        sumBlue += image[i + k][j - 1 + l].rgbtBlue;
                        sumGreen += image[i + k][j - 1 + l].rgbtGreen;
                        sumRed += image[i + k][j - 1 + l].rgbtRed;
                    }
                }
               //Calculate averages
                aveBlue = sumBlue / 6.0;
                aveGreen = sumGreen / 6.0;
                aveRed = sumRed / 6.0;
            }
            //For bottom row excluding corners
            else if (i == height - 1 && (j != 0 && j != width - 1))
            {
                for (int k = 0; k < 2; k++)
                {
                    for (int l = 0; l < 3; l++)
                    {
                        sumBlue += image[i - 1 + k][j - 1 + l].rgbtBlue;
                        sumGreen += image[i - 1 + k][j - 1 + l].rgbtGreen;
                        sumRed += image[i - 1 + k][j - 1 + l].rgbtRed;
                    }
                }
                //Calculate averages
                aveBlue = sumBlue / 6.0;
                aveGreen = sumGreen / 6.0;
                aveRed = sumRed / 6.0;
            }
            //For left most column excluding corners
            else if (j == 0 && (i != 0 && i != height - 1))
            {
                for (int k = 0; k < 3; k++)
                {
                    for (int l = 0; l < 2; l++)
                    {
                        sumBlue += image[i - 1 + k][j + l].rgbtBlue;
                        sumGreen += image[i - 1 + k][j + l].rgbtGreen;
                        sumRed += image[i - 1 + k][j + l].rgbtRed;
                    }
                }
                //Calculate averages
                aveBlue = sumBlue / 6.0;
                aveGreen = sumGreen / 6.0;
                aveRed = sumRed / 6.0;
            }
            //For right most column excluding corners
            else if (j == width - 1 && (i != 0 && i != height - 1))
            {
                for (int k = 0; k < 3; k++)
                {
                    for (int l = 0; l < 2; l++)
                    {
                        sumBlue += image[i - 1 + k][j - 1 + l].rgbtBlue;
                        sumGreen += image[i - 1 + k][j - 1 + l].rgbtGreen;
                        sumRed += image[i - 1 + k][j - 1 + l].rgbtRed;
                    }
                }
                //Calculate averages
                aveBlue = sumBlue / 6.0;
                aveGreen = sumGreen / 6.0;
                aveRed = sumRed / 6.0;
            }
            //For top left corner
            else if (i == 0 && j == 0)
            {
                for (int k = 0; k < 2; k++)
                {
                    for (int l = 0; l < 2; l++)
                    {
                        sumBlue += image[i + k][j + l].rgbtBlue;
                        sumGreen += image[i + k][j + l].rgbtGreen;
                        sumRed += image[i + k][j + l].rgbtRed;
                    }
                }
                //Calculate averages
                aveBlue = sumBlue / 4.0;
                aveGreen = sumGreen / 4.0;
                aveRed = sumRed / 4.0;
            }
            //For bottom left corner
            else if (i == height - 1 && j == 0)
            {
                for (int k = 0; k < 2; k++)
                {
                    for (int l = 0; l < 2; l++)
                    {
                        sumBlue += image[i - 1 + k][j + l].rgbtBlue;
                        sumGreen += image[i - 1 + k][j + l].rgbtGreen;
                        sumRed += image[i - 1 + k][j + l].rgbtRed;
                    }
                }
                //Calculate averages
                aveBlue = sumBlue / 4.0;
                aveGreen = sumGreen / 4.0;
                aveRed = sumRed / 4.0;
            }
            //For top right corner
            else if (i == 0 && j == width - 1)
            {
                for (int k = 0; k < 2; k++)
                {
                    for (int l = 0; l < 2; l++)
                    {
                        sumBlue += image[i + k][j - 1 + l].rgbtBlue;
                        sumGreen += image[i + k][j - 1 + l].rgbtGreen;
                        sumRed += image[i + k][j - 1 + l].rgbtRed;
                    }
                }
                //Calculate averages
                aveBlue = sumBlue / 4.0;
                aveGreen = sumGreen / 4.0;
                aveRed = sumRed / 4.0;
            }
            //For bottom right corner
            else if (i == height - 1 && j == width - 1)
            {
                for (int k = 0; k < 2; k++)
                {
                    for (int l = 0; l < 2; l++)
                    {
                        sumBlue += image[i - 1 + k][j - 1 + l].rgbtBlue;
                        sumGreen += image[i - 1 + k][j - 1 + l].rgbtGreen;
                        sumRed += image[i - 1 + k][j - 1 + l].rgbtRed;
                    }
                }
                //Calculate averages
                aveBlue = sumBlue / 4.0;
                aveGreen = sumGreen / 4.0;
                aveRed = sumRed / 4.0;
            }
            //For non-edge condition pixels sum all 9 surrounding pixels
            else
            {
                for (int k = 0; k < 3; k++)
                {
                    for (int l = 0; l < 3; l++)
                    {
                        sumBlue += image[i - 1 + k][j - 1 + l].rgbtBlue;
                        sumGreen += image[i - 1 + k][j - 1 + l].rgbtGreen;
                        sumRed += image[i - 1 + k][j - 1 + l].rgbtRed;
                    }
                }
                //Calculate averages
                aveBlue = sumBlue / 9.0;
                aveGreen = sumGreen / 9.0;
                aveRed = sumRed / 9.0;
            }

            //Set new image values to the calculated average values
            newImage[i][j].rgbtBlue = round(aveBlue);
            newImage[i][j].rgbtGreen = round(aveGreen);
            newImage[i][j].rgbtRed = round(aveRed);
        }
    }

    //Modify image to new image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = newImage[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //Declare new variable for the image with a black border and Gx & Gy
    RGBTRIPLE imageGxGy[height + 2][width + 2];
    //Declare an RGBTRIPLE that is balck
    RGBTRIPLE black = {.rgbtBlue = 0, .rgbtGreen = 0, .rgbtRed = 0};
    //Set top and bottom black border of imageGxGy
    for (int i = 0; i < width + 2; i++)
    {
        imageGxGy[0][i] = black;
        imageGxGy[height + 1][i] = black;
    }

    //Set right and left black borders of imageGxGy
    for (int i = 0; i < height; i++)
    {
        imageGxGy[i + 1][0] = black;
        imageGxGy[i + 1][width + 1] = black;
    }

    //Add image to imageGxGy variable
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageGxGy[i+1][j+1].rgbtBlue = image[i][j].rgbtBlue;
            imageGxGy[i+1][j+1].rgbtGreen = image[i][j].rgbtGreen;
            imageGxGy[i+1][j+1].rgbtRed = image[i][j].rgbtRed;
        }
    }

    //Cycle through the image to calculate Gx, Gy and sobel values for all pixel colors
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
          long int gxBlue, gxGreen, gxRed, gyBlue, gyGreen, gyRed;
          float sobelBlue, sobelGreen, sobelRed;

          //Calculate Gx for Blue
            gxBlue = (-1 * imageGxGy[i][j].rgbtBlue)
                + (-2 * imageGxGy[i+1][j].rgbtBlue) + (-1 * imageGxGy[i+2][j].rgbtBlue)
                + (imageGxGy[i][j+2].rgbtBlue) + (2 * imageGxGy[i+1][j+2].rgbtBlue)
                + (imageGxGy[i+2][j+2].rgbtBlue);
            //Calculate Gx for Green
            gxGreen = (-1 * imageGxGy[i][j].rgbtGreen)
                + (-2 * imageGxGy[i+1][j].rgbtGreen) + (-1 * imageGxGy[i+2][j].rgbtGreen)
                + (imageGxGy[i][j+2].rgbtGreen) + (2 * imageGxGy[i+1][j+2].rgbtGreen)
                + (imageGxGy[i+2][j+2].rgbtGreen);
            //Calulate Gx for Red
            gxRed = (-1 * imageGxGy[i][j].rgbtRed)
                + (-2 * imageGxGy[i+1][j].rgbtRed) + (-1 * imageGxGy[i+2][j].rgbtRed)
                + (imageGxGy[i][j+2].rgbtRed) + (2 * imageGxGy[i+1][j+2].rgbtRed)
                + (imageGxGy[i+2][j+2].rgbtRed);
            //Calculate Gy for Blue
            gyBlue = (-1 * imageGxGy[i][j].rgbtBlue)
                + (-2 * imageGxGy[i][j+1].rgbtBlue) + (-1 * imageGxGy[i][j+2].rgbtBlue)
                + (imageGxGy[i+2][j].rgbtBlue) + (2 * imageGxGy[i+2][j+1].rgbtBlue)
                + (imageGxGy[i+2][j+2].rgbtBlue);
            //Calculate Gy for Green
            gyGreen = (-1 * imageGxGy[i][j].rgbtGreen)
                + (-2 * imageGxGy[i][j+1].rgbtGreen) + (-1 * imageGxGy[i][j+2].rgbtGreen)
                + (imageGxGy[i+2][j].rgbtGreen) + (2 * imageGxGy[i+2][j+1].rgbtGreen)
                + (imageGxGy[i+2][j+2].rgbtGreen);
            //Calculate Gy for Red
            gyRed = (-1 * imageGxGy[i][j].rgbtRed)
                + (-2 * imageGxGy[i][j+1].rgbtRed) + (-1 * imageGxGy[i][j+2].rgbtRed)
                + (imageGxGy[i+2][j].rgbtRed) + (2 * imageGxGy[i+2][j+1].rgbtRed)
                + (imageGxGy[i+2][j+2].rgbtRed);

            //Calculate sobel for blue pixel
            sobelBlue = sqrt(pow(gxBlue, 2) + pow(gyBlue, 2));
            //Calculate sobel for green pixel
            sobelGreen = sqrt(pow(gxGreen, 2) + pow(gyGreen, 2));
            //Calculate sobel for red pixel
            sobelRed = sqrt(pow(gxRed, 2) + pow(gyRed, 2));

            //Check if sobel is greater than 255
            if (sobelBlue > 255)
                sobelBlue = 255;
            if (sobelGreen > 255)
                sobelGreen = 255;
            if (sobelRed > 255)
                sobelRed = 255;

            //modify pixel values of image[i][j] to the sobel values
            image[i][j].rgbtBlue = round(sobelBlue);
            image[i][j].rgbtGreen = round(sobelGreen);
            image[i][j].rgbtRed = round(sobelRed);
        }
    }
    return;
}
