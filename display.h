#pragma once
#include <cstdint>
#include <vector>
#include <utility>

struct Pixel
{
    public:
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;

    Pixel() : Red(0), Green(0), Blue(0) {}
  
    Pixel(uint8_t r, uint8_t g, uint8_t b) : Red(r), Green(g), Blue(b) {}
};

class display
{
    private:
        int Width;
        int Height;
        std::vector<std::vector<Pixel>> pixelMap; 
    public:
        display(int Width, int Height);
        void savePPMformat(void);
        void drawLine(double pointOneX, double pointOneY, double pointTwoX, double pointTwoY);
};