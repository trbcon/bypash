#pragma once
#include "wifi_sniffer.h"
#include <vector>

// Хранит список выбранных STA
void toggleSTASelection(const WiFiDevice& sta);
bool isSTASelected(const WiFiDevice& sta);
const std::vector<WiFiDevice>& getSelectedSTAs();
void clearSTASelection();
