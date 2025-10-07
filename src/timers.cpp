#include "../timers/timers.h"
#include "../display/display.h"



bool TimerMenuActive = true;
bool TimerActive = false;
bool isEditingTime = false;

int TimerMenuIndex = 0;
int TimerIndexX = 0;

int hour = 0;
int min = 0;
int sec = 0;

int timeSec = 0;

unsigned long MilTimerStart = 0;

const char* sw_menuItems[] = {"Start", "Stop", "Restart", "Exit"};


void TimerMenuOk() {
    switch (TimerMenuIndex) {
        case 0:
            isEditingTime = !isEditingTime;
            break;
        case 1:
            SetTimer();
            TimerActive = true;
            break;
        case 2:
            TimerActive = false;
            break;
        case 3:
            timeSec = (hour * 60 + min) * 60 + sec;
            MilTimerStart = millis();
            TimerActive = true;
            break;
        case 4:
            TimerExit();
            break;
    }
}


void TimerMenuUp() {
    if (!isEditingTime) {
        TimerMenuIndex = (TimerMenuIndex == 0) ? 4 : TimerMenuIndex - 1;
    } else {
        if (TimerIndexX == 0) hour = (hour + 1) % 100;
        else if (TimerIndexX == 1) min = (min + 1) % 60;
        else if (TimerIndexX == 2) sec = (sec + 1) % 60;
    }
}

void TimerMenuDown() {
    if (!isEditingTime) {
        TimerMenuIndex = (TimerMenuIndex == 4) ? 0 : TimerMenuIndex + 1;
    } else {
        if (TimerIndexX == 0) hour = (hour == 0) ? 99 : hour - 1;
        else if (TimerIndexX == 1) min = (min == 0) ? 59 : min - 1;
        else if (TimerIndexX == 2) sec = (sec == 0) ? 59 : sec - 1;
    }
}


void TimerMenuLeft() {
    if (isEditingTime) {
        TimerIndexX = (TimerIndexX == 0) ? 2 : TimerIndexX - 1;
    }
}

void TimerMenuRight() {
    if (isEditingTime) {
        TimerIndexX = (TimerIndexX + 1) % 3;
    }
}


void SetTimer() {
    timeSec = (hour * 60 + min) * 60 + sec;
    MilTimerStart = millis();
}


void TimerUpdate() {
    if (!TimerActive) return;

    if (millis() - MilTimerStart >= 1000) {
        MilTimerStart = millis();
        if (timeSec > 0) timeSec--;
    }

    hour = timeSec / 3600;
    min = (timeSec % 3600) / 60;
    sec = timeSec % 60;

    TimerUI();

    if (timeSec == 0) {
        TimerEnd();
    }
}

void TimerEnd() {
    TimerActive = false;
    // надо добавить звуковой сигнал или мигание
}

void TimerExit() {
    TimerMenuActive = false;
    isEditingTime = false;
    TimerActive = false;
}

void TimerUI() {
    tft.setCursor(10, 10);
    tft.fillRect(10, 10, 160, 30, TFT_BLACK);
    tft.setTextColor(TFT_PINK);
    tft.setTextSize(2);
    tft.printf("%02d:%02d:%02d", hour, min, sec);
}

void TimerMenuUI() {
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE);

    // время
    tft.setCursor(10, 10);
    if (isEditingTime && TimerMenuIndex == 0) {
        if (TimerIndexX == 0) tft.setTextColor(TFT_PINK);
        tft.printf("%02d", hour);
        tft.setTextColor(TFT_WHITE);
        tft.print(":");
        if (TimerIndexX == 1) tft.setTextColor(TFT_PINK);
        tft.printf("%02d", min);
        tft.setTextColor(TFT_WHITE);
        tft.print(":");
        if (TimerIndexX == 2) tft.setTextColor(TFT_PINK);
        tft.printf("%02d", sec);
        tft.setTextColor(TFT_WHITE);
    } else {
        tft.printf("%02d:%02d:%02d", hour, min, sec);
    }

    // меню
    for (int i = 1; i <= 4; i++) {
        tft.setCursor(10, 10 + i * 30);
        if (TimerMenuIndex == i) {
            tft.setTextColor(TFT_PINK);
            tft.print("> ");
        } else {
            tft.setTextColor(TFT_WHITE);
            tft.print("  ");
        }
        tft.print(sw_menuItems[i - 1]);
    }
}
