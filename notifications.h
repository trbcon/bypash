

std::string notif[] = {};
int notifSize;
unsigned long notifStartTime;




void setNotification(std::string StrNotification){
    notifSize = sizeof(notif) / sizeof(std::string);
    notif[notifSize] = StrNotification;
    deleteNotification();
}



void printNotifications(){
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    for(int i; i < notifSize; i++){
        tft.setCursor(110, i*8);
        tft.print(notif[i]);
    }
}

void deleteNotification() {
    notifStartTime = millis();
    // if (millis() - startTime >= 3000) {
}