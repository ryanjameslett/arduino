#include <Adafruit_NeoPixel.h>

#define N_LEDS 72
#define PIN     1
#define MAX_LOOPS 5


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


Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);
int pixelVal[N_LEDS];

void setup() {
  strip.begin();

  // Initialize pixel array
  for (int i = 0; i < N_LEDS; i++) {
    pixelVal[i] = 0;
  }
}

void loop() {
  strip.show();
  delay(15);
}
