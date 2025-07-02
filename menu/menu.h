#pragma once
#include <vector>
#include <map>
#include <Arduino.h> 


struct Menu {
  const char* name;
  std::vector<const char*> items;
  std::map<String, Menu*> submenus;
};

extern Menu mainMenu;
extern Menu wifiMenu;
extern Menu wifiSpammerMenu;
extern Menu bluetoothMenu;
extern Menu settingsMenu;
extern Menu DisplaySettingsMenu;
extern Menu RotationSettingsMenu;
extern Menu WatchMenu;
extern Menu ThemesMenu;
extern Menu TADMenu;


extern Menu* currentMenu;
extern int selectedItem;
extern int viewOffset;
extern const byte maxVisibleItems;
extern std::vector<Menu*> menuStack;

// _____
// Menu settingsMenu;
// Menu settingsMenu;
// Menu settingsMenu;
// Menu settingsMenu;
// _____

void setupMenus();