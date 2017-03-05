#include "Particle.h"
#include "neopixel/neopixel.h"
#include "pomodoro.h"

#define PIXEL_COUNT 8
// #define PIXEL_COUNT 60
#define PIXEL_PIN D3
#define PIXEL_TYPE WS2812B

extern Adafruit_NeoPixel strip;
extern void Clear();

typedef enum
{
    THIRTY_MINS     = (30 * 10),
    FIVE_MINS       = ( 5 * 10),
    FIFTEEN_MINS    = (15 * 10),
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
        Clear();
    }

    pom_data = {
        .start_time = 0,
        .stop_time = 0,
        .pom_length = INVALID,
        .is_active = false
    };
}

void pom_init() {
    strip.begin();
    Clear();
    pom_reset();
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
    const float all_on = (float)PIXEL_COUNT * 255.0f;
    int on_now = (int)(all_on * (1.0f - progress_pct));

    for(int i=PIXEL_COUNT-1; i>=0; i--) {
        int pix = (on_now >= 255) ? 255 : on_now;
        strip.setPixelColor(i, pix, 0, 0);
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

    if(LOW == digitalRead(D0)) {
        pom_start(THIRTY_MINS);
    } else if (LOW == digitalRead(D1)) {
        pom_start(FIVE_MINS);
    } else if (LOW == digitalRead(D2)) {
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
    }

    return retval;
}