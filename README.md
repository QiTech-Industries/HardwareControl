# HardwareControl
This library provides controllers for basic active hardware modules such as selfregulating heaters and stepper motors.

# Controllers
## HeatController
TODO
### Example (25.02.2022)
```cpp
// main.cpp
/**
 * Example code for using 3 heat-controllers simultaneously
 */
#include <Arduino.h>
#include <HeatController.h>

HeatController heater1({
    .id = 1,
    .targetTemp = 200,
    .pinHeat = 26,
    .pinSensorSo = 16,
    .pinSensorCs = 17,
    .pinSensorSck = 25
});
HeatController heater2({
    .id = 2,
    .targetTemp = 200,
    .pinHeat = 27,
    .pinSensorSo = 13,
    .pinSensorCs = 12,
    .pinSensorSck = 14
});
HeatController heater3({
    .id = 3,
    .targetTemp = 200,
    .pinHeat = 5,
    .pinSensorSo = 18,
    .pinSensorCs = 19,
    .pinSensorSck = 23
});
HeatController controllerList[] = {heater1, heater2, heater3};
int controllerCount = 3;

void setup(){
    Serial.begin(115200);
    // Start controllers with valid configuration
    for(int i=0; i<controllerCount; ++i){
        if(controllerList[i].isReady()) controllerList[i].start();
    }

    // Make some of the controllers talk
    controllerList[0].setDebuggingLevel(WARNING);
    controllerList[controllerCount-1].setDebuggingLevel(INFO);
}

void loop(){
    for(int i=0; i<controllerCount; ++i){
        if(controllerList[i].isReady()) controllerList[i].handle();
    }
    delay(1); // Small delay to prevent message-flooding
}
```
## StepperController
TODO
### Example (25.02.2022)
```cpp
// main.cpp
#include <Stepper.h>

stepperConfiguration_s stepperConfig = {.stepperId = "stepper",
                         .maxCurrent = 700,
                         .microstepsPerStep = 32,
                         .stepsPerRotation = 200,
                         .mmPerRotation = 10,
                         .pins = {
                            .en = 12,
                            .dir = 14,
                            .step = 17,
                            .cs = 13,
                        }
};
FastAccelStepperEngine engine = FastAccelStepperEngine();
Stepper myStepper = Stepper(stepperConfig, &engine);

void setup() {
    SPI.begin();
    Serial.begin(115200);
    engine.init();
    myStepper.init();
    myStepper.setDebuggingLevel(INFO);
}

void loop() {
    // Issue command
    myStepper.movePosition(80, 100);

    // Let the handler do its magic
    while(true){
        myStepper.handle();
    };
}
```

# Licence
This library is property of QiTech Industries and must not be copied or distributed without permission.