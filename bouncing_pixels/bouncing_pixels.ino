#include <Adafruit_NeoPixel.h>

#define N_LEDS 72
#define PIN     1
#define NUM_PIXELS 11

/**
 * Defines a single pixel that bounces from one end of the light strip to the other.
 */
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

/**
 * Empty constructor
 */
BouncingPixel::BouncingPixel() {  
}

/**
 * Constructor for initializing the pixel.
 * 
 * @param int strip_size The length of the led strip
 * @param double color The color of the pixel
 * @param int init_pos The initial position of the pixel (must be between 0 and N_LEDS)
 * @param int dir The initial direction of the pixel (1 goes up, -1 goes down)
 */
BouncingPixel::BouncingPixel(int strip_size, double color, int init_pos, int dir) {
  _color = color;
  _strip_size = strip_size;
  _pos = init_pos;
  _dir = dir;
}

/**
 * Retrive the next position on the strip for the pixel
 * 
 * @return int
 */
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

/**
 * Get the color of the pixel
 * 
 * @return double
 */
double BouncingPixel::color() {
  return _color;
}

/**
 * Global vars
 */
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);
BouncingPixel pixels[NUM_PIXELS];

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
 * Initialize the project
 */
void setup() {
  strip.begin();
  
  for (int i = 0; i < NUM_PIXELS; i++) {
    pixels[i] = BouncingPixel(
      N_LEDS, 
      wheel(random(1,255)), 
      random(0, N_LEDS-1), 
      random(-1,0)*-1
    );
  }
}

/**
 * Main loop
 */
void loop() {
  int loc;
  double color;

  for (int i = 0; i < NUM_PIXELS; i++) {
    loc = pixels[i].next();
    color = pixels[i].color();

    if (loc > 0) {
      strip.setPixelColor(loc-1, 0);
    }
    strip.setPixelColor(loc, color);

    if (loc < N_LEDS - 1) {
      strip.setPixelColor(loc+1, 0);
    }
  }
 
  strip.show();
  delay(15);
}


