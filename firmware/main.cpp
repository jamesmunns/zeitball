#include "Particle.h"
#include "led_playground.h"

void setup() // Put setup code here to run once
{
    pinMode(D7, OUTPUT);
    LedSetup();

    Particle.function("demo", LedCommand);
}

void loop() // Put code here to loop forever
{
    Particle.publish("Heartbeat", "Hello :)");
    for(int i=0; i<100; i++) {
        LedHandler();
        delay(100);
    }
}
