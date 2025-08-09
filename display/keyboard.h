#pragma once
#include <TFT_eSPI.h>

extern bool keyboardActive;
extern String input_text;

void draw_keyboard();
void perform_ok_action();

extern int selected_row;
extern int selected_col;
extern const int key_rows;
extern const int max_cols[];