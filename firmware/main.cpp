#include "Particle.h"
#include "led_playground.h"

void setup() // Put setup code here to run once
{
    pinMode(D7, OUTPUT);
    Serial.begin(57600);
    LedSetup();
}

void loop() // Put code here to loop forever
{
    Serial.println("Hello, World!");
    LedPlay();
}
