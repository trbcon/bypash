#define BTN_UP     32
#define BTN_DOWN   33
#define BTN_LEFT   25
#define BTN_RIGHT  26
#define BTN_OK     27

#define LONG_PRESS_TIME   500
#define DOUBLE_CLICK_TIME 300

struct ButtonState {
  int pin;
  bool isPressed = false;
  bool longPressHandled = false;
  bool waitingDouble = false;
  unsigned long pressStartTime = 0;
  unsigned long lastReleaseTime = 0;
};

ButtonState btns[] = {
  {BTN_UP}, {BTN_DOWN}, {BTN_LEFT}, {BTN_RIGHT}, {BTN_OK}
};

const char* btnNames[] = {
  "UP", "DOWN", "LEFT", "RIGHT", "OK"
};


void ButtonSetup() {
  for (int i = 0; i < 5; i++) {
    pinMode(btns[i].pin, INPUT_PULLUP);
  }
}


void onSingleClick(const char* name) {
  if (strcmp(name, "UP") == 0) {
    if (isMenu) {
      selectedItem--;
      if (selectedItem < 0) selectedItem = currentMenu->items.size() - 1;
    }
  } else if (strcmp(name, "DOWN") == 0) {
    if (isMenu) {
      selectedItem++;
      if (selectedItem >= currentMenu->items.size()) selectedItem = 0;
    }
  } else if (strcmp(name, "LEFT") == 0) {
    if (isMenu) {
      handleBack();
    }
  } else if (strcmp(name, "RIGHT") == 0) {
    if (isMenu) {
      handleOk();
    }
  } else if (strcmp(name, "OK") == 0) {
    if (isMenu) {
      handleOk();
    }
  }
}

void onDoubleClick(const char* name) {
  if (strcmp(name, "UP") == 0) {
    
  } else if (strcmp(name, "DOWN") == 0) {
    
  } else if (strcmp(name, "OK") == 0) {
    
  }
}

void onLongPress(const char* name) {
  if (strcmp(name, "UP") == 0) {
    
  } else if (strcmp(name, "OK") == 0) {
    
  }
}



void ButtonUpdate() {
  unsigned long now = millis();

  for (int i = 0; i < 5; i++) {
    ButtonState &btn = btns[i];
    bool reading = digitalRead(btn.pin) == LOW;

    // Нажатие
    if (!btn.isPressed && reading) {
      btn.isPressed = true;
      btn.longPressHandled = false;
      btn.pressStartTime = now;
    }

    // Удержание
    if (btn.isPressed && !btn.longPressHandled && now - btn.pressStartTime >= LONG_PRESS_TIME) {
      btn.longPressHandled = true;
      onLongPress(btnNames[i]);
    }

    // Отпускание
    if (btn.isPressed && !reading) {
      btn.isPressed = false;

      if (!btn.longPressHandled) {
        if (now - btn.lastReleaseTime <= DOUBLE_CLICK_TIME) {
          onDoubleClick(btnNames[i]);
          btn.waitingDouble = false;
        } else {
          btn.lastReleaseTime = now;
          btn.waitingDouble = true;
        }
      }
    }

    // Обработка одиночного клика 
    if (btn.waitingDouble && (now - btn.lastReleaseTime > DOUBLE_CLICK_TIME)) {
      onSingleClick(btnNames[i]);
      btn.waitingDouble = false;
    }
  }
}