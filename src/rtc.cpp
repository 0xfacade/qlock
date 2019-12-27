#include<Arduino.h>
#include <ThreeWire.h>  
#include <RtcDS1302.h>

#define RTC_CLK 32
#define RTC_DAT 33
#define RTC_RST 25

ThreeWire myWire(RTC_DAT,RTC_CLK,RTC_RST); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

void setupRTC() {
    Rtc.Begin();

    if (!Rtc.GetIsRunning()) {
        Serial.println("RTC was not actively running, starting now.");
        Rtc.SetIsRunning(true);
    }
}

void saveTimeToRTC(const int hours, const int minutes, const int seconds) {
    if (Rtc.GetIsWriteProtected()) {
        Serial.println("RTC was write protected, enabling writing now.");
        Rtc.SetIsWriteProtected(false);
    }
    RtcDateTime t = RtcDateTime(2000, 1, 1, hours, minutes, seconds);
    Rtc.SetDateTime(t);
}

bool getTimeFromRTC(int &hours, int &minutes) {
    if (!Rtc.IsDateTimeValid()) {
        // Common Causes:
        //    1) first time you ran and the device wasn't running yet
        //    2) the battery on the device is low or even missing
        Serial.println("RTC lost confidence in the DateTime!");
        return false;
    }

    RtcDateTime now = Rtc.GetDateTime();
    hours = now.Hour();
    minutes = now.Minute();

    if (!now.IsValid())     {
        // Common Causes:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Serial.println("RTC lost confidence in the DateTime!");
        return false;
    }

    return true;
}
