#include <vector>
#include <map>
// #include <SPI.h>


#include "../menu/menu.h"
#include "../notifications/notifications.h"
#include "../buttons/buttons.h"
#include "../display/display.h"
#include "../sensors/pins.h"
#include "../sensors/watch.h"
#include "../wireless/wi-fi.h"
#include "../wireless/bluetooth.h"
#include "../wired/usb.h"
#include "../config/settings.h"

bool isMenu = true;
// bool isNotifications = false;
bool isStopwatchRunning = false;
bool isPinsMenu = false;
bool isWatchOK = false;

// // settings
// #include <settings.h>
// #include <notifications.h>
// #include <display.h>
// #include <buttons.h>
// //

// //files
// #include <bluetooth.h>
// #include <pins.h>
// #include <usb.h>
// #include <wi-fi.h>
// #include <watch.h>
// //


extern void WatchDraw();
extern void drawMenu();
extern void ButtonSetup();
extern void ButtonUpdate();
extern void setPins();
extern void WatchInit();
void executeAction(String label);
void selectMenu(bool &isSomething);




unsigned long startMillis;


void startScreen() {
  tft.fillScreen(TFT_BLACK);
  int LX1, LX2, LX3, LY1, LY2, LY3;
  LX1 = 79; LX2 = 43; LX3 = 116; LY1 = 10; LY2 = 118; LY3 = 43;
  tft.drawLine(LX1, LY1, LX1, LY2, TFT_WHITE);
  tft.drawLine(LX1 + 1, LY1, LX1 + 1, LY2, TFT_WHITE);
  tft.drawLine(LX2, LY3, LX3, LY3, TFT_WHITE);
  tft.drawLine(LX2, LY3+1, LX3, LY3+1, TFT_WHITE);
}

void StopwatchDraw() {
  tft.fillRect(0, 40, 160, 30, TFT_BLACK);
  tft.setCursor(10, 40);
  TimeResult time = StartStopwatch();
  tft.printf("%02lu.%03lu сек", time.sec, time.ms);
  // добавить проверку на нажатие кнопок(ок для запуска, влево для выхода)
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

// -------------------------------
void executeAction(String label) {
  if (String(currentMenu->name) == "Wi-Fi spammer" && label == "Start attack") {
    // StartWiFiAttack();
  } else if (String(currentMenu->name) == "Wi-Fi" && label == "Wi-Fi scanner"){
    // WiFiScanner();
  } else if (String(currentMenu->name) == "Watch" && label == "Stopwatch"){
    startMillis = millis();
    isStopwatchRunning = true;
    isMenu = false;
  } else if (String(currentMenu->name) == "Pins") {
    isPinsMenu = true;
  } else {
    Serial.print("Выбран пункт: ");
    Serial.println(label);
  }
}
// -------------------------------


void selectMenu(bool &isSomething) {
  isMenu = false;
  // isNotifications = false;
  isStopwatchRunning = false;
  isPinsMenu = false;
  isWatchOK = false;


  
  isSomething = true;
}


void setup() {
  Serial.begin(9600);
  displayInit();

  startScreen();

  setupMenus();
  drawMenu();
  ButtonSetup();

  setPins();
  // printPins();

  WatchInit();


  // wsl_bypass_init();

  // WiFi.mode(WIFI_STA);
  // WiFi.disconnect();

  // to sniff
  // esp_wifi_set_promiscuous(true);

  // uint8_t mac[6];
  // esp_wifi_get_mac(WIFI_IF_STA, mac); // MAC устройства

  // wifi_send_broadcast_deauth(mac, 0x07); // reason: Class 3 frame from non-auth STA


}

void loop() {
  ButtonUpdate();
  WatchDraw();
  
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    if (isMenu) {
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
    } else if (isStopwatchRunning){
      if (command == "ok") {
        isStopwatchRunning = false;
        isMenu = true;
      }
    }
  }

  if (isStopwatchRunning) {
    StopwatchDraw();
  }

  // if (isPinsMenu) {
    
  // }
}




