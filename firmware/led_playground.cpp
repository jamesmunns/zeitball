#include "neopixel/neopixel.h"
#include <math.h>

#define PIXEL_COUNT 8
#define PIXEL_PIN D2
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
static uint8_t curpix = 0;

void SimpleSpinner() {
    for(int i=0; i<PIXEL_COUNT; i++) {
        int x = (i==curpix) ? 64 : 4;
        strip.setPixelColor(i, 0, 0, x);
    }

    strip.show();

    curpix += 1;
    curpix %= PIXEL_COUNT;

    delay(500 / PIXEL_COUNT);
}

// ---------------------------------------------------------------------------

void LedSetup() {
    strip.begin();
    strip.show();
}

void LedPlay() {
    for(;;) {
        SimpleSpinner();
    }
}