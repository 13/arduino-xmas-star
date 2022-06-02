#include <Arduino.h>
#include <FastLED.h>
#include <Flame.h>

#define FASTLED_ALLOW_INTERRUPTS 0                            // Used for ESP8266.

// Fixed definitions cannot change on the fly.
#define LED_DT 4                                             // Serial data pin
#define COLOR_ORDER GRB                                       // It's GRB for WS2812B and GBR for APA102
#define LED_TYPE WS2812                                       // What kind of strip are you using (APA102, WS2801 or WS2812B)?
#define NUM_LEDS 1                                           // Number of LED's

// Initialize changeable global variables.
uint8_t max_bright = 255;                                     // Overall brightness definition. It can be changed on the fly.

struct CRGB leds[NUM_LEDS];                                   // Initialize our LED array.

Flame flame2;
Flame flame3;
Flame flame4;
Flame flame5;

void rainbow_wave(uint8_t thisSpeed, uint8_t deltaHue);

void setup() {
  Serial.begin(115200);

  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);         // For WS2812B

  FastLED.setBrightness(max_bright);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500); // FastLED power management set at 5V, 500mA
  
  flame2.setup(2,50,100);
  flame3.setup(3,15,50);
  flame4.setup(4,20,100);
  flame5.setup(5,30,150);
}

void loop() {
  rainbow_wave(2, 5);                                      // Speed, delta hue values.
  FastLED.show();

  flame2.flicker();
  flame3.flicker();
  flame4.flicker();
  flame5.flicker();
}

void rainbow_wave(uint8_t thisSpeed, uint8_t deltaHue) {     // The fill_rainbow call doesn't support brightness levels.
 //uint8_t thisHue = beatsin8(thisSpeed,0,255);                // A simple rainbow wave.
 uint8_t thisHue = beat8(thisSpeed,255);                     // A simple rainbow march.
 fill_rainbow(leds, NUM_LEDS, thisHue, deltaHue);            // Use FastLED's fill_rainbow routine.
}
