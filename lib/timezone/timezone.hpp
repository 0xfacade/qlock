#pragma once
#include <RtcDateTime.h>

/* Determines whether it is Daylight Saving Time in Western Europe */
bool isSummerTime(const RtcDateTime& time);

RtcDateTime getTimeInBerlin(const RtcDateTime& utc);
