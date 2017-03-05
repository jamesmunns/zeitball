#include "Particle.h"
#include "neopixel/neopixel.h"
#include "config.h"

extern Adafruit_NeoPixel strip;

void ring_clear() {
    for(int i=0; i<PIXEL_COUNT; i++) {
        strip.setPixelColor(i, 0, 0, 0);
    }
    strip.show();
}