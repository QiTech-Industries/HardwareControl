#include "DcMotor.h"

#include <Arduino.h>

DcMotor::DcMotor(motorConfiguration_s config) { _config = config; }

void DcMotor::modeToString(const mode_e mode, char* out) {
    const char* modes[3] = {"left", "right", "off"};
    strcpy(out, modes[mode]);
}

void IRAM_ATTR DcMotor::handleInterrupt() {
    // direct register manipulation would be faster here
    if (digitalRead(_config.pins.encoderB))
        _ticks++;
    else
        _ticks--;
}

void DcMotor::turnRightPwm(uint16_t speedPwm) {
    analogWrite(_config.pins.rightTurn, speedPwm);
    analogWrite(_config.pins.leftTurn, 0);
    _currentMode = RIGHT;
};

void DcMotor::turnLeftPwm(uint16_t speedPwm) {
    analogWrite(_config.pins.leftTurn, speedPwm);
    analogWrite(_config.pins.rightTurn, 0);
    _currentMode = LEFT;
};

int32_t DcMotor::getPosition() { return _ticks; }

bool DcMotor::isMoving() { return _currentMode != OFF; }

void DcMotor::resetPosition() { _ticks = 0; }

void DcMotor::off() {
    analogWrite(_config.pins.leftTurn, 0);
    analogWrite(_config.pins.leftTurn, 0);
    _currentMode = OFF;
    _braking = false;
};

void DcMotor::brake() {
    if (_braking || _currentMode == OFF) return;
    if (_currentMode == LEFT)
        turnRightPwm(255);
    else
        turnLeftPwm(255);
    _braking = true;
}

float DcMotor::getCurrentSpeed() { return _currentSpeedRpm; }

void DcMotor::handle() {
    if (_braking && _currentMode == LEFT && _lastTicks > _ticks)
        off();
    else if (_braking && _currentMode == RIGHT && _lastTicks < _ticks)
        off();
    if (millis() - _lastMillis >= MEASURE_INTERVAL_MS) {
        // cast from unsigned long to long to avoid faulty results by auto cast of expression to unsigned
        _currentSpeedRpm = (_ticks - _lastTicks) * 60000 / (long)(millis() - _lastMillis) / _config.ticksPerRotation;
        _lastTicks = _ticks;
        _lastMillis = millis();

        char mode[10];
        modeToString(_currentMode, mode);
        logPrint(LOG_LEVEL, INFO, "dcMotor: {id: '%s', rpm: %.2f, position: %i, mode: %s}\n", _config.motorId, _currentSpeedRpm, _ticks,
                 mode);
    }
}

void DcMotor::init(void (*interrupt)()) {
    Serial.begin(115200);
    pinMode(_config.pins.rightTurn, OUTPUT);
    pinMode(_config.pins.leftTurn, OUTPUT);
    pinMode(_config.pins.encoderA, INPUT_PULLUP);
    pinMode(_config.pins.encoderB, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(_config.pins.encoderA), interrupt, FALLING);
}
