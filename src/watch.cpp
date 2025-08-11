#include "../display/watch.h"
#include "../display/display.h"



RTC_DS3231 rtc;

String NowTimeStr;

void WatchInit() {
  if (!rtc.begin()) {
    Serial.println("RTC initialization failed");
    
    return;
  } else {
    isWatchOK = true;
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
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