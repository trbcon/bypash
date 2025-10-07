#include "esp_timer.h"

extern bool isMenu;

extern bool TimerMenuActive;
extern bool TimerActive;
extern bool isEditingTime;

extern int TimerMenuIndex;
extern int TimerIndexX;


extern int hour;
extern int min;
extern int sec;

extern int timeSec;

extern int MilTimerStart;


extern const char* sw_menuItems[];


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