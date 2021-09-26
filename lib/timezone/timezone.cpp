#include <Arduino.h>
#include <RtcDateTime.h>

bool isSummerTime(const RtcDateTime& time) {  
  // In Europe, summertime starts on the last Sunday of March at 01:00 UTC
  // and ends on the last Sunday of October at 01:00 UTC

  if (time.Month() < 3 || time.Month() > 10) {
    // Jan, Feb, Nov, Dec are always winter time.
    return false;
  }

  if (time.Month() > 3 && time.Month() < 10) {
    // April, May, June, July, August and Sept. are always summer time
    return true;
  }

  if (time.Month() == 3) {
    // March has 31 days, so 4 weeks and 3 days
    
    int daysLeftInMonth = 31 - time.Day();
    // Day of week starts to count at Sunday = 0
    int daysToNextSunday = 7 - time.DayOfWeek();

    bool monthHasOtherSunday = daysLeftInMonth >= daysToNextSunday;

    // Before last sunday: monthHasOtherSunday is true
    // on last sunday: monthHasOtherSunday is false, isSunday is true
    // after: monthHasOtherSunday is false, isSunday is false

    if (monthHasOtherSunday) {
      // There is another Sunday in this month, so is is not yet summer time.
      return false;
    }

    if (!monthHasOtherSunday && time.DayOfWeek() == 0) {
      // It is the last Sunday of this month.
      return time.Hour() >= 1;
    }

    if (!monthHasOtherSunday && time.DayOfWeek() != 0) {
      return true;
    }
  }

  if (time.Month() == 10) {
    int daysLeftInMonth = 31 - time.Day();
    // Day of week starts to count at Sunday = 0
    int daysToNextSunday = 7 - time.DayOfWeek();

    bool monthHasOtherSunday = daysLeftInMonth >= daysToNextSunday;

    if (monthHasOtherSunday) {
      // There is another Sunday in this month, so is is still summer time.
      return true;
    }

    if (!monthHasOtherSunday && time.DayOfWeek() == 0) {
      // It is the last Sunday of this month.
      return time.Hour() < 1;
    }

    if (!monthHasOtherSunday && time.DayOfWeek() != 0) {
      return false;
    }
  }
}

RtcDateTime getTimeInBerlin(const RtcDateTime& utc) {
  if (isSummerTime(utc)) {
    return utc + 2 * 60 * 60;
  } else {
    return utc + 1 * 60 * 60;
  }
}

