// Related
#include "logging.h"
// System / External
#include <Arduino.h>
// Selfmade
// Project

bool isLogRelevant(loggingLevel_e currentLevel, loggingLevel_e messageLevel){
    return currentLevel >= messageLevel;
}

void logPrint(loggingLevel_e currentLevel, loggingLevel_e messageLevel, const char* message, ...){
    if(!isLogRelevant(currentLevel, messageLevel)) return;

    // Set color according to messagelevel
    switch(messageLevel){
        case NONE:
            break;
        case CRITICAL:
            Serial.print("\x1B[31m");
            break;
        case ERROR:
            Serial.print("\x1B[31m");
            break;
        case WARNING:
            Serial.print("\x1B[33m");
            break;
        case INFO:
            Serial.print("\x1B[36m");
            break;
    }

    // Adjusted copypasta from Print.cpp
    char loc_buf[64];
    char * temp = loc_buf;
    va_list arg;
    va_list copy;
    va_start(arg, message);
    va_copy(copy, arg);
    int len = vsnprintf(temp, sizeof(loc_buf), message, copy);
    va_end(copy);
    if(len < 0) {
        va_end(arg);
        return;
    };
    if(len >= sizeof(loc_buf)){
        temp = (char*) malloc(len+1);
        if(temp == NULL) {
            va_end(arg);
            return;
        }
        len = vsnprintf(temp, len+1, message, arg);
    }
    va_end(arg);
    len = Serial.write((uint8_t*)temp, len);
    if(temp != loc_buf){
        free(temp);
    }

    // reset color
    Serial.print("\033[0m");
}

// TODO
void testIsLogRelevant(){
    isLogRelevant(WARNING, NONE) == true;
    isLogRelevant(CRITICAL, WARNING) == false;
    isLogRelevant(ERROR, ERROR) == true;
    isLogRelevant(NONE, ERROR) == false;
    isLogRelevant(NONE, NONE) == true;
    isLogRelevant(CRITICAL, NONE) == true;
}