#pragma once
#include "../sensors/pins.h"
#include "../display/display.h"
#include "../buttons/buttons.h"
#include <vector>


//  v nachale nado vizvat setPins

// byte PinMenuX = 0;
byte AllPinsMenuY = 0;


const char* SinglePinMenuArr[] = {"Pin ", "status ", "value "};


void PrintPinMenu() {
    tft.setCursor(0, 7);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    for (int i = 0; i < 3; i++) {

    }

} 

void printPins() {
    tft.setCursor(0, 1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    for (byte i = 0; i < PIN_COL; i++) {
        (i == AllPinsMenuY) ? tft.setTextColor(TFT_WHITE, TFT_BLACK) : tft.setTextColor(TFT_PINK, TFT_BLACK);
        tft.printf("%s | mode: %s | pinNum: %d | %s\n", pins[i].name, pins[i].mode, pins[i].pinNum, pins[i].isAnalog ? "Analog" : "Digital");
    }
}


void PInsUp() {

}

void PInsDown() {

}

void PInsok() {}

void PInsRight() {}

void PInsLeft() {}



void handlePinMenuInput () {
    ButtonEvent btn = readButton();
    int itemsCount = currentMenu->items.size();

    if (btn == ButtonEvent::UP && selectedItem > 0) {
        selectedItem--;
        if (selectedItem < viewOffset) viewOffset = selectedItem;
    }
    if (btn == ButtonEvent::DOWN && selectedItem < itemsCount - 1) {
        selectedItem++;
        if (selectedItem >= viewOffset + maxVisibleItems)
            viewOffset = selectedItem - maxVisibleItems + 1;
    }
    if (btn == ButtonEvent::OK) {
        handleOk();
    }
    if (btn == ButtonEvent::LEFT) {
        handleBack();
    }
}










const int pinNumsArray[] = {26, 27, 14, 12, 13};

const byte PIN_COL = 5;
const byte DIGITAL_COL = 3;
const byte ANALOG_COL = 2;

Pin pins[PIN_COL];

void setPins() {
    static char nameBuffer[PIN_COL][20];    

    // DIGITAL
    for (byte i = 0; i < DIGITAL_COL; i++) {
        snprintf(nameBuffer[i], sizeof(nameBuffer[i]), "Digital pin %d", i + 1);
        pins[i].name = nameBuffer[i];
        pins[i].mode = pins[i].modes[2]; // "off"
        pins[i].isAnalog = false;
        pins[i].pinNum = pinNumsArray[i];
    }

    // ANALOG
    for (byte i = DIGITAL_COL; i < PIN_COL; i++) {
        snprintf(nameBuffer[i], sizeof(nameBuffer[i]), "Analog pin %d", i - DIGITAL_COL + 1);
        pins[i].name = nameBuffer[i];
        pins[i].mode = pins[i].modes[2]; // "off"
        pins[i].isAnalog = true;
        pins[i].pinNum = pinNumsArray[i];
    }
}

// void printPins() {

// }




// const int pinNumsArray[] = {D26, D27, D14, D12, D13};

// const byte PIN_COL = 5;

// const byte DIGITAL_COL = 3;
// const byte ANALOG_COL = 2;

// struct Pin pins[PIN_COL];

// // Pin pinD1;
// // Pin pinD2;
// // Pin pinD3;
// // Pin pinA1; // d12
// // Pin pinA2; // d13

// void setPins(){
//     // DIGITAL
//     for (byte i = 0; i < DIGITAL_COL; i++)
//     {
//         pins[i].name = "digital pin%s", i;
//         pins[i].mode = pins[i].modes[2];
//         isAnalog = false;
//         pins[i].pinNum = pinNumsArray[i];
//     }
//     // ANALOG
//     for (byte i = DIGITAL_COL; i < PIN_COL; i++)
//     {
//         pins[i].name = "anaolog pin%d", i;
//         pins[i].mode = pins[i].modes[2];
//         isAnalog = true;
//         pins[i].pinNum = pinNumsArray[i];
//     }
// }


// void pirntPins() {
//     for (byte i = 0; i < PIN_COL; i++)
//     {
//         Serial.pirnt("%s mode: %s", pins[i].name, pins[i].mode);
//     }
    
// }

// void pinMenuControl(){
    
// }


// void pinsEdit() {
//   
// }



