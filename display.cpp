#include "display.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <math.h>

display::display(int Width, int Height)
{
    for(int y = 0; y < Height; y++)
    {
        std::vector<Pixel> currentYLevel;
        for(int x = 0; x < Width; x++)
        {
            Pixel newPixel;
            currentYLevel.push_back(newPixel);
        }
        this->pixelMap.push_back(currentYLevel);
    }
    this->Height = Height;
    this->Width = Width;
    return;
}

void display::drawLine(double pointOneX, double pointOneY, double pointTwoX, double pointTwoY)
{

    int initialX     = (int)std::lround(pointOneX);
    int initialY     = (int)std::lround(pointOneY);
    int destinationX = (int)std::lround(pointTwoX);
    int destinationY = (int)std::lround(pointTwoY);

    Pixel Painted(255,255, 255);

    int distanceX = abs(destinationX - initialX);
    int distanceY = abs(destinationY - initialY);

    int stepX = (initialX < destinationX) ? 1 : -1;
    int stepY = (initialY < destinationY) ? 1 : -1;

    int check = distanceX - distanceY;

    while(true)
    {
        bool canPaint =  (initialX < this->Width && initialX >= 0) && (initialY < this->Height && initialY >= 0); 
      

        if( canPaint ) {  this->pixelMap[initialY][initialX] = Painted; }

        if(initialX == destinationX && initialY == destinationY) { return; }

        int doubleCheck = 2 * check;

        if(doubleCheck >= -distanceY)
        {
            check -= distanceY;
            initialX += stepX;
        }

        if(doubleCheck <= distanceX)
        {
            check += distanceX;
            initialY += stepY;
        }
    }

}

void display::savePPMformat(void)
{
    std::ofstream outFile("output.ppm", std::ios::binary);

    outFile << "P6\n";
    outFile << this->Width << " " << this->Height << "\n";
    outFile << "255\n";

    for (int y = 0; y < Height; y++)
    {
        for (int x = 0; x < Width; x++)
        {
            const Pixel& currentPixel = this->pixelMap[y][x];

            outFile.put(static_cast<char>(currentPixel.Red));
            outFile.put(static_cast<char>(currentPixel.Green));
            outFile.put(static_cast<char>(currentPixel.Blue));
        }
    }
}
