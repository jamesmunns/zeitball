#include "Particle.h"
#include "led_playground.h"
#include "pomodoro.h"

void setup() // Put setup code here to run once
{
    // pinMode(D7, OUTPUT);
    LedSetup();

    // Particle.function("demo", LedCommand);
    // Particle.function("pom", PomCommand);

    // pom_init();

    pinMode(D0, INPUT);
    pinMode(D1, INPUT);
    pinMode(D2, INPUT);
}

void loop() // Put code here to loop forever
{
    // Particle.publish("Heartbeat", "Hello :)");
    // for(int i=0; i<100; i++) {
    //     // LedHandler();
    //     pom_update();
    //     delay(100);
    // }
    // LedPlay();
    // delay(250);
    // Serial.print(digitalRead(D0));
    // Serial.print(digitalRead(D1));
    // Serial.print(digitalRead(D2));

    // Serial.println("");

    // pom_poll();
    // pom_update();
    LedPlay();
    delay(50);

}
