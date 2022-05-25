// Related
#include "McValidator.h"
// System / External
#include <stdint.h>
// Selfmade
// Project

bool McValidator::isDigitalPin(uint8_t pin) { return true; }

bool McValidator::isAnalogPin(uint8_t pin) { return true; }

bool McValidator::isDigitalPin(uint8_t pins[], uint16_t pinsLength) {
    for (uint16_t i = 0; i < pinsLength; ++i) {
        if (!isDigitalPin(pins[i])) return false;
    }
    return true;
}
