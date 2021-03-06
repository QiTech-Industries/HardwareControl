#pragma once

// Related
#include "McValidator.h"
// System / External
// Selfmade
// Project

/**
 * @brief Validator-Implementation for the ESP-32 (TODO: Check full mc-id)
 */
class McValidatorEsp32 : public virtual McValidator {
   public:
    /**
     * @brief Checks whether a digital pin is valid and
     *
     * @param pin Pin-number
     * @return true pin exists
     * @return false pin does not exist
     */
    bool isDigitalPin(uint8_t pin);

    /**
     * @brief Checks whether an analog pin is valid and exists
     *
     * @param pin Pin-number
     * @return true pin exists
     * @return false pin does not exist
     */
    bool isAnalogPin(uint8_t pin);

    // inherit function overload from base class isDigitalPin(uint8_t pins[], uint16_t pinsLength)
    using McValidator::isDigitalPin;
};
