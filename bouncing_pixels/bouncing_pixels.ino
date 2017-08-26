#include <Adafruit_NeoPixel.h>

#define N_LEDS 72
#define PIN     1
#define MAX_LOOPS 5

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);
int pixelVal[N_LEDS];

class BouncingPixel
{
  private:
    int _pos, _dir, _color;
    Adafruit_NeoPixel _strip;

  public:
    BouncingPixel(Adafruit_NeoPixel strip, int color);
    next();
};

BouncingPixel::BouncingPixel(Adafruit_NeoPixel strip, int color) {
  _color = color;
  _strip = strip;
  _pos = random(0, _strip.numPixels());
}

BouncingPixel::next() {
  _strip.setPixelColor(_pos, _color);
  
  _pos += _dir;
  if (_pos < 0) {
    _pos = 1;
    _dir = -_dir;
  }
  else if (_pos >= _strip.numPixels()) {
    _pos = _strip.numPixels();
    _dir = -_dir;
  }

  return _pos;
}

void setup() {
  strip.begin();

  // Initialize pixel array
  for (int i = 0; i < N_LEDS; i++) {
    pixelVal[i] = 0;
  }
}


/*
 
void (*displays[])() = {green_bounce, red_bounce};

int loop_count = 0;
int current_display = 0;
int max_displays = sizeof(displays);
*/

void loop() {
  // increment our looping count
  /*
  if (loop_count >= MAX_LOOPS) {
    current_display++;
    loop_count = 0;
  }

  if (current_display >= MAX_DISPLAYS) {
    current_display = 0;
  }*/
  green_bounce();
  red_bounce();
  strip.show();
  delay(15);
}
