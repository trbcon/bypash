#pragma once
#include <vector>

struct WiFiDevice {
  uint8_t mac[6];
  int8_t rssi;
  uint8_t channel;
  bool is_ap;
};

void startSniffer();
void stopSniffer();
const std::vector<WiFiDevice>& getDetectedDevices();