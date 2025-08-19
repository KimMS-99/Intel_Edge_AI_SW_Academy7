#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS1302.h>
#include <MsTimer2.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
DS1302 rtc(4, 5, 6);
Time t;

volatile bool updateFlag = false;

char dateStr[17];
char timeStr[17];
const char* dowTable[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

void setup() {
  Serial.begin(115200);

  rtc.halt(false);
  rtc.writeProtect(false);

  // rtc.setDOW(MONDAY);
  // rtc.setTime(9, 32, 00);           // 시, 분, 초
  // rtc.setDate(19, 5, 2025);          // 일, 월, 년

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" ");
  lcd.setCursor(0, 1);
  lcd.print(" ");

  MsTimer2::set(1000, onTimer); // 1초마다 onTimer 실행
  MsTimer2::start();
}

void loop() {
  if (updateFlag) {
    updateFlag = false;

    t = rtc.getTime();
    snprintf(dateStr, sizeof(dateStr), "%04d-%02d-%02d", t.year, t.mon, t.date);
    snprintf(timeStr, sizeof(timeStr), "%02d:%02d:%02d %s", t.hour, t.min, t.sec, dowTable[t.dow]);

    lcd.setCursor(0, 0);
    lcd.print(dateStr);
    lcd.setCursor(0, 1);
    lcd.print(timeStr);
    Serial.println(timeStr);
  }
}

void onTimer() {
  updateFlag = true;
}

