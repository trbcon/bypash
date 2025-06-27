#include "../buttons/buttons.h"
#include <Arduino.h>
#include <cstring>

static ButtonState btns[] = {
  { BTN_UP },
  { BTN_DOWN },
  { BTN_LEFT },
  { BTN_RIGHT },
  { BTN_OK }
};

static const char* btnNames[] = {
  "UP", "DOWN", "LEFT", "RIGHT", "OK"
};

void ButtonSetup() {
  for (int i = 0; i < 5; i++) {
    pinMode(btns[i].pin, INPUT_PULLUP);
  }
}

void onSingleClick(const char* name) {
  if      (strcmp(name, "UP") == 0 && isMenu) {
    if (--selectedItem < 0) selectedItem = currentMenu->items.size() - 1;
  }
  else if (strcmp(name, "DOWN") == 0 && isMenu) {
    if (++selectedItem >= currentMenu->items.size()) selectedItem = 0;
  }
  else if (strcmp(name, "LEFT") == 0 && isMenu) {
    handleBack();
  }
  else if ((strcmp(name, "RIGHT") == 0 || strcmp(name, "OK") == 0) && isMenu) {
    handleOk();
  }
}

void onDoubleClick(const char* name) {
  if (strcmp(name, "LEFT") == 0 && isMenu) {
    handleBack();
  }
  // добавить остальные двойные клики по желанию
}

void onLongPress(const char* name) {
  if (strcmp(name, "UP") == 0) {
    // долгий UP
  }
  else if (strcmp(name, "OK") == 0) {
    // долгий OK
  }
}

void ButtonUpdate() {
  unsigned long now = millis();
  for (int i = 0; i < 5; i++) {
    ButtonState& btn = btns[i];
    bool pressed = (digitalRead(btn.pin) == LOW);

    // начало нажатия
    if (!btn.isPressed && pressed) {
      btn.isPressed        = true;
      btn.longPressHandled = false;
      btn.pressStartTime   = now;
    }

    // долгий клик
    if (btn.isPressed
        && !btn.longPressHandled
        && now - btn.pressStartTime >= LONG_PRESS_TIME) {
      btn.longPressHandled = true;
      onLongPress(btnNames[i]);
    }

    // отпускание
    if (btn.isPressed && !pressed) {
      btn.isPressed = false;
      if (!btn.longPressHandled) {
        if (now - btn.lastReleaseTime <= DOUBLE_CLICK_TIME) {
          onDoubleClick(btnNames[i]);
          btn.waitingDouble = false;
        } else {
          btn.lastReleaseTime = now;
          btn.waitingDouble  = true;
        }
      }
    }

    // одиночный клик
    if (btn.waitingDouble
        && now - btn.lastReleaseTime > DOUBLE_CLICK_TIME) {
      onSingleClick(btnNames[i]);
      btn.waitingDouble = false;
    }
  }
}