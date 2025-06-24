#include <vector>
#include <string>

struct Notification {
    std::string text;
    unsigned long startTime;
};

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
    int y = 10;
    unsigned long now = millis();

    std::vector<Notification> stillActive;

    for (auto& notif : notifications) {
        if (now - notif.startTime < 4000) {  // 7 секунд живёт
            tft.setCursor(110, y * 8);
            tft.print(notif.text.c_str());
            stillActive.push_back(notif);
            y++;
        }
        // Иначе мы не добавляем в новый список = удаляем
    }

    notifications = stillActive; // Обновляем список активных
}
