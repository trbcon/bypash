#include "wifi_sniffer.h"
#include <esp_wifi.h>
#include <WiFi.h>

static std::vector<WiFiDevice> devices;

static void snifferCallback(void* buf, wifi_promiscuous_pkt_type_t type) {
  if (type != WIFI_PKT_MGMT) return;
  const wifi_promiscuous_pkt_t* pkt = (wifi_promiscuous_pkt_t*)buf;
  const uint8_t* payload = pkt->payload;

  uint8_t subtype = payload[0] & 0xF0;
  WiFiDevice dev;
  dev.rssi = pkt->rx_ctrl.rssi;
  dev.channel = pkt->rx_ctrl.channel;

  if (subtype == 0x80) {
    memcpy(dev.mac, payload + 10, 6);
    dev.is_ap = true;
  } else if (subtype == 0x40) {
    memcpy(dev.mac, payload + 10, 6);
    dev.is_ap = false;
  } else return;

  for (auto& d : devices)
    if (memcmp(d.mac, dev.mac, 6) == 0) return;

  devices.push_back(dev);
}

void startSniffer() {
  WiFi.mode(WIFI_MODE_NULL);
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_promiscuous_rx_cb(snifferCallback);
}

void stopSniffer() {
  esp_wifi_set_promiscuous(false);
}

const std::vector<WiFiDevice>& getDetectedDevices() {
  return devices;
}