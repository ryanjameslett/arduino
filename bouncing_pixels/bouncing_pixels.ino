#include <Adafruit_NeoPixel.h>

#define N_LEDS 72
#define PIN     1
#define MAX_LOOPS 5

class BouncingPixel
{
  private:
    int _pos, _dir, _strip_size;
    double _color;

  public:
    BouncingPixel(int strip_size, double color, int init_pos);
    int next();
    double color();
};

BouncingPixel::BouncingPixel(int strip_size, double color, int init_pos) {
  _color = color;
  _strip_size = strip_size;
  _pos = init_pos;
  _dir = 1;
}

int BouncingPixel::next() {
  _pos += _dir;
  if (_pos < 0) {
    _pos = 1;
    _dir = -_dir;
  }
  else if (_pos >= _strip_size) {
    _pos = _strip_size;
    _dir = -_dir;
  }

  return _pos;
}

double BouncingPixel::color() {
  return _color;
}

double RED = 0xFF0000;
double GREEN = 0x800000;
double BLUE = 0x0000FF;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);
double pixelVal[N_LEDS];
// BouncingPixel greenPixel = BouncingPixel(N_LEDS, 0x00FF00);
// BouncingPixel redPixel = BouncingPixel(N_LEDS, 0xFF0000, 1);
BouncingPixel pixels[3] = {
  BouncingPixel(N_LEDS, RED, 1),
  BouncingPixel(N_LEDS, GREEN, 6),
  BouncingPixel(N_LEDS, BLUE, 9)
};

void setup() {
  strip.begin();
}

void loop() {
  int loc;
  int color;

  for (int i = 0; i < 3; i++) {
    loc = pixels[i].next();
    color = pixels[i].color();
    
    strip.setPixelColor(loc-1, 0);
    strip.setPixelColor(loc, color);
    strip.setPixelColor(loc+1, 0);
  }
 
  strip.show();
  delay(15);
}











