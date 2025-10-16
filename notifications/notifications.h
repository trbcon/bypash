#pragma once
#include <vector>
#include <Arduino.h>

extern bool isNotifications;
extern bool isMenu;


enum class NotificationType { INFO, WARNING, ERROR };

struct Notification {
    String text;
    NotificationType type;
    uint32_t timestamp;
    bool unread;
};

extern std::vector<Notification> notifications;

// Добавить уведомление
void addNotification(const String& text, NotificationType type = NotificationType::INFO);

// Очистить все уведомления
void clearAllNotifications();

// Удалить одно уведомление по индексу
void removeNotification(int index);

// Показать меню уведомлений
void showNotificationsMenu();

// Обработать ввод в меню уведомлений
void handleNotificationsMenuInput();