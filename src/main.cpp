#include<Arduino.h>
#include <timezone.hpp>

#include "rtc.hpp"
#include "wifitime.hpp"
#include "display.hpp"

#define TIME_SYNC_INTERVAL_SECONDS (60 * 60)

uint64_t lastTimeSyncEpoch = 0;

bool shouldSyncRtcFromNtp() {
  return lastTimeSyncEpoch == 0
    || !isRtcTrusted()
    || ((getTimeFromRTC().Epoch64Time() - lastTimeSyncEpoch) >= TIME_SYNC_INTERVAL_SECONDS);
}

bool syncRtcFromNtp() {
  uint64_t currentTime = getEpochFromWiFi();
  if (currentTime == 0) {
    Serial.println("WiFi timed out.");
    return false;
  }

  RtcDateTime rtcTime;
  rtcTime.InitWithEpoch64Time(currentTime);
  Serial.printf("RTC set to %d:%d.%d %d.%d.%d\n", rtcTime.Hour(), rtcTime.Minute(), rtcTime.Second(), rtcTime.Day(), rtcTime.Month(), rtcTime.Year());
  RtcDateTime localTime = getTimeInBerlin(rtcTime);
  Serial.printf("Time in Berlin: %d:%d.%d %d.%d.%d\n", localTime.Hour(), localTime.Minute(), localTime.Second(), localTime.Day(), localTime.Month(), localTime.Year());

  saveTimeToRTC(rtcTime);
  return true;
}

void setup() {
  Serial.begin(115200);
  setupRTC();
  setupDisplay();
}

void loop() {
  if (shouldSyncRtcFromNtp()) {
    bool success = syncRtcFromNtp();
    if (success) {
      lastTimeSyncEpoch = getTimeFromRTC().Epoch64Time();
    }
  }
  
  if (!isRtcTrusted()) {
    Serial.println("Rtc is not trusted. Skipping display of time and waiting a bit longer.");
    delay(60 * 1000);
    return;
  }

  RtcDateTime utc = getTimeFromRTC();
  RtcDateTime berlinTime = getTimeInBerlin(utc);

  displayTime(berlinTime.Hour(), berlinTime.Minute());

  delay(500);
}
