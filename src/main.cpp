#include "./controller/stepper/Stepper.h"

stepperConfiguration_s spoolConfig = {.stepperId = "spool",
                         .maxCurrent = 700,
                         .microstepsPerStep = 32,
                         .stepsPerRotation = 200,
                         .mmPerRotation = 10,
                         .pins = {
                            .en = 12,
                            .dir = 16,
                            .step = 26,
                            .cs = 5,
                        }
};
stepperConfiguration_s ferrariConfig = {.stepperId = "ferrari",
                         .maxCurrent = 700,
                         .microstepsPerStep = 32,
                         .stepsPerRotation = 200,
                         .mmPerRotation = 10,
                        .pins = { // Pins of ferrari
                        .en = 12,
                        .dir = 14,
                        .step = 17,
                        .cs = 13,
                        }
};
stepperConfiguration_s pullerConfig = {.stepperId = "puller",
                         .maxCurrent = 700,
                         .microstepsPerStep = 32,
                         .stepsPerRotation = 200,
                         .mmPerRotation = 10,
                         .pins = { // Pins of puller
                        .en = 12,
                        .dir = 27,
                        .step = 25,
                        .cs = 2,
                         }
};

FastAccelStepperEngine engine = FastAccelStepperEngine();
Stepper spool = Stepper(spoolConfig, &engine);
Stepper ferrari = Stepper(ferrariConfig, &engine);
Stepper puller = Stepper(pullerConfig, &engine);

void setup() {
    SPI.begin();
    Serial.begin(115200);

    // Initalisation
    engine.init();
    spool.init();
    puller.init();
    ferrari.init();

    // Set starting commands
    puller.moveRotate(-20);
    spool.moveRotate(50);
    ferrari.movePosition(80, 100);
    
}

void loop() {
    // Handle commands sent by user via terminal
    if(Serial.available() > 0){
        uint8_t newCommand = Serial.read();
        switch(newCommand){
            // Basic commands
            case 'h': // Home
                Serial.println("[CMD]: home()");
                ferrari.moveHome(30);
                break;
            case 'o': // Oscillate
                Serial.println("[CMD]: moveOscillate()");
                ferrari.moveOscillate(40, 50, 90);
                break;
            case 'p': // Position
                Serial.println("[CMD]: movePosition()");
                ferrari.movePosition(40, 80);
                break;
            case 'r': // Rotate
                Serial.println("[CMD]: moveRotate()");
                ferrari.moveRotate(40);
                break;
            case 'R': // Rotate
                Serial.println("[CMD]: moveRotate()");
                ferrari.moveRotate(-40);
                break;
            case 'a': // Adjust
                Serial.println("[CMD]: moveRotateWithLoadAdjust()");
                ferrari.moveRotateWithLoadAdjust(40, 60);
                break;
            case 'x': // mode off
                Serial.println("[CMD]: switchModeOff()");
                ferrari.switchModeOff();
                break;
            case 's': // mode standby
                Serial.println("[CMD]: switchModeStandby()");
                ferrari.switchModeStandby();
                break;
            case 'l': // print out long debugging message
                Serial.println("[CMD]: enable debugging, printStatusLong()");
                ferrari.printStatus(true);
                break;
            case 'd': // enable debugging
                Serial.println("[CMD]: enable debugging");
                ferrari.setDebuggingLevel(INFO);
                break;
            case 'D': // disable  debugging
                Serial.println("[CMD]: disable debugging");
                ferrari.setDebuggingLevel(NONE);
                break;
            // Debug-related 'programs', adjust as needed
            case '1':
                Serial.println("[CMD]: debug procedure 1");
                ferrari.adjustMoveSpeed(150);
                break;
            case '2':
                Serial.println("[CMD]: debug procedure 2");
                ferrari.adjustMovePositions(50, 130);
                break;
            case '3':
                Serial.println("[CMD]: debug procedure 3");
                ferrari.adjustMovePositions(90, 110);
                break;
            case '4':
                Serial.println("[CMD]: debug procedure 4");
                ferrari.adjustMovePositions(120, 30);
                break;
            case '5':
                Serial.println("[CMD]: debug procedure 5");
                break;
            case '6':
                Serial.println("[CMD]: debug procedure 6");
                break;
            default:
                Serial.println("[CMD] Unknown command - input ignored");
        };
    }

    // Let the stepper do its thing for a second
    for(int i=0; i<10; ++i){
        for(int k=0; k<10; ++k){
            spool.handle();
            ferrari.handle();
            puller.handle();
            delay(10); // TODO: Delay only to prevent a debug-message-flood
        }
        //spool.printStatus(false);
        ferrari.printStatus(false);
        //puller.printStatus(false);
    }
    //spool.printStatus(true);
    ferrari.printStatus(true);
    //puller.printStatus(true);
}