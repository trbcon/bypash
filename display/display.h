#pragma once
#include <TFT_eSPI.h>
#include <RTClib.h>
#include <Arduino.h> 

extern TFT_eSPI tft;
extern RTC_DS3231 rtc;

extern String NowTimeStr;
extern bool isWatchOK;

void WatchInit();

void WatchDraw();

void displayInit();

void drawMenu();