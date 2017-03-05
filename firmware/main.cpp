#include "Particle.h"
#include "neopixel/neopixel.h"
#include "pomodoro.h"
#include "config.h"
#include "ring.h"

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

void io_init()
{
    pinMode(RIGHT_BUTTON, INPUT);
    pinMode(CENTER_BUTTON, INPUT);
    pinMode(LEFT_BUTTON, INPUT);
}

void setup() // Put setup code here to run once
{

    strip.begin();
    ring_clear();

    pom_init();

    // Particle.function("demo", LedCommand);
    Particle.function("pom", PomCommand);

}

void loop() // Put code here to loop forever
{

    pom_poll();
    pom_update();
    delay(50);

}
