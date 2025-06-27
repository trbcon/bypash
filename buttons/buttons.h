#pragma once
#include <Arduino.h>
#include <cstring>
#include "../menu/menu.h"

#define BTN_UP           32
#define BTN_DOWN         33
#define BTN_LEFT         25
#define BTN_RIGHT        26
#define BTN_OK           27

#define LONG_PRESS_TIME   500
#define DOUBLE_CLICK_TIME 300

extern bool        isMenu;
extern Menu*       currentMenu;
extern int         selectedItem;
extern void        handleBack();
extern void        handleOk();

struct ButtonState {
  int              pin;
  bool             isPressed        = false;
  bool             longPressHandled = false;
  bool             waitingDouble    = false;
  unsigned long    pressStartTime   = 0;
  unsigned long    lastReleaseTime  = 0;

  // инициализирует только pin, остальные поля получают default-значения
  ButtonState(int p) : pin(p) {}
};

void ButtonSetup();
void ButtonUpdate();
void onSingleClick(const char* name);
void onDoubleClick(const char* name);
void onLongPress(const char* name);