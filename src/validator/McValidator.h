#pragma once

// Related
// System / External
#include <stdint.h>
// Selfmade
// Project

/**
 * @brief Validator for a microcontroller, for example for checking whether a pin exists and is of a specified type
 */
class McValidator{
    public:
        /**
         * @brief Checks whether a digital pin is valid and exists
         * 
         * @param pin Pin-number
         * @return true pin exists
         * @return false pin does not exist
         */
        bool isDigitalPinValid(uint8_t pin);

        /**
         * @brief Checks whether an analog pin is valid and exists
         * 
         * @param pin Pin-number
         * @return true pin exists
         * @return false pin does not exist
         */
        bool isAnalogPinValid(uint8_t pin);

        /**
         * @brief Checks multiple digital pins for validity, using isDigitalPinValid()
         * 
         * @param pins pin-numbers to be checked
         * @param pinsLength Size of pin-array
         * @return true all pins are valid
         * @return false one or more pins are invalid
         */
        bool isDigitalPinsValid(uint8_t pins[], uint16_t pinsLength);
};
