#include "Particle.h"
#include "neopixel/neopixel.h"
#include <math.h>

#define PIXEL_COUNT 8
// #define PIXEL_COUNT 60
#define PIXEL_PIN D2
#define PIXEL_TYPE WS2812B
#define PI 3.1415926f

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
static uint8_t curpix = 0;
static float exponent = 4.0f;

void Clear() {
    for(int i=0; i<PIXEL_COUNT; i++) {
        strip.setPixelColor(i, 0, 0, 0);
    }
    strip.show();
}

void SimpleSpinner() {
    Clear();
    for(int j=0; j<(PIXEL_COUNT*10); j++) {
        for(int i=0; i<PIXEL_COUNT; i++) {
            int x = (i==curpix) ? 64 : 4;
            strip.setPixelColor(i, 0, 0, x);
        }

        strip.show();

        curpix += 1;
        curpix %= PIXEL_COUNT;

        delay(500 / PIXEL_COUNT);
    }
}

void DingDone() {
    Clear();

    for(int j=0; j<3; j++) {
        for(int i=0; i<PIXEL_COUNT; i++) {
            strip.setPixelColor(i, 64, 0, 0);
        }
        strip.show();
        delay(500);

        for(int i=0; i<PIXEL_COUNT; i++) {
            strip.setPixelColor(i, 0, 0, 0);
        }
        strip.show();
        delay(500);
    }
}

void SimpleCountdown() {
    Clear();
    // Start all on
    for(int i=0; i<PIXEL_COUNT; i++) {
        strip.setPixelColor(i, 64, 0, 0);
    }
    strip.show();
    delay(1000);

    for(int i=0; i<PIXEL_COUNT; i++) {
        strip.setPixelColor(i, 0, 0, 0);
        strip.show();
        delay(1000);
    }

    delay(2000);

    DingDone();

}

void RBChaser() {
    Clear();

    int idx = 0;

    for(int k=0; k<(PIXEL_COUNT*10); k++) {

        for(int i=0; i<PIXEL_COUNT; i++) {
            if(i==idx) {
                strip.setPixelColor(i, 255, 0, 0);
            }
            else if(((i+(PIXEL_COUNT/2))%PIXEL_COUNT) == idx) {
                strip.setPixelColor(i, 0, 0, 255);
            }
            else {
                strip.setPixelColor(i, 0, 0, 0);
            }
        }
        idx += 1;
        idx %= PIXEL_COUNT;

        strip.show();
        delay(500/PIXEL_COUNT);
    }
}

void TimeBreath() {
    Clear();

    for(int k=0; k<(10000/5); k++) {
        float val = ((exp(sin(millis()/2000.0*PI)) - 0.36787944)*108.0);
        for(int i=0; i<PIXEL_COUNT; i++) {
            strip.setPixelColor(i, val, val, val);
        }
        strip.show();
        delay(5);
    }
}

void FadeAround() {
    Clear();

    const int max = 255 * PIXEL_COUNT;

    for(int j=max; j>0; j--) {
        int running = j;
        for(int i=PIXEL_COUNT-1; i>=0; i--) {
            int pix = (running >= 255) ? 255 : running;
            strip.setPixelColor(i, pix, 0, 0);
            running -= pix;
        }
        strip.show();
        delay(2);
    }

    DingDone();

    for(int j=max; j>0; j--) {
        int running = j;
        for(int i=PIXEL_COUNT-1; i>=0; i--) {
            int pix = (running >= 255) ? 255 : running;
            strip.setPixelColor(i, pix, 0, 0);
            running -= pix;
        }
        strip.show();
        delay(5);
    }

    DingDone();

    for(int j=max; j>0; j--) {
        int running = j;
        for(int i=PIXEL_COUNT-1; i>=0; i--) {
            int pix = (running >= 255) ? 255 : running;
            strip.setPixelColor(i, pix, 0, 0);
            running -= pix;
        }
        strip.show();
        delay(10);
    }

    DingDone();
}

void FadeDown() {
    Clear();

    for(int j=255; j>=0; j--) {
        for(int i=0; i<PIXEL_COUNT; i++) {
            strip.setPixelColor(i, 0, 0, j);
        }
        strip.show();
        delay(50);
    }

    DingDone();
}

void FadeUpDown() {
    Clear();

    for(int j=32; j<=255; j++) {
        for(int i=0; i<PIXEL_COUNT; i++) {
            strip.setPixelColor(i, 0, j, 0);
        }
        strip.show();
        delay(40);
    }

    for(int j=255; j>=0; j--) {
        for(int i=0; i<PIXEL_COUNT; i++) {
            int pix = (j < 24) ? 24 : j;
            strip.setPixelColor(i, 0, pix, 0);
        }
        strip.show();
        delay(40);
    }

    DingDone();
}

void FakeClock() {
    for(int h=0; h<PIXEL_COUNT; h++) {
        for(int m=0; m<PIXEL_COUNT; m++) {
            for(int s=0; s<PIXEL_COUNT; s++) {
                for(int x=0; x<PIXEL_COUNT; x++) {
                    int r = (x==h) ? 128 : 0;
                    int g = (x==m) ? 128 : 0;
                    int b = (x==s) ? 128 : 0;

                    strip.setPixelColor(x, r, g, b);
                }
                strip.show();
                delay(50);
            }
        }
    }

    DingDone();
}

// ---------------------------------------------------------------------------
// Fancy Math

double deg2rad(double x) {
    return (PI*x) / 180.0f;
}

typedef struct {
    double x;
    double y;
    double r;
    double deg;
    double intensity;
} Point_t;

static Point_t leds[PIXEL_COUNT];

void fancy_init() {

    for(int i=0; i < PIXEL_COUNT; i++) {
        leds[i].deg = (360.0f * (double)i) / (double)PIXEL_COUNT;
        leds[i].r = 1.0f;

        leds[i].x = sin(deg2rad(leds[i].deg));
        leds[i].y = cos(deg2rad(leds[i].deg));

        // printf("%d: %.2f %.2f %.2f %.2f\n", i, leds[i].deg, leds[i].r, leds[i].x, leds[i].y);
    }
}

void fancy_light(float x, float y) {

    for(int l=0; l<PIXEL_COUNT; l++) {
        double d_x = x - leds[l].x;
        double d_y = y - leds[l].y;

        float a = sqrt(d_x*d_x + d_y*d_y);
        // float b = exp2(a);
        float b = pow(exponent, a);
        float c = 1.0f / b;

        leds[l].intensity = c;

        int boom = 255.0f * c;

        strip.setPixelColor(l, boom, 0, 0);
    }

    strip.show();
}

// ---------------------------------------------------------------------------

void LedSetup() {
    strip.begin();
    fancy_init();
    Clear();
}

volatile bool busy = false;

// Hmm. I sure hope String is implemented as a heap variable, rather than as a fixed
//   compile-time-sized value. Otherwise writing to `command` is a really bad idea.
//   Consider switching to c-str's.
static String command = "";

int LedCommand(String eventData) {
    if(busy) {
        return -100;
    } else {
        busy = true;
        command = eventData;
    }

    return 0;
}

void LedHandler() {
    if(!busy) {
        return;
    }

    bool handled = true;

    // TODO, process message
    if(command == "FadeUpDown") {
        FadeUpDown();
    } else if(command == "FadeDown") {
        FadeDown();
    } else if(command == "FadeAround") {
        FadeAround();
    } else if(command == "TimeBreath") {
        TimeBreath();
    } else if(command == "RBChaser") {
        RBChaser();
    } else if(command == "SimpleSpinner") {
        SimpleSpinner();
    } else if(command == "SimpleCountdown") {
        SimpleCountdown();
    } else if(command == "FakeClock") {
        FakeClock();
    } else {
        handled = false;
        DingDone();
    }

    Clear();


    if(handled) {
        command.concat(" complete");
    } else {
        command.concat(" error: unknown");
    }

    Particle.publish("status", command);

    command = "";
    busy = false;

}

void fancy_demo() {
    // cartesian demo
    // for(float x=-1.0f; x < 1.0f; x+=0.5f) {
    //     for(float y=1.0f; y > -1.0f; y-=0.5f) {
    //         fancy_light(x, y);
    //         delay(500);
    //     }
    // }

    // Circular demo
    // for(float e=2.0f; e<10.0f; e+=1.0f) {
    //     exponent = e;
    //     for(int j=0; j<20; j++) {
    //         for(int i=0; i<PIXEL_COUNT; i++) {
    //             fancy_light(leds[i].x, leds[i].y);
    //             delay(500 / PIXEL_COUNT);
    //         }
    //     }

    //     DingDone();
    // }

    // Other Circular demo
    // for(float e=2.0f; e<4.1f; e+=0.5f) {
        // exponent = e;
        for(float d=0; d<720; d+=1.0) {
            float x = sin(deg2rad(d));
            float y = cos(deg2rad(d));
            fancy_light(x,y);
            delay(10);
        }
        DingDone();
    // }

}

void LedPlay() {
    for(;;) {
        fancy_demo();
        // FadeUpDown();
        // FadeDown();
        // FadeAround();
        // TimeBreath();
        // RBChaser();
        // SimpleSpinner();
        // SimpleCountdown();
        // FakeClock();
    }
}