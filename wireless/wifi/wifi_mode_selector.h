#pragma once

enum class AttackMode {
  SINGLE_AP_SINGLE_STA,
  MULTI_AP_MULTI_STA,
  ALL_APS_ALL_STAS
};

void setAttackMode(AttackMode mode);
AttackMode getAttackMode();