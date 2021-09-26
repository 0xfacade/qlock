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

void saveTimeToRTC(const RtcDateTime& time) {
    Rtc.SetIsWriteProtected(false);
    Rtc.SetDateTime(time);
    Rtc.SetIsWriteProtected(true);
}

RtcDateTime getTimeFromRTC() {
    return Rtc.GetDateTime();
}

bool isRtcTrusted() {
    return Rtc.IsDateTimeValid();
}

