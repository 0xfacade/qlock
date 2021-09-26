#include <Arduino.h>
#include <unity.h>
#include <timezone.hpp>

void setup() {
    delay(2000);
    UNITY_BEGIN();
}


void test_isSummerTime() {
  RtcDateTime time (2021, 9, 26, 15, 0, 0);

  RtcDateTime switches[] = {
    RtcDateTime(2021, 10, 31, 1, 0, 0),
    RtcDateTime(2022, 3, 27, 1, 0, 0),
    RtcDateTime(2022, 10, 30, 1, 0, 0),
    RtcDateTime(2023, 3, 26, 1, 0, 0),
    RtcDateTime(2023, 10, 29, 1, 0, 0)
  };

  RtcDateTime stop (2023, 12, 12, 1, 0, 0);

  bool summerTime = true;
  while (time < stop) {
    bool result = isSummerTime(time);
    TEST_ASSERT(result == summerTime);
    time += 3600;
    for (size_t i = 0; i < 5; i++) {
      if (time == switches[i]) {
        summerTime = !summerTime;
        break;
      }
    }
  }
}

void loop() {
    RUN_TEST(test_isSummerTime);
    UNITY_END();
}