#pragma once
#include <Wire.h>
#include "RTClib.h"


// секундомер
// #include <TFT_eSPI.h>

// TFT_eSPI tft = TFT_eSPI();
// bool running = false;
// unsigned long startMillis = 0;

// void setup() {
//   Serial.begin(115200);
//   tft.init();
//   tft.setRotation(1);
//   tft.fillScreen(TFT_BLACK);
//   tft.setTextColor(TFT_GREEN, TFT_BLACK);
//   tft.setTextSize(3);

//   tft.setCursor(10, 10);
//   tft.print("Нажми 's' для старта");
// }

// void loop() {
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
//     }
//   }

//   if (running) {
//     unsigned long elapsed = millis() - startMillis;
//     unsigned long sec = elapsed / 1000;
//     unsigned long ms = elapsed % 1000;

//     tft.fillRect(0, 40, 160, 30, TFT_BLACK); // Очистка
//     tft.setCursor(10, 40);
//     tft.setTextColor(TFT_GREEN);
//     tft.printf("%02lu.%03lu сек", sec, ms);
//   }

//   delay(50);
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
