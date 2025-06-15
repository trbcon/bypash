

std::string notif[] = {};
int notifSize;


void setNotification(std::string StrNotification){
    notifSize = sizeof(notif) / sizeof(std::string);
    notif[notifSize] = StrNotification;
}



void printNotifications(){
    tft.setCursor(0, y);
}

void deleteNotification(){

}