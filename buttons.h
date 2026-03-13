#pragma once
#include <Arduino.h>
#include "config.h"

enum class ButtonAction { 
    NONE, 
    NEXT, 
    PREV, 
    VOL_UP, 
    VOL_DOWN };

class InputController {
private:
    unsigned long last_press = 0;
    const unsigned long debounce_delay = 250;

public:
    void begin() {
        pinMode(Config::PIN_VOL_UP, INPUT_PULLUP);
        pinMode(Config::PIN_VOL_DOWN, INPUT_PULLUP);
        pinMode(Config::PIN_PREV, INPUT_PULLUP);
        pinMode(Config::PIN_NEXT, INPUT_PULLUP);
    }

    ButtonAction checkButtons() {
        if (millis() - last_press < debounce_delay) {
            return ButtonAction::NONE;
        }

        if (digitalRead(Config::PIN_NEXT) == LOW) {
            last_press = millis();
            return ButtonAction::NEXT;
        }
        if (digitalRead(Config::PIN_PREV) == LOW) {
            last_press = millis();
            return ButtonAction::PREV;
        }
        if (digitalRead(Config::PIN_VOL_UP) == LOW) {
            last_press = millis();
            return ButtonAction::VOL_UP;
        }
        if (digitalRead(Config::PIN_VOL_DOWN) == LOW) {
            last_press = millis();
            return ButtonAction::VOL_DOWN;
        }

        return ButtonAction::NONE;
    }
};