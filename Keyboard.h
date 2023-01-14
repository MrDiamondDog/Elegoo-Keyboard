#include <Elegoo_GFX.h>
#include <Elegoo_TFTLCD.h>
#include <TouchScreen.h>
#include <Arduino.h>

#define MINPRESSURE 10
#define MAXPRESSURE 1000

#define TS_MINX 120
#define TS_MAXX 900

#define TS_MINY 70
#define TS_MAXY 920

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define ORANGE 0xFCA0
#define GRAY 0x2965
#define ACCENT_ORANGE 0xE4C0

#define PENRADIUS 5

#define MAXWIDTH 240
#define MAXHEIGHT 320
#define MIDWIDTH 120
#define MIDHEIGHT 160

class Keyboard {
private:
  Elegoo_GFX_Button buttons[33];
  bool numbers;
public:
  char text[22];
  int index;
  void open(Elegoo_TFTLCD *tft, bool textBoxFill = true);
  void drawButton(int i, int x, int y, char *label, Elegoo_TFTLCD *tft);
  void checkButtons(TSPoint p, Elegoo_TFTLCD *tft);
  char* getLabel(int i);
  void close();
};
