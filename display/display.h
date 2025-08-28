#pragma once
#include <TFT_eSPI.h>
#include <Arduino.h> 

extern TFT_eSPI tft;


void displayInit();
void drawMenu();
void drawTopBar();