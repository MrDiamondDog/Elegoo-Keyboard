// Call this to render the keyboard
void Keyboard::open(Elegoo_TFTLCD *tft, bool textBoxFill = true) {
  tft->fillRect(0, 200, 240, 300, WHITE);
  if (textBoxFill) tft->fillRect(0, 175, 240, 25, GRAY);

  int total = 0;
  for (int row = 0; row < 3; row++) {
    for (int i = 0; i < 10; i++) {
      if (total == 21 || total == 20) {
        total++;
        continue;
      }
      drawButton(total, i * 24, row * 30 + 200, getLabel(total), tft);
      total++;
    }
  }

  buttons[20].initButton(tft, 24, 275, 48, 30, WHITE, MAGENTA, WHITE, (numbers) ? "ABC" : "123", 2);
  buttons[20].drawButton();

  buttons[31].initButton(tft, 108, 305, 216, 30, WHITE, ORANGE, WHITE, "SPACE", 2);
  buttons[31].drawButton();

  drawButton(32, 9 * 24, 3 * 30 + 200, "C", tft);
}

void Keyboard::drawButton(int i, int x, int y, char *label, Elegoo_TFTLCD *tft) {
  uint16_t color = ORANGE;

  if (i == 19) color = GREEN;
  if (i == 29) color = RED;
  if (i == 32) color = RED;
  buttons[i].initButton(tft, x + 12, y + 15, 24, 30, WHITE, color, WHITE, label, 2);
  buttons[i].drawButton();
}

// Call this in your loop function while the keyboard is open
void Keyboard::checkButtons(TSPoint p, Elegoo_TFTLCD *tft) {
  // Use this before passing in p, or uncomment the next lines
  // 
  // if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
  //   // scale from 0->1023 to tft.width
  //   p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
  //   p.y = (tft.height() - map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
  // }

  for (int i = 0; i < 33; i++) {
    if (buttons[i].contains(p.x, p.y)) {
      buttons[i].press(true);  // tell the button it is pressed
    } else {
      buttons[i].press(false);  // tell the button it is NOT pressed
    }

    if (buttons[i].justPressed()) {
      if (i == 19) {
        // enter
        Serial.println(text);
      } else if (i == 29) {
        // backspace
        index--;
        text[index] = *"";
        tft->fillRect(11 * index + 5, 175, 11, 25, GRAY);
        tft->setCursor(11 * index + 5, 180);
        if (index <= 0) index = 0;
      } else if (i == 20) {
        // numbers
        numbers = !numbers;
        open(tft, false);
      } else if (i == 32) {
        // clear
        index = 0;
        memset(text, 0, sizeof(text));
        tft->fillRect(0, 175, 240, 25, GRAY);
      } else {
        if (index <= 20) {
          text[index] = *getLabel(i);
          tft->setCursor(11 * index + 5, 180);
          tft->setTextColor(WHITE);
          tft->print(text[index]);
          index++;
        }
      }

      buttons[i].drawButton(true);

      delay(200);  // debounce
    }

    if (buttons[i].justReleased()) {
      buttons[i].drawButton();
    }
  }
}

// Call this before removing the keyboard in anyway, otherwise you will not be able to open it again
void Keyboard::close() {
  memset(text, 0, sizeof(text));
  memset(buttons, 0, sizeof(buttons));
  index = 0;
  numbers = false;
}

char *Keyboard::getLabel(int i) {
  // dont look at this
  switch (i) {
    case 0:
        return (numbers) ? "1" : "Q";
    case 1:
        return (numbers) ? "2" : "W";
    case 2:
        return (numbers) ? "3" : "E";
    case 3:
        return (numbers) ? "4" : "R";
    case 4:
        return (numbers) ? "5" : "T";
    case 5:
        return (numbers) ? "6" : "Y";
    case 6:
        return (numbers) ? "7" : "U";
    case 7:
        return (numbers) ? "8" : "I";
    case 8:
        return (numbers) ? "9" : "O";
    case 9:
        return (numbers) ? "0" : "P";
    case 10:
        return (numbers) ? "-" : "A";
    case 11:
        return (numbers) ? "/" : "S";
    case 12:
        return (numbers) ? ":" : "D";
    case 13:
        return (numbers) ? ";" : "F";
    case 14:
        return (numbers) ? "(" : "G";
    case 15:
        return (numbers) ? ")" : "H";
    case 16:
        return (numbers) ? "{" : "J";
    case 17:
        return (numbers) ? "}" : "K";
    case 18:
        return (numbers) ? "$" : "L";
    case 19:
        return (numbers) ? ">" : ">";
    case 20:
        return (numbers) ? "1" : "1";
    case 21:
        return (numbers) ? "@" : "@";
    case 22:
        return (numbers) ? "&" : "Z";
    case 23:
        return (numbers) ? "@" : "X";
    case 24:
        return (numbers) ? "." : "C";
    case 25:
        return (numbers) ? "," : "V";
    case 26:
        return (numbers) ? "'" : "B";
    case 27:
        return (numbers) ? "?" : "N";
    case 28:
        return (numbers) ? "!" : "M";
    case 29:
        return (numbers) ? "<" : "<";
    case 30:
        return (numbers) ? " " : " ";
    case 31:
        return (numbers) ? " " : " ";
  }
}
