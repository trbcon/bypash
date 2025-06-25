#include <menu.h>
#include <RTClib.h>

RTC_DS3231 rtc;


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

String NowTimeStr;

void WatchInit() {
  try {
    rtc.begin();
    if (rtc.lostPower()) {
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    String hourStr, minStr, NowTimeStr;
  // rtc.setTime(2025, 1, 30, 12, 45, 0); // установить время вручную
  } catch (error_t) {
    return;
  }
}

void WatchDraw() {
  DateTime now = rtc.now();
  NowTimeStr = "";
  // Форматирование часов
  if(now.hour() < 10) NowTimeStr += "0";
  NowTimeStr += String(now.hour()) + ":";

  // Форматирование минут
  if(now.minute() < 10) NowTimeStr += "0";;
  NowTimeStr += String(now.minute());

  tft.setCursor((160 - tft.textWidth(NowTimeStr)) / 2, 0);
  tft.println(NowTimeStr);
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