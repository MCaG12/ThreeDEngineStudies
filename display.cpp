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
        std::vector<double> CurrentRow;
        CurrentRow.assign(Width, std::numeric_limits<double>::infinity());

        for(int x = 0; x < Width; x++)
        {
            Pixel newPixel;
            currentYLevel.push_back(newPixel);
        }
        this->DepthBuffer.push_back( CurrentRow );
        this->pixelMap.push_back(currentYLevel);
    }

    this->Height = Height;
    this->Width = Width;
    return;
}

void display::drawLine(double pointOneX, double pointOneY, double pointTwoX, double pointTwoY, Pixel LineColor)
{

    int initialX     = (int)std::lround(pointOneX);
    int initialY     = (int)std::lround(pointOneY);
    int destinationX = (int)std::lround(pointTwoX);
    int destinationY = (int)std::lround(pointTwoY);

    int distanceX = abs(destinationX - initialX);
    int distanceY = abs(destinationY - initialY);

    int stepX = (initialX < destinationX) ? 1 : -1;
    int stepY = (initialY < destinationY) ? 1 : -1;

    int check = distanceX - distanceY;

    while(true)
    {
        bool canPaint =  (initialX < this->Width && initialX >= 0) && (initialY < this->Height && initialY >= 0); 
      

        if( canPaint ) {  this->pixelMap[initialY][initialX] = LineColor; }

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

double display::paintPixelCheck(double x0, double y0, double x1, double y1, double x2, double y2)
{
    return (x1 - x0) * (y2 - y0) - (x2- x0) * (y1 - y0);
}

void 
display::paintPixel(double x0, double y0, double z0, 
                    double x1, double y1, double z1,
                    double x2, double y2, double z2,
                    Pixel pixelColor)
{
    double area = paintPixelCheck(x0, y0, x1,  y1,  x2,  y2);
    if(area == 0) { return; }

    //fetching the clipping rectangles extremes

    int LeftMostX  = std::min({x0, x1, x2});
    int RightMostX = std::max({x0, x1, x2});

    int BottomMostY = std::min({y0, y1, y2});
    int TopMostY    = std::max({y0, y1, y2});

    if(LeftMostX < 0) LeftMostX = 0;
    if(RightMostX >= this->Width) RightMostX = this->Width - 1;

    if(BottomMostY < 0) BottomMostY = 0;
    if(TopMostY >= this->Height) TopMostY = this->Height - 1;

    //if(LeftMostX < 0 || RightMostX > Width - 1 || BottomMostY < 0 || TopMostY > Height - 1) return;

    for(int y = BottomMostY; y <= TopMostY; y++)
    {
        for (int x = LeftMostX; x <= RightMostX; x++)
        {
            double px = x + 0.5;
            double py = y + 0.5;

            double wA = paintPixelCheck(x1, y1, x2, y2, px, py);
            double wB = paintPixelCheck(x2, y2, x0, y0, px, py);
            double wC = paintPixelCheck(x0, y0, x1, y1, px, py);

            bool isPixelInside = (area > 0) ? (wA >= 0 && wB >= 0 && wC >= 0) : (wA <= 0 && wB <= 0 && wC <= 0);

            if(isPixelInside) 
            { 
                double depth = ( (wA /area ) * z0) + ( ( wB / area) * z1) + ( ( wC / area ) * z2);
                if(depth < this->DepthBuffer[y][x])
                {
                    this->DepthBuffer[y][x] = depth;
                    this->pixelMap[y][x] = pixelColor;
                }
            }
         
        }
    }
}

double display::calculateFaceBrightness( Vector3d<double> EdgeOne, Vector3d<double> EdgeTwo, 
                                         Vector3d<double> EdgeThree, Vector3d<double> LightDirection)
{
    Vector3d<double> differenceEdgeOneEdgeTwo(0,0,0);
    Vector3d<double> differenceEdgeOneEdgeThree(0,0,0);

    differenceEdgeOneEdgeTwo.setVectorIndex(0 , (EdgeTwo.getVectorIndex(0)  - EdgeOne.getVectorIndex(0) ) );
    differenceEdgeOneEdgeTwo.setVectorIndex(1,  (EdgeTwo.getVectorIndex(1)  - EdgeOne.getVectorIndex(1) ) );
    differenceEdgeOneEdgeTwo.setVectorIndex(2,  (EdgeTwo.getVectorIndex(2)  - EdgeOne.getVectorIndex(2) ) );

    differenceEdgeOneEdgeThree.setVectorIndex(0 , (EdgeThree.getVectorIndex(0)  - EdgeOne.getVectorIndex(0) ) );
    differenceEdgeOneEdgeThree.setVectorIndex(1,  (EdgeThree.getVectorIndex(1)  - EdgeOne.getVectorIndex(1) ) );
    differenceEdgeOneEdgeThree.setVectorIndex(2,  (EdgeThree.getVectorIndex(2)  - EdgeOne.getVectorIndex(2) ) );
    
    Vector3d<double> Normal = differenceEdgeOneEdgeTwo.crossProduct(differenceEdgeOneEdgeThree);

    Normal = Normal.normalizeVector();

    double FaceBrightness = Normal.getVectorIndex(0) * LightDirection.getVectorIndex(0) +
                            Normal.getVectorIndex(1) * LightDirection.getVectorIndex(1) +
                            Normal.getVectorIndex(2) * LightDirection.getVectorIndex(2);

    if( FaceBrightness < 0 ) { FaceBrightness = 0; }

    double ambient = 0.15; //pure black looks bad , brighten things up a little

    return ambient + (1 - ambient) * FaceBrightness;

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

void display::clear()
{
    for (int y = 0; y < Height; y++)
        for (int x = 0; x < Width; x++)
        {
            pixelMap[y][x]    = Pixel(0, 0, 0);
            DepthBuffer[y][x] = std::numeric_limits<double>::infinity();
        }
}