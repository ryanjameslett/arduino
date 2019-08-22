#include <Adafruit_NeoPixel.h>

#define N_LEDS 72
#define PIN     1
#define NUM_PIXELS 11

double colors[NUM_PIXELS];
int positions[NUM_PIXELS];
int directions[NUM_PIXELS];

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

/**
 * Generate a color based on an value between 0 and 255
 * The colours are a transition r - g - b - back to r.
 * 
 * Stole this from the 'cyberpunk' sketch
 * 
 * @param byte WheelPos the desired position on the color wheel
 * @return strip.Color
 */
uint32_t wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

/**
 * Ideas:
 * - all pixels in a line - snake mode
 * - colour shift down the line
 * - 
 * - 
 * - 
 */


/**
 * Initialise Chaos mode
 */
void chaos_mode_init() {
  for (int i = 0; i < NUM_PIXELS; i++) {
    colors[i] = wheel(random(1,255));
    positions[i] = random(0, N_LEDS-1);
    directions[i] = random(-1,0) * -1;
  }
}


/**
 * Run through the chaos loop
 */
void chaos_mode_loop() {
  for (int i = 0; i < NUM_PIXELS; i++) {
    // get the next position
    positions[i] += directions[i];
    if (positions[i] < 0) {
      positions[i] = 1;
      directions[i] = -directions[i];
    }
    else if (positions[i] >= N_LEDS) {
      positions[i] = N_LEDS;
      directions[i] = -directions[i];
    }

    // write the pixel
    strip.setPixelColor(positions[i], colors[i]);

    // clean up after yourself
    if (positions[i] > 0) {
      strip.setPixelColor(positions[i]-1, 0);
    }
    if (positions[i] < N_LEDS - 1) {
      strip.setPixelColor(positions[i]+1, 0);
    }
  }
}

/**
 * Initialize the project
 */
void setup() {
  strip.begin();
  chaos_mode_init();
}

void loop() {
  chaos_mode_loop();
}
