#include <menu.h>



void drawMenu() {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.println(currentMenu->name);

  for (int i = 0; i < maxVisibleItems; i++) {
    int menuIndex = viewOffset + i;
    if (menuIndex >= currentMenu->items.size()) break;

    int y = (i + 1) * 10;

    if (menuIndex == selectedItem) {
      tft.setTextColor(TFT_YELLOW, TFT_BLACK);
      tft.setCursor(0, y);
      tft.print(">");
    } else {
      tft.setCursor(0, y);
      tft.print(" ");
    }

    tft.setCursor(10, y);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.print(currentMenu->items[menuIndex]);
  }
}