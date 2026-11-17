
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

double Utils::lerp(double a, double b, double t)
{
    return a + (b - a) * t;
}

Vector4d Utils::lerp(Vector4d a, Vector4d b, double t)
{
    return {
        lerp(a.x, b.x, t),
        lerp(a.y, b.y, t),
        lerp(a.z, b.z, t),
        lerp(a.w, b.w, t)
    };
}

std::vector<Vector4d> Utils::applySutherlandClipping(Vector4d corners[3])
{
    std::vector<Vector4d> Result;

    for(int i = 0; i < 3; i++)
    {
        Vector4d curr = corners[i];
        Vector4d next = corners[(i + 1) % 3];

        double currentDistance = curr.w + curr.z;
        double nextDistance    = next.w + next.z;

        bool isCurrentFront = (currentDistance >= 0);
        bool isNextFront    = (nextDistance >= 0);

        if ( isCurrentFront && isNextFront )
        {
            Result.push_back(next);
        }

        else if ( isCurrentFront && !isNextFront )
        {
            double distance = currentDistance / (currentDistance - nextDistance);
            Result.push_back(lerp(curr, next ,distance));
        }

        else if ( !isCurrentFront && isNextFront )
        {
            double distance = currentDistance / (currentDistance - nextDistance);
            Result.push_back(lerp(curr, next ,distance));
            Result.push_back(next);
        }

    }
    return Result;
}


