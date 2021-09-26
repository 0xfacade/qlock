#pragma once
#include <RtcDateTime.h>

void setupRTC();
void saveTimeToRTC(const RtcDateTime& time);
RtcDateTime getTimeFromRTC();
bool isRtcTrusted();
