#pragma once

void setupRTC();
bool getTimeFromRTC(int &hours, int &minutes);
void saveTimeToRTC(const int hours, const int minutes, const int seconds);
