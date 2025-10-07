#include "esp_timer.h"

extern bool isMenu;

extern bool TimerMenuActive;
extern bool TimerActive;
extern bool isEditingTime;

extern int TimerMenuIndex;
extern int TimerIndexX;


extern int HourTimer;
extern int MinuteTimer;
extern int SecTimer;

extern int timeSec;

extern unsigned long MillisecTimerStart;


extern const char* sw_menuTimerItems[];


void SetTimer();
void TimerEnd();

void TimerMenuOk();
void TimerMenuUp();
void TimerMenuDown();
void TimerMenuRight();
void TimerMenuLeft();

void TimerUpdate();
void TimerMenuUI();
void TimerUI();

void TimerExit();