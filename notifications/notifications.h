#pragma once
#include <vector>
#include <string>

struct Notification {
    std::string text;
    // unsigned long startTime;
};

extern std::vector<Notification> notifications;

void setNotification(const std::string& strNotification);
void clearNotifications();
// void printNotifications();
void printMiniNotification();
void notificationsMenu();
void deleteMiniNotification();