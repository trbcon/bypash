// #include "../buttons/buttons.h"
// #include "../display/keyboard.h"
// #include <Arduino.h>
// #include <cstring>

// static ButtonState btns[] = {
//   { BTN_UP },
//   { BTN_DOWN },
//   { BTN_LEFT },
//   { BTN_RIGHT },
//   { BTN_OK }
// };

// static const char* btnNames[] = {
//   "UP", "DOWN", "LEFT", "RIGHT", "OK"
// };

// void ButtonSetup() {
//   for (int i = 0; i < 5; i++) {
//     pinMode(btns[i].pin, INPUT_PULLUP);
//   }
// }

// void onSingleClick(const char* name) {
//   if (keyboardActive) {
//     if (strcmp(name, "UP") == 0 && selected_row > 0) selected_row--;
//     else if (strcmp(name, "DOWN") == 0 && selected_row < key_rows - 1) selected_row++;
//     else if (strcmp(name, "LEFT") == 0 && selected_col > 0) selected_col--;
//     else if (strcmp(name, "RIGHT") == 0 && selected_col < max_cols[selected_row] - 1) selected_col++;
//     else if (strcmp(name, "OK") == 0) perform_ok_action();

//     draw_keyboard();
//     return;  // меню не трогаем
//   }


//   if (strcmp(name, "UP") == 0) {
//     if (isMenu) {
//       selectedItem--;
//       if (selectedItem < 0) selectedItem = currentMenu->items.size() - 1;
//     }
//   }
//   else if (strcmp(name, "DOWN") == 0) {
//     if (isMenu){
//       selectedItem++;
//       if (selectedItem >= currentMenu->items.size()) selectedItem = 0;
//     } 
//   }
//   else if (strcmp(name, "LEFT") == 0) {
//     if (isMenu) {
//       handleBack();
//     }
//   }
//   else if (strcmp(name, "RIGHT") == 0) {
//     if (isMenu) handleOk();
//   }
//   else if (strcmp(name, "OK") == 0) {
//     if (isMenu) handleOk();
//   }
// }

// void onDoubleClick(const char* name) {
//   if (strcmp(name, "UP") == 0) {
//   }
//   else if (strcmp(name, "DOWN") == 0) {
//   }
//   else if (strcmp(name, "LEFT") == 0) {
//   }
//   else if (strcmp(name, "RIGHT") == 0) {
//   }
//   else if (strcmp(name, "OK") == 0) {
//   }
//   // добавить остальные двойные клики по желанию
// }

// void onLongPress(const char* name) {
//   if (strcmp(name, "UP") == 0) {
//   }
//   else if (strcmp(name, "DOWN") == 0) {
//     if (isNotifications) {
//       isNotifications = false;
//     } else {
//       isNotifications = true;
//       // selectMenu(isNotifications);
//     }
//   }
//   else if (strcmp(name, "LEFT") == 0) {
//   }
//   else if (strcmp(name, "RIGHT") == 0) {
//   }
//   else if (strcmp(name, "OK") == 0) {
//   }
// }

// void ButtonUpdate() {
//   unsigned long now = millis();
//   for (int i = 0; i < 5; i++) {
//     ButtonState& btn = btns[i];
//     bool pressed = (digitalRead(btn.pin) == LOW);

//     // начало нажатия
//     if (!btn.isPressed && pressed) {
//       btn.isPressed        = true;
//       btn.longPressHandled = false;
//       btn.pressStartTime   = now;
//     }

//     // долгий клик
//     if (btn.isPressed
//         && !btn.longPressHandled
//         && now - btn.pressStartTime >= LONG_PRESS_TIME) {
//       btn.longPressHandled = true;
//       onLongPress(btnNames[i]);
//     }

//     // отпускание
//     if (btn.isPressed && !pressed) {
//       btn.isPressed = false;
//       if (!btn.longPressHandled) {
//         if (now - btn.lastReleaseTime <= DOUBLE_CLICK_TIME) {
//           onDoubleClick(btnNames[i]);
//           btn.waitingDouble = false;
//         } else {
//           btn.lastReleaseTime = now;
//           btn.waitingDouble  = true;
//         }
//       }
//     }

//     // одиночный клик
//     if (btn.waitingDouble
//         && now - btn.lastReleaseTime > DOUBLE_CLICK_TIME) {
//       onSingleClick(btnNames[i]);
//       btn.waitingDouble = false;
//     }
//   }
// }

#include "../buttons/buttons.h"

struct ButtonPin {
    uint8_t pin;
    ButtonEvent event;
};

static const ButtonPin buttonPins[] = {
    { BTN_UP,    ButtonEvent::UP },
    { BTN_DOWN,  ButtonEvent::DOWN },
    { BTN_LEFT,  ButtonEvent::LEFT },
    { BTN_RIGHT, ButtonEvent::RIGHT },
    { BTN_OK,    ButtonEvent::OK }
};

void ButtonSetup() {
    for (const auto& btn : buttonPins) {
        pinMode(btn.pin, INPUT_PULLUP);
    }
}

ButtonEvent readButton() {
    for (const auto& btn : buttonPins) {
        if (digitalRead(btn.pin) == LOW) {
            return btn.event;
        }
    }
    return ButtonEvent::NONE;
}