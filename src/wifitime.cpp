#include <Arduino.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "creds.h"

void getHoursMinutesFromWifi(int &hours, int &minutes, int &seconds) {
    WiFiUDP ntpUDP;
    NTPClient timeClient(ntpUDP);

    Serial.print("Connecting to WiFi");
    WiFi.begin(WIFI_NAME, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    timeClient.begin();
    timeClient.setTimeOffset(3600);

    while(!timeClient.update()) {
        timeClient.forceUpdate();
    }

    hours = timeClient.getHours();
    minutes = timeClient.getMinutes();
    seconds = timeClient.getSeconds();

    WiFi.disconnect();
}