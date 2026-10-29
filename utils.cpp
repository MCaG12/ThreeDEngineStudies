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
    double distanceA = PointA->W + PointA->Z;
    double distanceB = PointB->W + PointB->Z;

    if(distanceA < 0 && distanceB < 0) return false;
    if(distanceA >= 0 && distanceB >= 0) return false;

    double transform = distanceA / (distanceA - distanceB);

    Vector4d ClippedPoint = this->newPositions(PointA, PointB, transform);

    if(distanceA < 0)
    { 
        (*PointA) = ClippedPoint 
    }
    else
    {
        (*PointB) = ClippedPoint 
    }
    
    return true;
}

