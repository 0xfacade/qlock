#include <Arduino.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "creds.hpp"

#define WIFI_CONNECT_TIMEOUT_SECONDS 20

uint64_t getEpochFromWiFi() {
  WiFiUDP ntpUDP;
  NTPClient timeClient(ntpUDP);

  Serial.print("Connecting to WiFi to get time..");

  WiFi.begin(WIFI_NAME, WIFI_PASS);

  int waiting_time_millis = 0;
  while (WiFi.status() != WL_CONNECTED && waiting_time_millis < (WIFI_CONNECT_TIMEOUT_SECONDS * 1000)) {
      delay(500);
      Serial.print(".");
      waiting_time_millis += 500;
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Failed to connect.");
    return 0;
  }

  timeClient.begin();
  timeClient.forceUpdate();

  Serial.printf("Time is %s (epoch: %lu)\n", timeClient.getFormattedTime(), timeClient.getEpochTime());

  WiFi.disconnect();

  return timeClient.getEpochTime();
}
