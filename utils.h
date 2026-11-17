#pragma once
#include "vector4d.h"
#include <utility>
#include "pixel.h"
#include <vector>
#include <cmath>

class Utils
{
    private:
        double lerp(double a, double b, double t);
        Vector4d lerp(Vector4d a, Vector4d b, double t);

    public:
        bool applyClipping(Vector4d *PointA, Vector4d *PointB);
        Vector4d newPositions(Vector4d *PointA, Vector4d *PointB, double transform);
        std::pair<double,double> putToScreen(Vector4d *Point, int Width, int Height);
        bool backFaceCullingCheck(Vector4d *PointA, Vector4d *PointB, Vector4d *PointC);
        std::vector<Vector4d> applySutherlandClipping(Vector4d corners[3]);
};