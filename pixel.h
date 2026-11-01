#pragma once
#include <cstdint>

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