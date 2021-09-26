#include<Arduino.h>
#include "rtc.hpp"
#include "timezone.hpp"
#include "wifitime.hpp"
#include "FastLED.h"

#define TIME_SYNC_INTERVAL_SECONDS (60 * 60)

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("Hi!");
  delay(1000);
}


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
  saveTimeToRTC(rtcTime);
  return true;
}


void main2() {
  
  while (true) {
    if (shouldSyncRtcFromNtp()) {
      bool success = syncRtcFromNtp();
      if (success) {
        lastTimeSyncEpoch = getTimeFromRTC().Epoch64Time();
      }
    }
    
    if (!isRtcTrusted()) {
      Serial.println("Rtc is not trusted. Skipping display of time.");
      continue;
    }
    
    
  }
}
