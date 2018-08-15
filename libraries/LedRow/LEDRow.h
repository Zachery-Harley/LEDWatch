#ifndef LEDRow_H
#define LEDRow_H

#include <FastLED.h>
#include <Arduino.h>

class LEDRow{
    public:
        LEDRow(CRGB ledLights[]);
        void update_row(uint8_t delta_time);
};

#endif