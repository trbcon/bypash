// #include <BleKeyboard.h>

// BleKeyboard bleKeyboard("ESP32 Keyboard", "Manufacturer", 100);

// void setup() {
//   Serial.begin(115200);
//   bleKeyboard.begin();
// }

// void loop() {
//   if(bleKeyboard.isConnected()) {
//     // Отправка комбинации Ctrl+Alt+Del
//     bleKeyboard.press(KEY_LEFT_CTRL);
//     bleKeyboard.press(KEY_LEFT_ALT);
//     bleKeyboard.press(KEY_DELETE);
//     delay(100);
//     bleKeyboard.releaseAll();
//   }
//   delay(3000);
// }