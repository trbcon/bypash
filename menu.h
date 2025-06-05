struct Menu {
  const char* name;
  std::vector<const char*> items;
  std::map<String, Menu*> submenus;
};

Menu mainMenu;
Menu wifiMenu;
Menu wifiSpammerMenu;
Menu bluetoothMenu;

Menu* currentMenu = &mainMenu;
int selectedItem = 0;
int viewOffset = 0;
const int maxVisibleItems = 4;

std::vector<Menu*> menuStack;

void setupMenus() {
  mainMenu.name = "Main";
  mainMenu.items = {"Wi-Fi", "Bluetooth", "Pins", "2.4", "1", "2", "3", "4", "5", "asd", "adadasda"};
  mainMenu.submenus["Wi-Fi"] = &wifiMenu;
  mainMenu.submenus["Bluetooth"] = &bluetoothMenu;

  wifiMenu.name = "Wi-Fi";
  wifiMenu.items = {"Wi-Fi spammer", "Wi-Fi scanner", "back"};
  wifiMenu.submenus["Wi-Fi spammer"] = &wifiSpammerMenu;

  wifiSpammerMenu.name = "Wi-Fi spammer";
  wifiSpammerMenu.items = {"Start attack", "Stop", "back"};

  bluetoothMenu.name = "Bluetooth";
  bluetoothMenu.items = {"Bluetooth connect", "Bluetooth scan", "back"};
}
