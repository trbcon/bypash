// #pragma once
#include <Wire.h>

// секундомер
// #include <TFT_eSPI.h>
//   if (Serial.available()) {
//     char c = Serial.read();
//     if (c == 's') {
//       startMillis = millis();
//       running = true;
//       tft.fillScreen(TFT_BLACK);
//     } else if (c == 'e') {
//       running = false;
//       tft.setCursor(10, 100);
//       tft.setTextColor(TFT_RED);
//       tft.print("СТОП");

extern unsigned long startMillis;

struct TimeResult {
    unsigned long sec;
    unsigned long ms;
};


TimeResult StartStopwatch() {
    unsigned long elapsed = millis() - startMillis;
    TimeResult result;
    result.sec = elapsed / 1000;
    result.ms = elapsed % 1000;
    return result;
}



// unsigned long StartStopwatch() {
//     unsigned long elapsed = millis() - startMillis;
//     unsigned long sec = elapsed / 1000;
//     unsigned long ms = elapsed % 1000;
//     return sec, ms;
// }







// таймер
// #include <Wire.h>
// #include <TFT_eSPI.h>
// #include "RTClib.h"

// RTC_DS3231 rtc;
// TFT_eSPI tft = TFT_eSPI();

// DateTime endTime;
// bool timerRunning = false;

// void startTimer(uint16_t seconds) {
//   endTime = rtc.now() + TimeSpan(0, 0, 0, seconds); // 0дн 0ч 0м Xсек
//   timerRunning = true;
//   tft.fillScreen(TFT_BLACK);
// }

// void setup() {
//   Serial.begin(115200);
//   Wire.begin(21, 22);
//   rtc.begin();
//   tft.init();
//   tft.setRotation(1);
//   tft.fillScreen(TFT_BLACK);
//   tft.setTextColor(TFT_WHITE, TFT_BLACK);
//   tft.setTextSize(3);

//   startTimer(10); // Запуск таймера на 10 секунд
// }

// void loop() {
//   if (timerRunning) {
//     DateTime now = rtc.now();
//     int secondsLeft = (endTime - now).totalseconds();

//     if (secondsLeft <= 0) {
//       timerRunning = false;
//       tft.fillScreen(TFT_BLACK);
//       tft.setCursor(20, 40);
//       tft.print("Готово!");
//     } else {
//       tft.fillRect(0, 40, 160, 30, TFT_BLACK); // Очистка строки
//       tft.setCursor(20, 40);
//       tft.print("Осталось: ");
//       tft.print(secondsLeft);
//       tft.print("с");
//     }
//   }

//   delay(250);
// }
