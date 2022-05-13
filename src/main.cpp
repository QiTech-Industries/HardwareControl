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
    .mmPerRotation = 8,
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

uint16_t TEMP_SPEED_RPM = 5;

void setup() {
    SPI.begin();
    Serial.begin(115200);
    Serial.println("\n-----------------");

    // Initalisation
    engine.init();
    spool.init();
    puller.init();
    ferrari.init();

    McValidatorEsp32 testValidator;
    uint8_t pins[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    uint16_t pinLen = 10;
    Serial.printf("digiPinTest: %d\n", testValidator.isDigitalPin(pins, pinLen));

    // Set starting commands
    // ferrari.movePosition(80, 80);
}

void loop() {
    // Handle commands sent by user via terminal
    if(Serial.available() > 0){
        uint8_t newCommand = Serial.read();
        switch(newCommand){
            // Basic commands
            case 'c':
                spool.moveRotate(3);
                spool.handle();
                for(int i=0;i<5;++i){
                    delay(1000);
                    Serial.print(".");
                }
                Serial.print("\n");
                for(int i=3; i<=100; ++i){
                    spool.adjustMoveSpeed(i);
                    spool.handle();
                    delay(2000);
                    Serial.printf("rpm;%d;", i);
                    for(int k=0; k<50; ++k){
                        delay(100);
                        Serial.printf("%d%c", spool.getCurrentStall(), (k==49 ? '\n': ';'));
                    }
                }
                spool.switchModeOff();
                break;
            case 'h': // Home
                Serial.println("[CMD]: home()");
                //ferrari.moveHome(70);
                ferrari.movePosition(70, 63);
                break;
            case 'H': // Home
                Serial.println("[CMD]: home()");
                ferrari.moveOscillate(2, 63, 108);
                break;
            case 'p': // Position
                Serial.println("[CMD]: movePosition()");
                ferrari.movePosition(80, 80);
                break;
            
            case '.':
                spool.moveRotateWithLoadAdjust(TEMP_SPEED_RPM, 0);
                break;
            case '+':
                Serial.printf("\nSpeed+: %d\t", TEMP_SPEED_RPM);
                TEMP_SPEED_RPM += 1;
                spool.adjustMoveSpeed(TEMP_SPEED_RPM);
                break;
            case '-':
                TEMP_SPEED_RPM -= 1;
                Serial.printf("\nSpeed-: %d\t", TEMP_SPEED_RPM);
                spool.adjustMoveSpeed(TEMP_SPEED_RPM);
                break;

            case '1': // Oscillate
                Serial.println("[CMD]: 111111111111111111111()");
                puller.moveRotate(-20);
                spool.moveRotateWithLoadAdjust(-5, 5);
                // ferrari.moveOscillate(30, 80, 130);
                break;
            case '2': // Oscillate
                Serial.println("[CMD]: 222222222222222222222222()");
                puller.moveRotate(-30);
                spool.moveRotateWithLoadAdjust(-7.5, 5);
                // ferrari.moveOscillate(30, 80, 130);
                break;
            case '3': // Oscillate
                Serial.println("[CMD]: 333333333333333333333333333333333()");
                puller.moveRotate(-40);
                spool.moveRotateWithLoadAdjust(-10, 5);
                // ferrari.moveOscillate(30, 80, 130);
                break;
            case '4': // Oscillate
                Serial.println("[CMD]: 44444444444444444444444444444444()");
                puller.moveRotate(-50);
                spool.moveRotateWithLoadAdjust(-12.5, 5);
                // ferrari.moveOscillate(30, 80, 130);
                break;
            case '5':
                Serial.println("[CMD]: 555555555555555555()");
                puller.moveRotate(-60);
                spool.moveRotateWithLoadAdjust(-15, 5);
                break;
            case '6':
                Serial.println("[CMD]: 666666666666()");
                puller.moveRotate(-80);
                spool.moveRotateWithLoadAdjust(-20, 5);
                break;
            case '7':
                Serial.println("[CMD]: 777777777777777()");
                puller.moveRotate(-100);
                spool.moveRotateWithLoadAdjust(-25, 5);
                break;
            case '8':
                Serial.println("[CMD]: 88888888888888888()");
                puller.moveRotate(-120);
                spool.moveRotateWithLoadAdjust(-30, 5);
                break;
            case '9':
                Serial.println("[CMD]: 999999999999999999()");
                puller.moveRotate(-140);
                spool.moveRotateWithLoadAdjust(-35, 5);
                break;
            case '0':
                Serial.println("[CMD]: 000000000000000000000()");
                puller.moveRotate(-160);
                spool.moveRotateWithLoadAdjust(-40, 5);
                break;

            case 'q':
                ferrari.movePosition(70, 80);
                break;
            case 'b':
                ferrari.movePosition(70, 100);
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
                puller.moveRotate(40);
                break;
            case 'R': // Rotate
                Serial.println("[CMD]: moveRotate()");
                ferrari.moveRotate(-40);
                break;
            case 'a': // Adjust
                Serial.println("[CMD]: moveRotateWithLoadAdjust()");
                ferrari.moveRotateWithLoadAdjust(40, 5);
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
