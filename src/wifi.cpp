//   // Настройка кнопок
//   pinMode(32, INPUT_PULLUP); // UP
//   pinMode(33, INPUT_PULLUP); // DOWN
//   pinMode(25, INPUT_PULLUP); // OK


// ButtonEvent btn = readButton();
//   if (btn == ButtonEvent::UP && selectedDeviceIndex > 0) selectedDeviceIndex--;
//   if (btn == ButtonEvent::DOWN && selectedDeviceIndex < devices.size() - 1) selectedDeviceIndex++;
//   if (btn == ButtonEvent::OK) {
//     // В зависимости от режима — запускаем соответствующую логику
//     switch (mode) {
//       case AttackMode::SINGLE_AP_SINGLE_STA:
//         if (devices[selectedDeviceIndex].is_ap) {
//           // Ищем первого клиента и атакуем
//           for (const auto& sta : stas) {
//             sendDeauth(devices[selectedDeviceIndex], sta);
//             break;
//           }
//         }
//         break;

//       case AttackMode::MULTI_AP_MULTI_STA:
//         for (const auto& ap : aps) {
//           for (const auto& sta : stas) {
//             sendDeauth(ap, sta);
//           }
//         }
//         break;

//       case AttackMode::ALL_APS_ALL_STAS:
//         for (const auto& ap : aps) {
//           for (const auto& sta : stas) {
//             sendDeauth(ap, sta);
//           }
//         }
//         break;
//     }
//   }


// Переменные для выбора устройства
int selectedDeviceIndex = 0;

void strt() {
  // Запуск Wi-Fi sniffer в режиме promiscuous
//   startSniffer();

  // Отображаем меню выбора режима атаки
//   showAttackModeMenu();
}

// void loop() {
//   // Обработка ввода в меню
//   handleAttackModeInput();

//   // Получаем текущий режим атаки
//   AttackMode mode = getAttackMode();

//   // Получаем список обнаруженных устройств
//   const auto& devices = getDetectedDevices();

//   // Фильтруем AP и STA
//   std::vector<WiFiDevice> aps;
//   std::vector<WiFiDevice> stas;

//   for (const auto& d : devices) {
//     if (d.is_ap) aps.push_back(d);
//     else stas.push_back(d);
//   }

//   // Отображаем список устройств на дисплее
//   showDeviceList(devices, selectedDeviceIndex);
// }



#include "../wireless/wifi/wifi_sta_selector.h"
#include "../display/display.h"

void showDeviceList(const std::vector<WiFiDevice>& list, int selected) {
  tft.fillScreen(TFT_BLACK);
  for (int i = 0; i < list.size() && i < 10; ++i) {
    auto& d = list[i];
    char line[40];
    sprintf(line, "%02X:%02X:%02X:%02X:%02X:%02X %s%s",
      d.mac[0], d.mac[1], d.mac[2], d.mac[3], d.mac[4], d.mac[5],
      d.is_ap ? "AP" : "STA",
      (!d.is_ap && isSTASelected(d)) ? " [✔]" : "");

    tft.setCursor(0, i * 16);
    tft.setTextColor(i == selected ? TFT_YELLOW : TFT_WHITE);
    tft.println(line);
  }
}

// #include "display.h"
// #include <TFT_eSPI.h>
// #include "sta_selector.h"

// TFT_eSPI tft = TFT_eSPI();

// void initDisplay() {
//   tft.init();
//   tft.setRotation(1);
//   tft.fillScreen(TFT_BLACK);
//   tft.setTextColor(TFT_WHITE);
//   tft.setTextSize(1);
// }

void showTextLines(const std::vector<String>& lines) {
  tft.fillScreen(TFT_BLACK);
  for (int i = 0; i < lines.size(); ++i) {
    tft.setCursor(0, i * 16);
    tft.setTextColor(i == 0 ? TFT_YELLOW : TFT_WHITE);
    tft.println(lines[i]);
  }
}



// menu.cpp

// #include "menu.h"
// #include "display.h"
// #include "buttons.h"
// #include "mode_selector.h"

// static int selectedIndex = 0;
// static const char* modeNames[] = {
//   "1 AP → 1 STA",
//   "Multi AP → Multi STA",
//   "All APs → All STAs"
// };

// void showAttackModeMenu() {
//   std::vector<String> lines;
//   for (int i = 0; i < 3; ++i) {
//     lines.push_back(String(i == selectedIndex ? "> " : "  ") + modeNames[i]);
//   }
//   showTextLines(lines);
// }

// void handleAttackModeInput() {
//   ButtonEvent btn = readButton();
//   if (btn == ButtonEvent::UP && selectedIndex > 0) selectedIndex--;
//   if (btn == ButtonEvent::DOWN && selectedIndex < 2) selectedIndex++;
//   if (btn == ButtonEvent::OK) {
//     setAttackMode(static_cast<AttackMode>(selectedIndex));
//   }
// }
