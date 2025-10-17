// #pragma once
// #include <Arduino.h>

extern bool isAllPinsMenu;
extern bool isOncePinMenu;

// extern byte PinMenuX;
extern byte AllPinsMenuY;


struct Pin {
    const char* name;
    std::vector<const char*> modes = {"output", "input", "off"};
    const char* mode = nullptr; 
    bool isAnalog;
    int pinNum;
};


extern const byte DIGITAL_COL;
extern const byte PIN_COL;
extern const byte ANALOG_COL;


void PInsUp();
void PInsDown();
void PInsok();
void PInsRight();
void PInsLeft();

void PrintPinMenu();
void printPins();
void handlePinMenuInput();
void setPins();

