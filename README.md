# HardwareControl
This library provides controllers for basic active hardware modules such as selfregulating heaters and stepper motors.

# Controllers
## HeatController
TODO
## StepperController
TODO
### Example (24.02.2022)
```cpp
// main.cpp
#include <Stepper.h>

stepper_s stepperConfig = {.stepperId = "stepper",
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