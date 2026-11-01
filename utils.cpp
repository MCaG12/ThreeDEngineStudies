
#include "utils.h"

Vector4d Utils::newPositions(Vector4d *PointA, Vector4d *PointB, double transform)
{
    Vector4d result;

    result.x = PointA->x + ( (PointB->x - PointA->x) * transform);
    result.y = PointA->y + ( (PointB->y - PointA->y) * transform);
    result.z = PointA->z + ( (PointB->z - PointA->z) * transform);
    result.w = PointA->w + ( (PointB->w - PointA->w) * transform);

    return result;
}

bool Utils::applyClipping(Vector4d *PointA, Vector4d *PointB)
{
    double distanceA = PointA->w + PointA->z;
    double distanceB = PointB->w + PointB->z;

    if(distanceA < 0 && distanceB < 0) return false;
    if(distanceA >= 0 && distanceB >= 0) return true;

    double transform = distanceA / (distanceA - distanceB);

    Vector4d ClippedPoint = this->newPositions(PointA, PointB, transform);

    if(distanceA < 0)
    { 
        (*PointA) = ClippedPoint; 
    }
    else
    {
        (*PointB) = ClippedPoint;
    }

    return true;
}

std::pair<double,double> 
Utils::putToScreen(Vector4d *Point, int Width, int Height)
{
    double ndcX = Point->x / Point->w;
    double ndcY = Point->y / Point->w;

    std::pair<double,double> result;
    double screenX = (ndcX + 1) * 0.5 * Width;
    double screenY = (1 - ndcY) * 0.5 * Height;

    result = {screenX, screenY};
    return result;
}

std::pair<double, double> findLeft(double x, double y)
{
    std::pair<double, double> result = {-(y), x};
    return result;
}

bool
Utils::backFaceCullingCheck(Vector4d *PointA, Vector4d *PointB, Vector4d *PointC)
{
    if( ( PointA->z + PointA->w < 0 ) && ( PointB->z + PointB->w < 0 ) && ( PointC->z + PointC->w < 0 ) ) { return false; }

    std::pair<double, double> AtoB;
    std::pair<double, double> AtoC;

    AtoB = { ( (PointB->x / PointB->w) - (PointA->x/PointA->w) ) , ( (PointB->y / PointB->w) -  (PointA->y / PointA->w) ) };

    AtoC = { ( (PointC->x / PointC->w) - (PointA->x/PointA->w) ) , ( (PointC->y / PointC->w) - (PointA->y / PointA->w)  ) };

    AtoB = findLeft(AtoB.first, AtoB.second);

    double area = (AtoC.first * AtoB.first) + (AtoC.second * AtoB.second);

    if(area > 0){ return true; }

    return false;
}

double Utils::paintPixelCheck(double x0, double y0, double x1, double y1, double x2, double y2)
{
    return (x1 - x0) * (y2 - y0) - (x2- x0) * (y1 - y0);
}

void 
Utils::paintPixel(double x0, double y0, double x1, double y1, double x2, double y2, Pixel pixelColor, std::vector<std::vector<Pixel>> *pixelMap, int width, int height)
{
    double area = paintPixelCheck(x0, y0, x1,  y1,  x2,  y2);
    if(area == 0) { return; }

    //fetching the clipping rectangles extremes

    int LeftMostX  = std::min({x0, x1, x2});
    int RightMostX = std::max({x0, x1, x2});

    int BottomMostY = std::min({y0, y1, y2});
    int TopMostY    = std::max({y0, y1, y2});

    if(LeftMostX < 0) LeftMostX = 0;
    if(RightMostX > width) RightMostX = width - 1;

    if(BottomMostY < 0) BottomMostY = 0;
    if(TopMostY > height) TopMostY = height - 1;

    for(int y = BottomMostY; y < TopMostY; y++)
    {
        for (int x = LeftMostX; x < RightMostX; x++)
        {
            double px = x + 0.5;
            double py = y + 0.5;

            double wA = paintPixelCheck(x1, y1, x2, y2, px, py);
            double wB = paintPixelCheck(x2, y2, x0, y0, px, py);
            double wC = paintPixelCheck(x0, y0, x1, y1, px, py);

            bool isPixelInside = (area > 0) ? (wA >= 0 && wB >= 0 && wC >= 0) : (wA <= 0 && wB <= 0 && wC <= 0);

            if(isPixelInside) { (*pixelMap)[y][x] = pixelColor;}
         
        }
    }
}