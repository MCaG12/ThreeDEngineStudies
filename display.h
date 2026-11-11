#pragma once
#include <vector>
#include <utility>
#include "pixel.h"
#include <algorithm>
#include "vector3d.h"

class display
{
    private:
        int Width;
        int Height;
        std::vector<std::vector<double>> DepthBuffer;
    public:
        std::vector<std::vector<Pixel>> pixelMap; 
        display(int Width, int Height);
        void savePPMformat(void);
        void drawLine(double pointOneX, double pointOneY, double pointTwoX, double pointTwoY);
        void paintPixel(double x0, double y0, double z0, double x1, double y1, double z1, double x2, double y2, double z2, Pixel pixelColor);
        double paintPixelCheck(double x0, double y0, double x1, double y1, double x2, double y2);
        double calculateFaceBrightness( Vector3d<double> EdgeOne, Vector3d<double> EdgeTwo, Vector3d<double> EdgeThree, Vector3d<double> LightDirection);
};