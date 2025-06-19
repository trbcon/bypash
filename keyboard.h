// #include <TFT_eSPI.h>
#include <SPI.h>

#define BTN_UP     12
#define BTN_DOWN   13
#define BTN_LEFT   14
#define BTN_RIGHT  27
#define BTN_OK     26

TFT_eSPI tft = TFT_eSPI();

// Раскладки
const char* layout_en[] = {
  "1234567890-=",
  "qwertyuiop[]",
  "asdfghjkl;'\\",
  "zxcvbnm,./",
  "[SHIFT][SPACE][BKSP][ENT]"
};

const char* layout_ru[] = {
  "1234567890-=",
  "йцукенгшщзхъ",
  "фывапролджэ\\",
  "ячсмитьбю.",
  "[SHIFT][SPACE][BKSP][ENT]"
};

const int key_rows = 5;
const int max_cols[] = {12, 12, 12, 11, 4};

int selected_row = 0;
int selected_col = 0;
bool shift = false;
bool isRussian = false;

String input_text = "";
int cursor_pos = 0;
String current_char = "";

unsigned long last_action = 0;
unsigned long ok_hold_start = 0;
bool ok_held = false;

bool button(int pin) {
  return digitalRead(pin) == LOW;
}

char get_shifted_char(char c) {
  switch (c) {
    case '1': return '!';
    case '2': return '@';
    case '3': return '#';
    case '4': return '$';
    case '5': return '%';
    case '6': return '^';
    case '7': return '&';
    case '8': return '*';
    case '9': return '(';
    case '0': return ')';
    case '-': return '_';
    case '=': return '+';
    case '[': return '{';
    case ']': return '}';
    case ';': return ':';
    case '\'': return '"';
    case ',': return '<';
    case '.': return '>';
    case '/': return '?';
    case '\\': return '|';
    default: return isAlpha(c) ? toupper(c) : c;
  }
}

char getCharAt(int row, int col) {
  const char* layout = isRussian ? layout_ru[row] : layout_en[row];
  if (row < key_rows - 1) {
    char ch = layout[col];
    return shift ? get_shifted_char(ch) : ch;
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
  tft.print(isRussian ? "RU" : "EN");
  tft.setCursor(100, 0);
  tft.setTextColor(TFT_YELLOW);
  tft.print("Shift: ");
  tft.print(shift ? "ON" : "OFF");

  for (int row = 0; row < key_rows; row++) {
    int y = 15 + row * 20;
    int col_index = 0;
    int x = 0;
    const char* line = isRussian ? layout_ru[row] : layout_en[row];

    for (int i = 0; line[i] != '\0'; i++) {
      if (line[i] == ' ') continue;

      char ch = line[i];
      String s;

      if (row == key_rows - 1) {
        if (col_index == 0) s = "SHIFT";
        else if (col_index == 1) s = "SPACE";
        else if (col_index == 2) s = "BKSP";
        else if (col_index == 3) s = "ENT";
      } else {
        s = shift ? String(get_shifted_char(ch)) : String(ch);
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

  // Вывод текста, введённого пользователем
  tft.fillRect(0, 135, 160, 20, TFT_BLACK);
  tft.setCursor(0, 135);
  tft.setTextColor(TFT_WHITE);
  tft.print("Text: ");
  tft.print(input_text);

  // Отображение курсора (инверт символа под курсором)
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

void read_buttons() {
  if (millis() - last_action < 150) return;

  if (button(BTN_UP) && selected_row > 0) {
    selected_row--;
    if (selected_col >= max_cols[selected_row])
      selected_col = max_cols[selected_row] - 1;
    last_action = millis();
  } else if (button(BTN_DOWN) && selected_row < key_rows - 1) {
    selected_row++;
    if (selected_col >= max_cols[selected_row])
      selected_col = max_cols[selected_row] - 1;
    last_action = millis();
  } else if (button(BTN_LEFT)) {
    if (button(BTN_RIGHT)) {
      isRussian = !isRussian;
    } else if (cursor_pos > 0) {
      cursor_pos--;
    } else if (selected_col > 0) {
      selected_col--;
    }
    last_action = millis();
  } else if (button(BTN_RIGHT)) {
    if (cursor_pos < input_text.length()) {
      cursor_pos++;
    } else if (selected_col < max_cols[selected_row] - 1) {
      selected_col++;
    }
    last_action = millis();
  } else if (button(BTN_OK)) {
    if (!ok_held) {
      ok_hold_start = millis();
      ok_held = true;
    }

    if (millis() - ok_hold_start > 300) {
      perform_ok_action();
      ok_hold_start = millis();
    }
  } else {
    if (ok_held) {
      perform_ok_action();
      ok_held = false;
    }
  }
}

void perform_ok_action() {
  if (selected_row == key_rows - 1) {
    if (selected_col == 0) shift = !shift;
    else if (selected_col == 1) insert_char(' ');
    else if (selected_col == 2) delete_char();
    else if (selected_col == 3) {
      Serial.println("Entered: " + input_text);  // <- Здесь переменная input_text записывается
      input_text = "";
      cursor_pos = 0;
    }
  } else {
    char ch = getCharAt(selected_row, selected_col);
    insert_char(ch);
  }
  last_action = millis();
}

void setup() {
  Serial.begin(115200);
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);
  pinMode(BTN_OK, INPUT_PULLUP);

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  draw_keyboard();
}

void loop() {
  read_buttons();
  draw_keyboard();
}
