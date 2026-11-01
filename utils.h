#pragma once
#include "vector4d.h"
#include <utility>
#include "pixel.h"
#include <vector>
#include <algorithm>

class Utils
{
    public:
        bool applyClipping(Vector4d *PointA, Vector4d *PointB);
        Vector4d newPositions(Vector4d *PointA, Vector4d *PointB, double transform);
        std::pair<double,double> putToScreen(Vector4d *Point, int Width, int Height);
        bool backFaceCullingCheck(Vector4d *PointA, Vector4d *PointB, Vector4d *PointC);
        static  double paintPixelCheck(double x0, double y0, double x1, double y1, double x2, double y2);

        static void paintPixel(double x0, double y0, double x1, double y1, double x2, double y2, Pixel pixelColor, std::vector<std::vector<Pixel>> *pixelMap, int width, int height);
};