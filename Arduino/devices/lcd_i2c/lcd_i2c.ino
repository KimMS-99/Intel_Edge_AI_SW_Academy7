// I2C LCD 라이브러리 : LiquidCrystal I2C By Frank de Brabander
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// 16x2 LCD객체를 생성합니다. 이때 확인한 I2C의 주소값을 넣어줍니다.
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // 초기 사용시 I2C LCD 초기화 및 LCD 백라이트를 켜줍니다.
  lcd.init();
  lcd.backlight();
}

void loop() { 

  int value = 1;
  for(value=1; value<4 ; value++)
  {
    if(value=1){
      lcd.setCursor(0,0);           // 0번 행 0번 열부터 출력합니다.
      lcd.print("    lcd test    ");     
      delay(1000);
    }
    if(value=2){
      lcd.setCursor(0,1);           // 1번 행 0번 열부터 출력합니다.
      lcd.print("    Hello!!    ");
      delay(1000);
    }
     if(value=3){
      lcd.setCursor(0,0);           // 0번 행 0번 열부터 출력합니다.
      lcd.print("    lcd test    ");      
      lcd.setCursor(0,1);           // 1번 행 0번 열부터 출력합니다.
      lcd.print(" Hello People!! ");    
      delay(1000);
     }
     
  lcd.clear();
  }
  delay(1000);

}
