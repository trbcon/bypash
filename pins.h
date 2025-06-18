
struct Pin {
    const char* name;
    std::vector<const char*> modes = {"output", "input", "off"}
    char* mode = Pin.modes[2];
    bool isAnalog;

    int pinNum;
};

const int pinNumsArray[] = {D26, D27, D14, D12, D13};

const byte PIN_COL = 5;

const byte DIGITAL_COL = 3;
const byte ANALOG_COL = 2;

struct Pin pins[PIN_COL];

// Pin pinD1;
// Pin pinD2;
// Pin pinD3;
// Pin pinA1; // d12
// Pin pinA2; // d13

void setPins(){
    // DIGITAL
    for (byte i = 0; i < DIGITAL_COL; i++)
    {
        pins[i].name = "digital pin%s", i 
        pins[i].mode = pins[i].modes[2]
        isAnalog = false;
        pins[i].pinNum = pinNumsArray[i];
    }
    // ANALOG
    for (byte i = DIGITAL_COL; i < PIN_COL; i++)
    {
        pins[i].name = "anaolog pin%d", i 
        pins[i].mode = pins[i].modes[2]
        isAnalog = true;
        pins[i].pinNum = pinNumsArray[i];
    }
}


void pirntPins() {
    for (byte i = 0; i < PIN_COL; i++)
    {
        Serial.pirnt("%s mode: %s", pins[i].name, pins[i].mode)
    }
    
}

void pinMenuControl(){
    
}


// void pinsEdit() {
//   
// }



