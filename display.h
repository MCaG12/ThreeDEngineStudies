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
    uint8_t Padding;

    Pixel() : Red(0), Green(0), Blue(0), Padding(0) {}
  
    Pixel(uint8_t r, uint8_t g, uint8_t b) : Red(r), Green(g), Blue(b), Padding(0) {}
};

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