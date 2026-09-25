#include "comm_panel.hpp"

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

namespace {

constexpr uint8_t LCD_ADDR = 0x27;
constexpr uint8_t LCD_COLS = 16;
constexpr uint8_t LCD_ROWS = 2;

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

//for lcd
void printRow(uint8_t row, const char* text) {
  char buf[LCD_COLS + 1];
  snprintf(buf, sizeof(buf), "%-*s", LCD_COLS, text);
  lcd.setCursor(0, row);
  lcd.print(buf);
}

}  

void initDisplay() {
  lcd.init();
  Wire.setClock(400000);
  lcd.backlight();
  lcd.clear();
}

void updateAngleDisplay(int angle) {
  char text[LCD_COLS + 1];
  snprintf(text, sizeof(text), "Angle: %d", angle);
  printRow(0, text);
}



void showButtonMessage(const char* msg) {
  printRow(1, msg);
}