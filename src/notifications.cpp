#include "../notifications/notifications.h"
#include <TFT_eSPI.h>

extern TFT_eSPI tft;

std::vector<Notification> notifications;

void setNotification(const std::string& strNotification) {
    Notification n;
    n.text = strNotification;
    n.startTime = millis();
    notifications.push_back(n);
}

void clearNotifications() {
    notifications.clear();
}

void printNotifications() {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    int y = 0;
    unsigned long now = millis();

    std::vector<Notification> stillActive;

    for (auto& notif : notifications) {
        if (now - notif.startTime < 4000) {
            tft.setCursor(80, 9 + y * 8);
            tft.print(notif.text.c_str());
            stillActive.push_back(notif);
            y++;
        }
    }

    notifications = stillActive;
}
