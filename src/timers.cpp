#include "../timers/timers.h"
#include "../display/display.h"



bool TimerMenuActive = false;
bool TimerActive = false;
bool isEditingTime = false;

int TimerMenuIndex = 0;
int TimerIndexX = 0;

int HourTimer = 0;
int MinuteTimer = 0;
int SecTimer = 0;

int timeSec = 0;

unsigned long MillisecTimerStart = 0;

const char* sw_menuTimerItems[] = {"Start", "Stop", "Restart", "Exit"};


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
            timeSec = (HourTimer * 60 + MinuteTimer) * 60 + SecTimer;
            MillisecTimerStart = millis();
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
        if (TimerIndexX == 0) HourTimer = (HourTimer + 1) % 100;
        else if (TimerIndexX == 1) MinuteTimer = (MinuteTimer + 1) % 60;
        else if (TimerIndexX == 2) SecTimer = (SecTimer + 1) % 60;
    }
}

void TimerMenuDown() {
    if (!isEditingTime) {
        TimerMenuIndex = (TimerMenuIndex == 4) ? 0 : TimerMenuIndex + 1;
    } else {
        if (TimerIndexX == 0) HourTimer = (HourTimer == 0) ? 99 : HourTimer - 1;
        else if (TimerIndexX == 1) MinuteTimer = (MinuteTimer == 0) ? 59 : MinuteTimer - 1;
        else if (TimerIndexX == 2) SecTimer = (SecTimer == 0) ? 59 : SecTimer - 1;
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
    timeSec = (HourTimer * 60 + MinuteTimer) * 60 + SecTimer;
    MillisecTimerStart = millis();
    TimerActive = true;
}


void TimerUpdate() {
    if (!TimerActive) return;

    if (millis() - MillisecTimerStart >= 1000) {
        MillisecTimerStart = millis();
        if (timeSec > 0) timeSec--;
    }

    HourTimer = timeSec / 3600;
    MinuteTimer = (timeSec % 3600) / 60;
    SecTimer = timeSec % 60;

    // TimerUI();

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
    tft.printf("%02d:%02d:%02d", HourTimer, MinuteTimer, SecTimer);
}

void TimerMenuUI() {
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE);

    // время
    tft.setCursor(10, 10);
    if (isEditingTime && TimerMenuIndex == 0) {
        if (TimerIndexX == 0) tft.setTextColor(TFT_PINK);
        tft.printf("%02d", HourTimer);
        tft.setTextColor(TFT_WHITE);
        tft.print(":");
        if (TimerIndexX == 1) tft.setTextColor(TFT_PINK);
        tft.printf("%02d", MinuteTimer);
        tft.setTextColor(TFT_WHITE);
        tft.print(":");
        if (TimerIndexX == 2) tft.setTextColor(TFT_PINK);
        tft.printf("%02d", SecTimer);
        tft.setTextColor(TFT_WHITE);
    } else {
        tft.printf("%02d:%02d:%02d", HourTimer, MinuteTimer, SecTimer);
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
        tft.print(sw_menuTimerItems[i - 1]);
    }
}
