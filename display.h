#pragma once
#include <vector>
#include <utility>
#include "pixel.h"


class display
{
    private:
        int Width;
        int Height;
    public:
        std::vector<std::vector<Pixel>> pixelMap; 
        display(int Width, int Height);
        void savePPMformat(void);
        void drawLine(double pointOneX, double pointOneY, double pointTwoX, double pointTwoY);
};