#pragma once

#include "Particle.h"

#define PIXEL_COUNT 8
#define PIXEL_TYPE WS2812B
#define PI 3.1415926f
#define MAX_BRIGHTNESS 64
#define MAX_BRIGHTNESS_F (float)MAX_BRIGHTNESS

enum IO_PINS
{
    LEFT_BUTTON = D2,
    CENTER_BUTTON = D1,
    RIGHT_BUTTON = D0,
    PIXEL_PIN = D3
};