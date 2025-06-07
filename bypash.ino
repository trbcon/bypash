#include <TFT_eSPI.h>
#include <vector>
#include <map>


TFT_eSPI tft = TFT_eSPI();



//files
#include <bluetooth.h>
#include <buttons.h>
#include <display.h>
#include <pins.h>
#include <settings.h>
#include <usb.h>
#include <wi-fi.h>
//







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





void executeAction(String label) {
  if (String(currentMenu->name) == "Wi-Fi spammer" && label == "Start attack") {
    StartWiFiAttack();
  } else if (String(currentMenu->name) == "Wi-Fi" && label == "Wi-Fi scanner"){
    WiFiScanner();
  } else {
    Serial.print("Выбран пункт: ");
    Serial.println(label);
  }
}



// 16.10
// 47.00
// 56.20
// 58.00