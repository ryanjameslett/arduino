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
    BouncingPixel();
    BouncingPixel(int strip_size, double color, int init_pos, int dir);
    int next();
    double color();
};

BouncingPixel::BouncingPixel() {  
}

BouncingPixel::BouncingPixel(int strip_size, double color, int init_pos, int dir) {
  _color = color;
  _strip_size = strip_size;
  _pos = init_pos;
  _dir = dir;
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



#define NUM_PIXELS 11
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
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

BouncingPixel pixels[NUM_PIXELS];

void setup() {
  strip.begin();
  
  for (int i = 0; i < NUM_PIXELS; i++) {
    pixels[i] = BouncingPixel(N_LEDS, wheel(random(1,255)), random(0, N_LEDS-1), 1);
  }
}

void loop() {
  int loc;
  double color;

  for (int i = 0; i < NUM_PIXELS; i++) {
    loc = pixels[i].next();
    color = pixels[i].color();
    
    strip.setPixelColor(loc-1, 0);
    strip.setPixelColor(loc, color);
    strip.setPixelColor(loc+1, 0);
  }
 
  strip.show();
  delay(15);
}











