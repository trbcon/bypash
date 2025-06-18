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


void startScreen() {
  //
}



bool isMenu = true;
bool isStopwatchRunning = false;
bool 



void setup() {
  Serial.begin(9600);
  tft.init();
  tft.setRotation(1);
  tft.setTextSize(1);  // Text size 1
  tft.setTextColor(TFT_WHITE);
  tft.fillScreen(TFT_BLACK);

  startScreen();

  setupMenus();
  drawMenu();


  wsl_bypass_init();

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // to sniff
  // esp_wifi_set_promiscuous(true);

  uint8_t mac[6];
  // esp_wifi_get_mac(WIFI_IF_STA, mac); // MAC устройства

  // wifi_send_broadcast_deauth(mac, 0x07); // reason: Class 3 frame from non-auth STA


}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    if isMenu {
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

  if isStopwatchRunning {
    StopwatchDraw();
  }

  if Pins{
    pass
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


void StopwatchDraw() {
  tft.fillRect(0, 40, 160, 30, TFT_BLACK);
  tft.setCursor(10, 40);
  sec, ms = StartStopwatch();
  tft.printf("%02lu.%03lu сек", sec, ms);
  // добавить проверку на нажатие кнопок(ок для запуска, влево для выхода)
}



// -------------------------------
void executeAction(String label) {
  if (String(currentMenu->name) == "Wi-Fi spammer" && label == "Start attack") {
    StartWiFiAttack();
  } else if (String(currentMenu->name) == "Wi-Fi" && label == "Wi-Fi scanner"){
    WiFiScanner();
  } else if (String(currentMenu->name) == "Watch" && label == "Stopwatch"){
    startMillis = millis();
    StopwatchRunning = true;
    isMenu = false;
  } else if String(currentMenu->name) == "Pins"{
    
  }
  else {
    Serial.print("Выбран пункт: ");
    Serial.println(label);
  }
}
// -------------------------------


