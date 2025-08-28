#include "../applications/stopwatch.h"
#include "../display/display.h"

bool sw_running = false;
bool sw_active = false;
unsigned long sw_startTime = 0;
unsigned long sw_elapsed = 0;

int sw_menuIndex = 0;
const char* sw_menuItems[] = {"Start", "Stop", "Reset", "Exit"};
const int sw_menuCount = sizeof(sw_menuItems) / sizeof(sw_menuItems[0]);

void stopwatch_begin() {}

void stopwatch_enter() {
  isMenu = false;
  sw_active = true;
  sw_menuIndex = 0;
  tft.fillScreen(TFT_BLACK);
  drawStopwatchMenu();
}

void stopwatch_exit() {
  isMenu = true;
  sw_active = false;
  sw_running = false;
  drawMenu();
}

bool stopwatch_isActive() {
  return sw_active;
}

void stopwatch_command(const String& cmd) {
  if (cmd == "start") {
    if (!sw_running) {
      sw_startTime = millis() - sw_elapsed;
      sw_running = true;
    }
  } else if (cmd == "stop") {
    if (sw_running) {
      sw_elapsed = millis() - sw_startTime;
      sw_running = false;
    }
  } else if (cmd == "reset") {
    sw_running = false;
    sw_elapsed = 0;
    stopwatch_update();
  }
  drawStopwatchMenu();
}

void stopwatch_update() {
  if (!sw_active) return;

  unsigned long t = sw_running ? millis() - sw_startTime : sw_elapsed;
  int h = t / 3600000;
  int m = (t / 60000) % 60;
  int s = (t / 1000) % 60;
  int ms = t % 1000;

  tft.setCursor(10, 10);
  tft.fillRect(10, 10, 160, 20, TFT_BLACK);
  tft.setTextColor(TFT_PINK);
  tft.setTextSize(2);
  tft.printf("%02d:%02d:%02d.%03d", h, m, s, ms);
}

void drawStopwatchMenu() {
  tft.fillRect(0, 40, 160, 80, TFT_BLACK);
  // tft.fillScreen(TFT_BLACK); 
  tft.setTextSize(1);
  for (int i = 0; i < sw_menuCount; i++) {
    tft.setCursor(10, 45 + i * 15);
    if (i == sw_menuIndex) {
      tft.setTextColor(TFT_PINK);
      tft.print("> ");
    } else {
      tft.setTextColor(TFT_WHITE);
      tft.print("  ");
    }
    tft.print(sw_menuItems[i]);
  }
}

void stopwatch_menuUp() {
  if (!sw_active) return;
  sw_menuIndex = (sw_menuIndex - 1 + sw_menuCount) % sw_menuCount;
  drawStopwatchMenu();
}

void stopwatch_menuDown() {
  if (!sw_active) return;
  sw_menuIndex = (sw_menuIndex + 1) % sw_menuCount;
  drawStopwatchMenu();
}

void stopwatch_menuOk() {
  if (!sw_active) return;
  const char* selected = sw_menuItems[sw_menuIndex];
  if (strcmp(selected, "Start") == 0) stopwatch_command("start");
  else if (strcmp(selected, "Stop") == 0) stopwatch_command("stop");
  else if (strcmp(selected, "Reset") == 0) stopwatch_command("reset");
  else if (strcmp(selected, "Exit") == 0) stopwatch_exit();
}