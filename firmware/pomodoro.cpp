#include "Particle.h"
#include "neopixel/neopixel.h"
// #include "config.h"
// #include "math.h"
// #include "pomodoro.h"
// #include "ring.h"
#include "pomodoro.h"
#include "ring.h"
#include "math.h"
#include "config.h"

extern Adafruit_NeoPixel strip;

typedef enum
{
    THIRTY_MINS     = (30 * 60),
    FIVE_MINS       = ( 5 * 60),
    FIFTEEN_MINS    = (15 * 60),
    INVALID         = (0)
} Pom_Length_t;

typedef struct
{
    int start_time;
    int stop_time;
    Pom_Length_t pom_length;
    bool is_active;
} Pomodoro_t;

static Pomodoro_t pom_data;

void pom_reset() {
    // Clear the screen
    if(pom_data.is_active) {
        ring_clear();
    }

    pom_data = {
        .start_time = 0,
        .stop_time = 0,
        .pom_length = INVALID,
        .is_active = false
    };
}

void pom_init() {
    ring_clear();
    pom_reset();
}

int bound(int n, int minval, int maxval) {
    const int lowbound = (n < minval) ? minval : n;
    const int retval = (lowbound > maxval) ? maxval : lowbound;
    return retval;
}

void pom_update() {
    int now = Time.now();

    if(!pom_data.is_active ||
       (now < pom_data.start_time) ||
       (now > pom_data.stop_time))
    {
        // Welp.
        pom_reset();
        return;
    }

    float progress_pct = (float)(now - pom_data.start_time) / (float)pom_data.pom_length;
    const float all_on = (float)PIXEL_COUNT * MAX_BRIGHTNESS_F;
    int on_now = (int)(all_on * (1.0f - progress_pct));

    for(int i=PIXEL_COUNT-1; i>=0; i--) {
        // int pix = (on_now >= MAX_BRIGHTNESS) ? MAX_BRIGHTNESS : on_now;
        int pix = bound(on_now, 10, MAX_BRIGHTNESS);

        switch(pom_data.pom_length) {
            case THIRTY_MINS:
                strip.setPixelColor(i, 0, 0, pix);
                break;
            case FIVE_MINS:
                strip.setPixelColor(i, pix, 0, 0);
                break;
            case FIFTEEN_MINS:
                strip.setPixelColor(i, 0, pix, 0);
                break;
            default:
                pom_reset();
                return;
        }

        on_now -= pix;
    }
    strip.show();
}

bool pom_start(Pom_Length_t pomlen) {
    int now = Time.now();
    int end = now + pomlen;

    if((end < now) ||
       (pom_data.is_active)) {
        return false;
    }

    pom_data = {
        .start_time = now,
        .stop_time = end,
        .pom_length = pomlen,
        .is_active = true
    };

    // SET THE LEDs COMPLETELY ON
    pom_update();

    return true;
}

void pom_poll() {
    if(pom_data.is_active) {
        return;
    }

    if(LOW == digitalRead(LEFT_BUTTON)) {
        pom_start(THIRTY_MINS);
    } else if (LOW == digitalRead(CENTER_BUTTON)) {
        pom_start(FIVE_MINS);
    } else if (LOW == digitalRead(RIGHT_BUTTON)) {
        pom_start(FIFTEEN_MINS);
    }
}

int PomCommand(String eventData) {
    int retval = -1;

    if(eventData == "30") {
        retval = pom_start(THIRTY_MINS) ? 0 : -30;
    } else if (eventData == "5") {
        retval = pom_start(FIVE_MINS) ? 0 : -5;
    } else if (eventData == "15") {
        retval = pom_start(FIFTEEN_MINS) ? 0 : -15;
    } else if (eventData == "stop") {
        pom_reset();
        retval = 0;
    }

    return retval;
}