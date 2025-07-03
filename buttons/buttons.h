#pragma once
#include <Arduino.h>
#include <cstring>
#include "../menu/menu.h"
#include "../notifications/notifications.h"

// ─── Пины ─────────────────────────
#define BTN_UP     32
#define BTN_DOWN   33
#define BTN_LEFT   25
#define BTN_RIGHT  26
#define BTN_OK     27

#define LONG_PRESS_TIME    500
#define DOUBLE_CLICK_TIME  300

// ─── Глобальные переменные меню ──
extern bool        isMenu;
extern bool        isNotifications;
extern Menu*       currentMenu;
extern int         selectedItem;
extern void        handleBack();
extern void        handleOk();
extern void        notificationsMenu();
extern void        selectMenu(bool &isSomething);

// ─── Поддержка клавиатуры ─────────
extern bool        keyboardActive;

// ─── Структура ────────────────────
struct ButtonState {
  int pin;
  bool isPressed = false;
  bool longPressHandled = false;
  bool waitingDouble = false;
  unsigned long pressStartTime = 0;
  unsigned long lastReleaseTime = 0;

  ButtonState(int p) : pin(p) {}
};

void ButtonSetup();
void ButtonUpdate();
void onSingleClick(const char* name);
void onDoubleClick(const char* name);
void onLongPress(const char* name);