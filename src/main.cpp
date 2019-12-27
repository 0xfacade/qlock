#include<Arduino.h>
#include<FastLED.h>
#include "display.h"
#include "wifitime.h"
#include "rtc.h"

void setup() {
    Serial.begin(115200);
    setupDisplay();
    setupRTC();
}

void loop() {
    int hours, minutes, seconds;
    getHoursMinutesFromWifi(hours, minutes, seconds);
    saveTimeToRTC(hours, minutes, seconds);
    
    while(true) {
        bool couldGetTime = getTimeFromRTC(hours, minutes);
        if (!couldGetTime) {
            Serial.println("Could not get time from RTC. Regetting from Wifi.");
            break;
        }
        displayTime(hours, minutes);
        FastLED.delay(1000);
    }
}