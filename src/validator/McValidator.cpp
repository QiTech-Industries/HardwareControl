// Related
#include "McValidator.h"
// System / External
#include <stdint.h>
// Selfmade
// Project

bool McValidator::isDigitalPinValid(uint8_t pin){
    return true;
}

bool McValidator::isAnalogPinValid(uint8_t pin){
    return true;
}

bool McValidator::isDigitalPinsValid(uint8_t pins[], uint16_t pinsLength){
    for(uint16_t i=0; i<pinsLength; ++i){
        if(!isDigitalPinValid(pins[i])) return false;
    }
    return true;
}
