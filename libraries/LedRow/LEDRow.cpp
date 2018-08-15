#include <LEDRow.h>

CRGB* row_leds;
uint8_t cur_brightness = 100;
uint8_t tar_brightness = 100;

LEDRow::LEDRow(CRGB ledLights[]){
    row_leds = ledLights;
}

void update_row(uint8_t delta_time){
    #ifdef DEBUG
    Serial.println("LED row update dt: " + str(delta_time));
    #endif
}