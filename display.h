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
const int maxVisibleItems = 8;

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

void drawMenu() {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.println(currentMenu->name);

  for (int i = 0; i < maxVisibleItems; i++) {
    int menuIndex = viewOffset + i;
    if (menuIndex >= currentMenu->items.size()) break;

    int y = (i + 1) * 10;

    if (menuIndex == selectedItem) {
      tft.setTextColor(TFT_YELLOW, TFT_BLACK);
      tft.setCursor(0, y);
      tft.print(">");
    } else {
      tft.setCursor(0, y);
      tft.print(" ");
    }

    tft.setCursor(10, y);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.print(currentMenu->items[menuIndex]);
  }
}