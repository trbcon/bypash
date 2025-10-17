#include "../display/display.h"
#include "../buttons/buttons.h"
#include "../notifications/notifications.h"

static int notifSelected = 0;
static int notifScroll = 0;
const int maxLines = 5;

std::vector<Notification> notifications;

void addNotification(const String& text, NotificationType type) {
    notifications.push_back({text, type, millis(), true});
    if (notifications.size() > 50) notifications.erase(notifications.begin());
}

void clearAllNotifications() {
    notifications.clear();
    notifSelected = 0;
    notifScroll = 0;
}

void removeNotification(int index) {
    if (index >= 0 && index < notifications.size()) {
        notifications.erase(notifications.begin() + index);
        if (notifSelected >= notifications.size()) notifSelected = notifications.size() - 1;
        if (notifSelected < 0) notifSelected = 0;
        if (notifScroll > notifSelected) notifScroll = notifSelected;
        if (notifScroll < 0) notifScroll = 0;
    }
}

void showNotificationsMenu() {
    tft.fillScreen(TFT_BLACK);
    int total = notifications.size();
    if (notifSelected >= total && total > 0) notifSelected = total - 1;
    if (notifSelected < 0) notifSelected = 0;
    if (notifScroll > notifSelected) notifScroll = notifSelected;
    if (notifScroll < notifSelected - maxLines + 1) notifScroll = notifSelected - maxLines + 1;
    if (notifScroll < 0) notifScroll = 0;

    for (int i = 0; i < maxLines; ++i) {
        int idx = notifScroll + i;
        if (idx >= total) break;
        const auto& n = notifications[idx];
        uint16_t color = TFT_WHITE;
        if (n.type == NotificationType::WARNING) color = TFT_YELLOW;
        if (n.type == NotificationType::ERROR) color = TFT_RED;
        tft.setCursor(0, i * 16);
        tft.setTextColor(idx == notifSelected ? TFT_CYAN : color);
        tft.print(idx == notifSelected ? "> " : "  ");
        tft.println(n.text);
    }
    tft.setCursor(0, maxLines * 16 + 2);
    tft.setTextColor(TFT_DARKGREY);
    tft.println("[OK] удалить  [LEFT] все  [BACK] выход");
}



void handleNotificationsMenuInput() {
    // int total = notifications.size();

    // if (strcmp(btnName, "UP") == 0 && notifSelected > 0) notifSelected--;
    // if (strcmp(btnName, "DOWN") == 0 && notifSelected < total - 1) notifSelected++;
    // if (strcmp(btnName, "OK") == 0 && total > 0) {
    //     removeNotification(notifSelected);
    // }
    // if (strcmp(btnName, "LEFT") == 0) {
    //     clearAllNotifications();
    // }
    // if (strcmp(btnName, "BACK") == 0) {
    //     isNotifications = false; // Выход из меню уведомлений
    //     isMenu = true;           // Возврат в главное меню
    // } staraya huinya

    // new buttons upd

    ButtonEvent btn = readButton();

    if (btn == ButtonEvent::UP && notifSelected > 0) notifSelected--;
    if (btn == ButtonEvent::DOWN && notifSelected < total - 1) notifSelected++;
    if (btn == ButtonEvent::OK && total > 0) removeNotification(notifSelected);
    if (btn == ButtonEvent::LEFT) {
        isNotifications = false; // Выход из меню уведомлений
        isMenu = true;           // Возврат в главное меню        
    }
    if (btn == ButtonEvent::RIGHT) clearAllNotifications();



}