#include <Adafruit_NeoPixel.h>

#define N_LEDS 72
#define PIN     1

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  strip.begin();
}

int d1_pos = 0;
int d1_dir = 1;
void green_bounce() {
  strip.setPixelColor(d1_pos - 1, 0);
  strip.setPixelColor(d1_pos,     0x00FF00);
  strip.setPixelColor(d1_pos + 1, 0);

  d1_pos += d1_dir;
  if (d1_pos < 0) {
    d1_pos = 1;
    d1_dir = -d1_dir;
  }
  else if (d1_pos >= strip.numPixels()) {
    d1_pos = strip.numPixels();
    d1_dir = -d1_dir;
  }
}


int d2_pos = 15;
int d2_dir = -1;
void red_bounce() { 
  strip.setPixelColor(d2_pos - 1, 0);
  strip.setPixelColor(d2_pos,     0xFF0000);
  strip.setPixelColor(d2_pos + 1, 0);

  d2_pos += d2_dir;
  if (d2_pos < 0) {
    d2_pos = 1;
    d2_dir = -d2_dir;
  }
  else if (d2_pos >= strip.numPixels()) {
    d2_pos = strip.numPixels();
    d2_dir = -d2_dir;
  }
}

void loop() {
  green_bounce();
  red_bounce();
  strip.show();
  delay(15);
}
