#include <Arduino.h>
#include <FastLED.h>

FASTLED_USING_NAMESPACE

#define DATA_PIN    26
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    110

CRGB leds[NUM_LEDS];

#define BRIGHTNESS          100
#define FRAMES_PER_SECOND  120

void setup() {
  delay(500); // 3 second delay for recovery

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}
  
void loop()
{
  leds[0] = CRGB::White;
  leds[19] = CRGB::White;
  leds[39] = CRGB::White;
  leds[40] = CRGB::White;
  leds[60] = CRGB::White;

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 
}

