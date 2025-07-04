#include <../menu/menu.h>
#include "../display/display.h"

TFT_eSPI tft = TFT_eSPI();
RTC_DS3231 rtc;

String NowTimeStr;

void WatchInit() {
  if (!rtc.begin()) {
    Serial.println("RTC initialization failed");
    
    return;
  } else {
    isWatchOK = true;
  }
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void WatchDraw() {
  DateTime now = rtc.now();
  NowTimeStr = "";
  // Форматирование часов
  if(now.hour() < 10) NowTimeStr += "0";
  NowTimeStr += String(now.hour()) + ":";

  // Форматирование минут
  if(now.minute() < 10) NowTimeStr += "0";
  NowTimeStr += String(now.minute());

  tft.setCursor((160 - tft.textWidth(NowTimeStr)) / 2, 0);
  tft.println(NowTimeStr);
}

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
  tft.println(currentMenu->name);
  // tft.setTextSize(2);

  for (int i = 0; i < maxVisibleItems; i++) {
    int menuIndex = viewOffset + i;
    if (menuIndex >= currentMenu->items.size()) break;

    int y = (i + 1)* 8;

    if (menuIndex == selectedItem) {
      tft.setTextColor(TFT_YELLOW, TFT_BLACK);
      tft.setCursor(0, y);
      tft.print("> ");
    } else {
      tft.setCursor(0, y);
      tft.print("  ");
    }

    tft.setCursor(10, y);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.print(currentMenu->items[menuIndex]);
  }
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