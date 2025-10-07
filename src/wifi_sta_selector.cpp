#include "../wireless/wifi/wifi_sta_selector.h"

static std::vector<WiFiDevice> selectedSTAs;

bool isSTASelected(const WiFiDevice& sta) {
  for (auto& s : selectedSTAs)
    if (memcmp(s.mac, sta.mac, 6) == 0) return true;
  return false;
}

void toggleSTASelection(const WiFiDevice& sta) {
  for (auto it = selectedSTAs.begin(); it != selectedSTAs.end(); ++it) {
    if (memcmp(it->mac, sta.mac, 6) == 0) {
      selectedSTAs.erase(it);
      return;
    }
  }
  selectedSTAs.push_back(sta);
}

const std::vector<WiFiDevice>& getSelectedSTAs() {
  return selectedSTAs;
}

void clearSTASelection() {
  selectedSTAs.clear();
}
