void StartWiFiAttack() {
    Serial.println("Hello World");
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(10, 10);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println("Hello World");
    delay(1000);
    drawMenu(); 
}