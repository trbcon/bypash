// === include/buttons.h ===
#pragma once

#define BTN_UP     12
#define BTN_DOWN   13
#define BTN_LEFT   14
#define BTN_RIGHT  27
#define BTN_OK     26

#define LONG_PRESS_TIME 500
#define DOUBLE_CLICK_TIME 300

struct ButtonState {
  int pin;
  bool isPressed = false;
  bool longPressHandled = false;
  bool waitingDouble = false;
  unsigned long pressStartTime = 0;
  unsigned long lastReleaseTime = 0;
};

void ButtonSetup();
void ButtonUpdate();


// === src/keyboard.cpp ===
#include "../display/keyboard.h"
#include "../display/display.h"

// TFT_eSPI tft = TFT_eSPI();

bool isSpecialMenu = false;

const char* layout_en[] = {
  "1234567890-=",
  "qwertyuiop[]",
  "asdfghjkl;'\\",
  "zxcvbnm,./",
  "[SHIFT][SPACE][BKSP][ENT][LANG][SYM]"
};

const char* layout_ru[] = {
  "1234567890-=",
  "йцукенгшщзхъ",
  "фывапролджэ\\",
  "ячсмитьбю.",
  "[SHIFT][SPACE][BKSP][ENT][LANG][SYM]"
};

const char* layout_special[] = {
  "!@#$%^&*()_+",
  "{}[]<>~`|\\",
  ":;\"',.?/=",
  "←→↑↓✓✔✖★",
  "[ABC]"
};

const int key_rows = 5;
const int max_cols[] = {12, 12, 12, 11, 6};

int selected_row = 0;
int selected_col = 0;
bool shift = false;
bool isRussian = false;
bool keyboardActive = false;

String input_text = "";
int cursor_pos = 0;
String current_char = "";

char get_shifted_char_ru(char c) {
  if (c >= 'а' && c <= 'я') return c - ('а' - 'А');
  if (c == 'ё') return 'Ё';
  return c;
}

char getCharAt(int row, int col) {
  if (isSpecialMenu) {
    const char* layout = layout_special[row];
    return layout[col];
  }

  const char* layout = isRussian ? layout_ru[row] : layout_en[row];
  if (row < key_rows - 1) {
    char ch = layout[col];
    if (shift) {
      if (isRussian) return get_shifted_char_ru(ch);
      return isAlpha(ch) ? toupper(ch) : ch;
    }
    return ch;
  }
  return 0;
}

void insert_char(char ch) {
  input_text = input_text.substring(0, cursor_pos) + ch + input_text.substring(cursor_pos);
  cursor_pos++;
}

void delete_char() {
  if (cursor_pos > 0) {
    input_text.remove(cursor_pos - 1, 1);
    cursor_pos--;
  }
}

void draw_keyboard() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
  tft.setCursor(0, 0);
  tft.setTextColor(TFT_CYAN);
  tft.print("Layout: ");
  tft.print(isSpecialMenu ? "SYM" : (isRussian ? "RU" : "EN"));
  tft.setCursor(100, 0);
  tft.setTextColor(TFT_YELLOW);
  tft.print("Shift: ");
  tft.print(shift ? "ON" : "OFF");

  for (int row = 0; row < key_rows; row++) {
    int y = 15 + row * 20;
    int col_index = 0;
    int x = 0;
    const char* line = isSpecialMenu ? layout_special[row] : (isRussian ? layout_ru[row] : layout_en[row]);

    for (int i = 0; line[i] != '\0'; i++) {
      if (line[i] == ' ') continue;
      char ch = line[i];
      String s;

      if (row == key_rows - 1) {
        if (isSpecialMenu) {
          if (col_index == 0) s = "ABC";
        } else {
          if (col_index == 0) s = "↑";
          else if (col_index == 1) s = "SPACE";
          else if (col_index == 2) s = "←";
          else if (col_index == 3) s = "⏎";
          else if (col_index == 4) s = "L";
          else if (col_index == 5) s = "SYM";
        }
      } else {
        if (shift && !isSpecialMenu) {
          if (isRussian) ch = get_shifted_char_ru(ch);
          else ch = isAlpha(ch) ? toupper(ch) : ch;
        }
        s = String(ch);
      }

      bool selected = (row == selected_row && col_index == selected_col);
      if (selected) {
        tft.fillRect(x, y, 25, 18, TFT_WHITE);
        tft.setTextColor(TFT_BLACK);
        current_char = s;
      } else {
        tft.drawRect(x, y, 25, 18, TFT_WHITE);
        tft.setTextColor(TFT_GREEN);
      }

      tft.setCursor(x + 3, y + 4);
      tft.print(s);
      x += 26;
      col_index++;
    }
  }

  tft.fillRect(0, 135, 160, 20, TFT_BLACK);
  tft.setCursor(0, 135);
  tft.setTextColor(TFT_WHITE);
  tft.print("Text: ");
  tft.print(input_text);

  tft.setCursor(0, 145);
  for (int i = 0; i < input_text.length(); i++) {
    if (i == cursor_pos) {
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.print(input_text[i]);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
    } else {
      tft.print(input_text[i]);
    }
  }
  if (cursor_pos == input_text.length()) {
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.print(" ");
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
  }
}

void perform_ok_action() {
  if (selected_row == key_rows - 1) {
    if (isSpecialMenu) {
      if (selected_col == 0) isSpecialMenu = false;
    } else {
      if (selected_col == 0) shift = !shift;
      else if (selected_col == 1) insert_char(' ');
      else if (selected_col == 2) delete_char();
      else if (selected_col == 3) {
        Serial.println("Entered: " + input_text);
        keyboardActive = false;
      }
      else if (selected_col == 4) isRussian = !isRussian;
      else if (selected_col == 5) isSpecialMenu = true;
    }
  } else {
    char ch = getCharAt(selected_row, selected_col);
    insert_char(ch);
  }
}
