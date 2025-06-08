struct Menu {
  const char* name;
  std::vector<const char*> items;
  std::map<String, Menu*> submenus;
};

Menu mainMenu;
Menu wifiMenu;
Menu wifiSpammerMenu;
Menu bluetoothMenu;
Menu settingsMenu;
Menu DisplaySettingsMenu;
Menu RotationSettingsMenu;

// _____
// Menu settingsMenu;
// Menu settingsMenu;
// Menu settingsMenu;
// Menu settingsMenu;
// Menu settingsMenu;
// _____

Menu* currentMenu = &mainMenu;
int selectedItem = 0;
int viewOffset = 0;
const byte maxVisibleItems = 15;

std::vector<Menu*> menuStack;

void setupMenus() {
  mainMenu.name = "Main";
  mainMenu.items = {"Wi-Fi", "Bluetooth", "Pins", "2.4", "1", "2", "3", "4", "5", "asd", "Settings"};
  mainMenu.submenus["Wi-Fi"] = &wifiMenu;
  mainMenu.submenus["Bluetooth"] = &bluetoothMenu;

  wifiMenu.name = "Wi-Fi";
  wifiMenu.items = {"Wi-Fi spammer", "Wi-Fi scanner", "W" "back"};
  wifiMenu.submenus["Wi-Fi spammer"] = &wifiSpammerMenu;

  wifiSpammerMenu.name = "Wi-Fi spammer";
  wifiSpammerMenu.items = {"Start attack", "Stop", "back"};

  bluetoothMenu.name = "Bluetooth";
  bluetoothMenu.items = {"Bluetooth connect", "Bluetooth scan", "back"};



  settingsMenu.name = "Settings"
  settingsMenu.items = {"Display", "Themes", "back"}
  settingsMenu.submenus["Display"] = &DisplaySettingsMenu;

  DisplaySettingsMenu.name = "Display";
  DisplaySettingsMenu.items = {"Brigtness", "Rotation", "back"};
  DisplaySettingsMenu.submenus["Rotation"] = &RotationSettingsMenu;

  RotationSettingsMenu.name = "Rotation";
  RotationSettingsMenu.items = {"Vertical", "Horizontal", "back"};
}
