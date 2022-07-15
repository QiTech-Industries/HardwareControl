#pragma once
#include "../../logger/logging.h"
#include "../BaseController.h"

enum mode_e { LEFT, RIGHT, OFF };

/**
 * @brief Stepper hardware config that can not be changed
 *
 */
struct motorConfiguration_s {
    const char* motorId;        // motor identifier used in logs
    uint16_t ticksPerRotation;  // signals per shaft rotation * gear ratio
    struct Pins {
        uint8_t rightTurn;  // when this pin is set high motor turns right
        uint8_t leftTurn;   // when this pin is set high motor turns left
        uint8_t encoderA;   // one signal pin of the encoder
        uint8_t encoderB;   // other signal pin of the encoder
    } pins;
};

// TODO: inherit from BaseController although we have no ready() and different init() method
class DcMotor {
   private:
    const uint16_t MEASURE_INTERVAL_MS = 10;  // interval at which current speed is recalculated
    const loggingLevel_e LOG_LEVEL = INFO;    // class internal logging level

    // volatile variables can be written in ISR and main loop without beeing optimized away by compiler
    // int32 allows to run at full speed in one direction for 16 days straight
    volatile int32_t _ticks;
    int32_t _lastTicks = 0;
    bool _braking = false;
    mode_e _currentMode = OFF;
    unsigned long _lastMillis = 0;
    float _currentSpeedRpm = 0;
    motorConfiguration_s _config;

    /**
     * @brief Convert current mode to string for logging
     *
     * @param mode current mode (LEFT, RIGHT, OFF)
     * @param output pointer to place in memory where the string representation for mode will be stored
     */
    void modeToString(mode_e mode, char* output);

   public:
    DcMotor(motorConfiguration_s config);
    /**
     * @brief logic that needs to run repeatedly like arduino loop function
     *
     */
    void handle();

    /**
     * @brief initialize motor pins and interrupts like arduino setup function
     *
     * @param interrupt forwarding function of handleInterrupt() of current instance
     * needed because otherwise there is not possibility for the interrupt to know on which class instance the method should be called
     */
    void init(void (*interrupt)());

    /**
     * @brief Increment interrupt counter on interrupt immediately, no heavy lifting here
     *
     */
    void handleInterrupt();

    /**
     * @brief Get the current motor position in ticks
     *
     * @return int32_t motor position in ticks
     */
    int32_t getPosition();

    /**
     * @brief check if motor is currently rotating
     * 
     * @return true motor is currently turning
     * @return false motor has been stopped
     */
    bool isMoving();

    /**
     * @brief Cut off power to the motor which lets it turn with remaining inertia
     *
     */
    void off();

    /**
     * @brief actively brake the motor by turning in opposite direction, quickest way to stop
     *
     */
    void brake();

    /**
     * @brief Get the Current Speed in RPM
     *
     * @return float currentSpeedRpm positive if turning right, negative when left
     */
    float getCurrentSpeed();

    /**
     * @brief Let the motor rotate right with given pulse count
     *
     * @param speedPwm 0-255 pulses the motor receives
     */
    void turnRightPwm(uint16_t speedPwm);

    /**
     * @brief Let the motor rotate left with given pulse count
     *
     * @param speedPwm 0-255 pulses the motor receives
     */
    void turnLeftPwm(uint16_t speedPwm);

    /**
     * @brief Reset internal motor position to 0
     *
     */
    void resetPosition();
};
