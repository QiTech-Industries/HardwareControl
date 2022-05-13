#pragma once

// Related
// System / External
#include <stdint.h>
// Selfmade
// Project

/**
 * @brief Validator for a microcontroller, for example for checking whether a pin exists and is of a specified type
 */
class McValidator {
   public:
    /**
     * @brief Checks whether a digital pin is valid and exists
     *
     * @param pin Pin-number
     * @return true pin exists
     * @return false pin does not exist
     */
    bool isDigitalPin(uint8_t pin);

    /**
     * @brief Checks multiple digital pins for validity, using isDigitalPin(uint8_t pin)
     *
     * @param pins pin-numbers to be checked
     * @param pinsLength Size of pin-array
     * @return true all pins are valid
     * @return false one or more pins are invalid
     */
    bool isDigitalPin(uint8_t pins[], uint16_t pinsLength);

    /**
     * @brief Checks whether an analog pin is valid and exists
     *
     * @param pin Pin-number
     * @return true pin exists
     * @return false pin does not exist
     */
    bool isAnalogPin(uint8_t pin);
};
