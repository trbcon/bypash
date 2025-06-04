#include <TFT_eSPI.h>
#include <vector>
#include <map>

TFT_eSPI tft = TFT_eSPI();

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

void setup() {
  Serial.begin(9600);
  tft.init();
  tft.setRotation(1);
  tft.setTextSize(1);  // Text size 1
  tft.setTextColor(TFT_WHITE);
  tft.fillScreen(TFT_BLACK);

  setupMenus();
  drawMenu();
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "up") {
      selectedItem--;
      if (selectedItem < 0) selectedItem = currentMenu->items.size() - 1;
    } else if (command == "down") {
      selectedItem++;
      if (selectedItem >= currentMenu->items.size()) selectedItem = 0;
    } else if (command == "ok") {
      handleOk();
    } else if (command == "back") {
      handleBack();
    }

    if (selectedItem < viewOffset) {
      viewOffset = selectedItem;
    } else if (selectedItem >= viewOffset + maxVisibleItems) {
      viewOffset = selectedItem - maxVisibleItems + 1;
    }

    drawMenu();
  }
}

void handleOk() {
  String item = currentMenu->items[selectedItem];

  if (item == "back") {
    handleBack();
    return;
  }

  if (currentMenu->submenus.count(item)) {
    menuStack.push_back(currentMenu);
    currentMenu = currentMenu->submenus[item];
    selectedItem = 0;
    viewOffset = 0;
  } else {
    executeAction(item);
  }
}

void handleBack() {
  if (!menuStack.empty()) {
    currentMenu = menuStack.back();
    menuStack.pop_back();
    selectedItem = 0;
    viewOffset = 0;
  }
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


void executeAction(String label) {
  if (String(currentMenu->name) == "Wi-Fi spammer" && label == "Start attack") {
    Serial.println("Hello World");
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(10, 10);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println("Hello World");
    delay(1000);
    drawMenu(); // Возврат к меню
  } else {
    Serial.print("Выбран пункт: ");
    Serial.println(label);
  }
}


