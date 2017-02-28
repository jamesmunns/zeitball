#include "Particle.h"
#include "led_playground.h"
#include "pomodoro.h"

void setup() // Put setup code here to run once
{
    pinMode(D7, OUTPUT);
    LedSetup();

    // Particle.function("demo", LedCommand);
    // Particle.function("pom", PomCommand);
}

void loop() // Put code here to loop forever
{
    Particle.publish("Heartbeat", "Hello :)");
    // for(int i=0; i<100; i++) {
    //     // LedHandler();
    //     pom_update();
    //     delay(100);
    // }
    LedPlay();
}
