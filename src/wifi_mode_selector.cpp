#include "../wireless/wifi/wifi_mode_selector.h"

static AttackMode currentMode = AttackMode::SINGLE_AP_SINGLE_STA;

void setAttackMode(AttackMode mode) {
  currentMode = mode;
}

AttackMode getAttackMode() {
  return currentMode;
}