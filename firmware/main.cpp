#include "Particle.h"
#include "neopixel/neopixel.h"
#include <math.h>

#define PIXEL_COUNT 8
#define PIXEL_PIN D2
#define PIXEL_TYPE WS2812B
Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

static uint8_t curpix = 0;

void setup() // Put setup code here to run once
{
    pinMode(D7, OUTPUT);
    Serial.begin(57600);
    strip.begin();
    strip.show();
}

void loop() // Put code here to loop forever
{
    Serial.println("Hello, World!");

    for(int i=0; i<PIXEL_COUNT; i++) {
        int x = (i==curpix) ? 64 : 4;
        strip.setPixelColor(i, 0, 0, x);
    }

    strip.show();

    curpix += 1;
    curpix %= PIXEL_COUNT;

    delay(500 / PIXEL_COUNT);
}
