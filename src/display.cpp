#include <../menu/menu.h>
#include "../display/display.h"
#include "../display/watch.h"

TFT_eSPI tft = TFT_eSPI();



void displayInit() {
  tft.init();
  tft.setRotation(1);
  tft.setTextSize(1);  // Text size 1
  tft.setTextColor(TFT_WHITE);
  tft.fillScreen(TFT_BLACK);
}

void drawMenu() {
  int screenWidth = tft.width();
  tft.setTextSize(1);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  // tft.setTextSize(2);

  for (int i = 0; i < maxVisibleItems; i++) {
    int menuIndex = viewOffset + i;
    if (menuIndex >= currentMenu->items.size()) break;

    int y = (i + 1)* 8;

    if (menuIndex == selectedItem) {
      tft.setTextColor(TFT_PINK, TFT_BLACK);
      tft.setCursor(0, y);
      tft.print("> ");
    } else {
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.setCursor(0, y);
      tft.print("  ");
    }

    tft.setCursor(10, y);
    tft.print(currentMenu->items[menuIndex]);
  }
}


void drawTopBar() {
  tft.setTextSize(1);
  WatchDraw();
  tft.setCursor(0, 0);
  tft.setTextColor(TFT_PINK, TFT_BLACK);
  tft.println(currentMenu->name);
}


// int hour = now.hour();
// bool pm = false;

// if(hour > 12) {
//   hour -= 12;
//   pm = true;
// }
// else if(hour == 0) {
//   hour = 12;
// }
// else if(hour == 12) {
//   pm = true;
// }

// if(hour < 10) display.print('0');
// display.print(hour);
// display.print(':');
// if(now.minute() < 10) display.print('0');
// display.print(now.minute());
// display.print(pm ? " PM" : " AM");