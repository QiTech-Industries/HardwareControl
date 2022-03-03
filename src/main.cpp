#include "./controller/stepper/Stepper.h"

stepperConfiguration_s spoolConfig = {
    .stepperId = "spool",
    .maxCurrent = 700,
    .microstepsPerStep = 32,
    .stepsPerRotation = 200,
    .mmPerRotation = 2800,
    .gearRatio = 5.18,
    .pins = {
        .en = 12,
        .dir = 16,
        .step = 26,
        .cs = 5,
    }
};
stepperConfiguration_s ferrariConfig = {
    .stepperId = "ferrari",
    .maxCurrent = 700,
    .microstepsPerStep = 32,
    .stepsPerRotation = 200,
    .mmPerRotation = 10,
    .gearRatio = 1,
    .pins = {
        .en = 12,
        .dir = 14,
        .step = 17,
        .cs = 13,
    }
};
stepperConfiguration_s pullerConfig = {
    .stepperId = "puller",
    .maxCurrent = 700,
    .microstepsPerStep = 32,
    .stepsPerRotation = 200,
    .mmPerRotation = 10,
    .gearRatio = 1,
    .pins = {
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
    // ferrari.movePosition(80, 80);
}

void loop() {
    // Handle commands sent by user via terminal
    if(Serial.available() > 0){
        uint8_t newCommand = Serial.read();
        switch(newCommand){
            // Basic commands
            case 'h': // Home
                Serial.println("[CMD]: home()");
                ferrari.moveHome(60);
                break;
            case 'p': // Position
                Serial.println("[CMD]: movePosition()");
                ferrari.movePosition(80, 80);
                break;


            case '1': // Oscillate
                Serial.println("[CMD]: 111111111111111111111()");
                puller.moveRotate(-30);
                spool.moveRotateWithLoadAdjust(-5, 50);
                // ferrari.moveOscillate(30, 80, 130);
                break;
            case '2': // Oscillate
                Serial.println("[CMD]: 222222222222222222222222()");
                puller.moveRotate(-30);
                spool.moveRotateWithLoadAdjust(-10, 50);
                // ferrari.moveOscillate(30, 80, 130);
                break;
            case '3': // Oscillate
                Serial.println("[CMD]: 333333333333333333333333333333333()");
                puller.moveRotate(-30);
                spool.moveRotateWithLoadAdjust(-20, 50);
                // ferrari.moveOscillate(30, 80, 130);
                break;
            case '4': // Oscillate
                Serial.println("[CMD]: 44444444444444444444444444444444()");
                puller.moveRotate(-30);
                spool.moveRotateWithLoadAdjust(-30, 50);
                // ferrari.moveOscillate(30, 80, 130);
                break;

            case 'q':
                ferrari.movePosition(70, 50);
                break;
            case 'b':
                ferrari.movePosition(70, 100);
                break;
            case 'c':
                ferrari.moveOscillate(70, 50, 100);
                break;
            case 'v':
                ferrari.adjustMoveSpeed(30);
                break;
            case 'V':
                ferrari.adjustMoveSpeed(-30);
                break;


            case 'u': // Unwind
                Serial.println("[CMD]: moveRotate()");
                spool.switchModeOff();
                puller.moveRotate(60);
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
                Serial.println("[CMD]: switchModeStandby()");
                spool.switchModeStandby();
                ferrari.switchModeStandby();
                puller.switchModeStandby();
                break;
            case 'X': // mode standby
                Serial.println("[CMD]: switchModeOff()");
                spool.switchModeOff();
                ferrari.switchModeOff();
                puller.switchModeOff();
                break;
            case 'l': // print out long debugging message
                Serial.println("[CMD]: enable debugging, printStatusLong()");
                ferrari.printStatus(true);
                break;
            case 'd': // enable debugging
                Serial.println("[CMD]: enable debugging");
                //ferrari.setDebuggingLevel(INFO);
                break;
            case 'D': // disable  debugging
                Serial.println("[CMD]: disable debugging");
                //ferrari.setDebuggingLevel(NONE);
                break;
            // Debug-related 'programs', adjust as needed
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
        //ferrari.printStatus(false);
        //puller.printStatus(false);
    }
    //spool.printStatus(true);
    //ferrari.printStatus(true);
    //puller.printStatus(true);
}