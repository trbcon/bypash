#include "../notifications/notifications.h"
#include <TFT_eSPI.h>

extern TFT_eSPI tft;

std::vector<Notification> notifications;

void setNotification(const std::string& strNotification) {
    Notification n;
    n.text = strNotification;
    notifications.push_back(n);
}

void clearNotifications() {
    notifications.clear();
}

// void printNotifications() {
//     tft.setTextColor(TFT_WHITE, TFT_BLACK);
//     int y = 0;
//     unsigned long now = millis();

//     std::vector<Notification> stillActive;

//     for (auto& notif : notifications) {
//         if (now - notif.startTime < 4000) {
//             tft.setCursor(80, 9 + y * 8);
//             tft.print(notif.text.c_str());
//             stillActive.push_back(notif);
//             y++;
//         }
//     }

//     notifications = stillActive;
// }


void printMiniNotification() {
    Serial.print(notifications[notifications.size() - 1].text.c_str());

}

void notificationsMenu() {
    if (notifications.size() < 15) {
        for(int i = 0; i < notifications.size(); i++){
            Serial.print(notifications[i].text.c_str());
        }
    }
}

void deleteMiniNotification() {
    tft.fillRect(80, 9, 80, 8, TFT_BLACK);
    
}