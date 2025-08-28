#pragma once
#include <Arduino.h>
// #include "../display/display.h"


extern bool sw_running;
extern bool sw_active;
extern unsigned long sw_startTime;
extern unsigned long sw_elapsed;

extern int sw_menuIndex;
extern const char* sw_menuItems[];
extern const int sw_menuCount;
extern bool isMenu;


void stopwatch_begin();
void stopwatch_enter();
void stopwatch_exit();
void stopwatch_update();
void stopwatch_command(const String& cmd);
bool stopwatch_isActive();

// Меню-навигация
void stopwatch_menuUp();
void stopwatch_menuDown();
void stopwatch_menuOk();

void drawStopwatchMenu();