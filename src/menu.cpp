#include "../menu/menu.h"

Menu mainMenu;
Menu wifiMenu;
Menu wifiSpammerMenu;
Menu bluetoothMenu;
Menu settingsMenu;
Menu DisplaySettingsMenu;
Menu RotationSettingsMenu;
Menu WatchMenu;
Menu ThemesMenu;
Menu TADMenu;


Menu* currentMenu = &mainMenu;
int selectedItem = 0;
int viewOffset = 0;
const byte maxVisibleItems = 15;
std::vector<Menu*> menuStack;

void setupMenus() {
  mainMenu.name = "Main";
  mainMenu.items = {"Wi-Fi", "Bluetooth", "Pins", "2.4", "Watch", "2", "3", "4", "5", "asd", "Settings"};
  mainMenu.submenus["Wi-Fi"] = &wifiMenu;
  mainMenu.submenus["Bluetooth"] = &bluetoothMenu;
  mainMenu.submenus["Wi-Fi spammer"] = &wifiSpammerMenu;
  mainMenu.submenus["Watch"] = &WatchMenu;
  mainMenu.submenus["Settings"] = &settingsMenu;

  wifiMenu.name = "Wi-Fi";
  wifiMenu.items = {"Wi-Fi spammer", "Wi-Fi scanner", "W", "back"};
  wifiMenu.submenus["Wi-Fi spammer"] = &wifiSpammerMenu;

  wifiSpammerMenu.name = "Wi-Fi spammer";
  wifiSpammerMenu.items = {"Start attack", "Stop", "back"};

  bluetoothMenu.name = "Bluetooth";
  bluetoothMenu.items = {"BLE spam", "Bluetooth scan", "back"};

  WatchMenu.name = "Watch";
  WatchMenu.items = {"Stopwatch", "Timer", "back"};

  settingsMenu.name = "Settings";
  settingsMenu.items = {"Display", "Themes", "Time and Data", "back"};
  settingsMenu.submenus["Display"] = &DisplaySettingsMenu;
  settingsMenu.submenus["Themes"] = &ThemesMenu;
  settingsMenu.submenus["Time and Data"] = &TADMenu;

  ThemesMenu.name = "Themes";
  ThemesMenu.items = {"Dark(default)", "Light", "back"};

  DisplaySettingsMenu.name = "Display";
  DisplaySettingsMenu.items = {"Brigtness", "Rotation", "back"};
  DisplaySettingsMenu.submenus["Rotation"] = &RotationSettingsMenu;

  RotationSettingsMenu.name = "Rotation";
  RotationSettingsMenu.items = {"Vertical", "Horizontal", "back"};
}
