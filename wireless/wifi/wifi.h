#pragma once
#include "wifi_sniffer.h"
#include <vector>
#include <Arduino.h>

// void initDisplay();
void showDeviceList(const std::vector<WiFiDevice>& list, int selected);
void showTextLines(const std::vector<String>& lines);

// butt.h


// #pragma once
// enum class ButtonEvent { NONE, UP, DOWN, OK };
// ButtonEvent readButton();

// butt.cpp

// #include "buttons.h"

// #define BTN_UP   32
// #define BTN_DOWN 33
// #define BTN_OK   25

// ButtonEvent readButton() {
//   if (!digitalRead(BTN_UP)) return ButtonEvent::UP;
//   if (!digitalRead(BTN_DOWN)) return ButtonEvent::DOWN;
//   if (!digitalRead(BTN_OK)) return ButtonEvent::OK;
//   return ButtonEvent::NONE;
// }

//menu.h

// #pragma once
// void showAttackModeMenu();
// void handleAttackModeInput();