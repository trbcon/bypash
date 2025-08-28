#pragma once
#include <RTClib.h>
#include <Arduino.h> 

extern RTC_DS3231 rtc;
extern String NowTimeStr;
extern bool isWatchOK;

void WatchInit();
void WatchDraw();