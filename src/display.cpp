#include <FastLED.h>
#include <array>
#include "words.hpp"

FASTLED_USING_NAMESPACE

#define DATA_PIN        26
#define NUM_LEDS        110
#define BRIGHTNESS      100

#define REVERSE_ORDER

CRGB leds[NUM_LEDS];

void clear() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
}

template<std::size_t len> 
void addWord(const std::array<int, len>& word) {
  for (int i = 0; i < len; i++) {
    #ifdef REVERSE_ORDER
    leds[110 - word[i] - 1] = CRGB::White;
    #else
    leds[word[i]] = CRGB::White;
    #endif
  }
}

void displayTime(const int hoursIn, const int minutes) {
  int hours = hoursIn;;
  clear();
  addWord(ES_IST);

  switch (minutes / 5) {
    case 0: // ES IST .. UHR
      addWord(UHR);
      break;
    case 1: // ES IST FUENF NACH ..
      addWord(M_FUENF);
      addWord(NACH);
      break;
    case 2: // ES IST ZEHN NACH ..
      addWord(M_ZEHN);
      addWord(NACH);
      break;
    case 3: // ES IST VIERTEL NACH ..
      addWord(M_VIERTEL);
      addWord(NACH);
      break;
    case 4: // ES IST ZWANZIG NACH ..
      addWord(M_ZWANZIG);
      addWord(NACH);
      break;
    case 5: // ES IST FÜNF VOR HALB ..
      addWord(M_FUENF);
      addWord(VOR);
      addWord(M_HALB);
      hours++;
      break;
    case 6: // ES IST HALB ..
      addWord(M_HALB);
      hours++;
      break;
    case 7: // ES IST FUENF NACH HALB
      addWord(M_FUENF);
      addWord(NACH);
      addWord(M_HALB);
      hours++;
      break;
    case 8: // ES IST ZWANZIG VOR
      addWord(M_ZWANZIG);
      addWord(VOR);
      hours++;
      break;
    case 9:
      addWord(M_VIERTEL);
      addWord(VOR);
      hours++;
      break;
    case 10:
      addWord(M_ZEHN);
      addWord(VOR);
      hours++;
      break;
    case 11:
      addWord(M_FUENF);
      addWord(VOR);
      hours++;
      break;
  }

  hours = hours % 12;

  switch(hours) {
    case 0:
      addWord(H_ZWOELF);
      break;
    case 1:
      if (minutes / 5 == 0) {
        addWord(H_EIN);
      } else {
        addWord(H_EINS);
      }
      break;
    case 2:
      addWord(H_ZWEI);
      break;
    case 3:
      addWord(H_DREI);
      break;
    case 4:
      addWord(H_VIER);
      break;
    case 5:
      addWord(H_FUENF);
      break;
    case 6:
      addWord(H_SECHS);
      break;
    case 7:
      addWord(H_SIEBEN);
      break;
    case 8:
      addWord(H_ACHT);
      break;
    case 9:
      addWord(H_NEUN);
      break;
    case 10:
      addWord(H_ZEHN);
      break;
    case 11:
      addWord(H_ELF);
      break;
  }

  FastLED.show();
}

void setupDisplay() {
  FastLED.addLeds<WS2812B,DATA_PIN,GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  clear();
}
