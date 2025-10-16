#include <vector>
#include <map>
// #include <SPI.h>


#include "../menu/menu.h"

#include "../notifications/notifications.h"

#include "../buttons/buttons.h"

#include "../display/display.h"
#include "../display/keyboard.h"
#include "../display/watch.h"

#include "../applications/stopwatch.h"

#include "../sensors/pins.h"
#include "../sensors/watch.h"

#include "../timers/timers.h"

#include "../wireless/wifi/wifi.h"
#include "../wireless/wifi/wifi_deauth_sender.h"
#include "../wireless/wifi/wifi_mode_selector.h"
#include "../wireless/wifi/wifi_sniffer.h"
#include "../wireless/wifi/wifi_sta_selector.h"

#include "../wireless/bt/bluetooth.h"

#include "../wired/usb.h"

#include "../config/settings.h"


//PROGS
bool isMenu = true;
bool isStopwatchRunning = false;
bool isPinsMenu = false;
bool isWatchOK = false;

//SERVICES
bool isNotifications = false;

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


void handleMenuInput() {
    ButtonEvent btn = readButton();
    int itemsCount = currentMenu->items.size();

    if (btn == ButtonEvent::UP && selectedItem > 0) {
        selectedItem--;
        if (selectedItem < viewOffset) viewOffset = selectedItem;
    }
    if (btn == ButtonEvent::DOWN && selectedItem < itemsCount - 1) {
        selectedItem++;
        if (selectedItem >= viewOffset + maxVisibleItems)
            viewOffset = selectedItem - maxVisibleItems + 1;
    }
    if (btn == ButtonEvent::OK) {
        handleOk();
    }
    if (btn == ButtonEvent::LEFT) {
        handleBack();
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

// -------------------------------
void executeAction(String label) {
  if (String(currentMenu->name) == "Wi-Fi spammer" && label == "Start attack") {
    // StartWiFiAttack();
  } else if (String(currentMenu->name) == "Wi-Fi" && label == "Wi-Fi scanner") {
    // WiFiScanner();
  } else if (String(currentMenu->name) == "Watch" && label == "Stopwatch") {
    // startMillis = millis();
    // isStopwatchRunning = true;
    // isMenu = false;
    // isMenu = false;
    stopwatch_enter();
    // drawStopwatchMenu();
  } else if (String(currentMenu->name) == "Watch" && label == "Timer") {
    TimerActive = true;
  } else if (String(currentMenu->name) == "Pins") {
    isPinsMenu = true;
  } else if (String(currentMenu->name) == "Music Player") {
    //
  } else {
    Serial.print("Выбран пункт: ");
    Serial.println(label);
  }
}
// -------------------------------


// void selectMenu(bool &isSomething) {
//   isMenu = false;
//   // isNotifications = false;
//   isStopwatchRunning = false;
//   isPinsMenu = false;
//   isWatchOK = false;
//   isSomething = true;
// }


void updateAll() {
  TimerUpdate();

  if (sw_running) {
    stopwatch_update();
  }

  //notifications
  if (isNotifications) {
    showNotificationsMenu();
  }

  // if (isPinsMenu) {
    
  // }
}



void setup() {
  Serial.begin(115200);
  displayInit();
  WatchInit();

  startScreen();

  setupMenus();
  ButtonSetup();
  setPins();

  drawMenu();

  // printPins();


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
  // ButtonUpdate();
  drawTopBar();
  
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

      if (isMenu) drawMenu();      
    } else if (sw_active) { // Секундомер
      if (command == "start") {
        if (!sw_running) {
          sw_startTime = millis() - sw_elapsed;
          sw_running = true;
        }
      } else if (command == "stop") {
        if (sw_running) {
          sw_elapsed = millis() - sw_startTime;
          sw_running = false;
        }
      } else if (command == "reset") {
        sw_running = false;
        sw_elapsed = 0;
      }
      if (command == "up"){
        stopwatch_menuUp();
      } else if (command == "down") {
        stopwatch_menuDown();
      } else if (command == "ok") {
        stopwatch_menuOk();
      }

      if (sw_active) drawStopwatchMenu(); // sw_active это меню, а sw_running это сам секундомер
    } else if (TimerMenuActive) {
      if (command == "up") {
        TimerMenuUp();
      } else if (command == "down") {
        TimerMenuDown();
      } else if (command == "ok") {
        TimerMenuOk();
      } else if (command == "back") {
        handleBack();
      } else if (command == "right") {
        TimerMenuRight();
      } else if (command == "left") {
        TimerMenuLeft();
      }
    }
  }

  
  if (isNotifications) {
        showNotificationsMenu();
        handleNotificationsMenuInput();
    } else if (isMenu) {
        drawMenu();
        handleMenuInput();
    }

}



