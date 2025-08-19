// LCD를 사용하기 위해 라이브러리를 추가합니다.
// U8glib by oliver

#include <U8glib.h>
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);  // I2C / TWI

char oledLine1[17]="IoT Home By KSH";
char oledLine2[17]="WiFi Connecting";
char oledLine3[17]="ABCD";
char oledLine4[17]="1234";

void setup() {
  // put your setup code here, to run once:
 //u8g.setRot180();
  u8g.setColorIndex(1);
  u8g.setFont(u8g_font_unifont);
  displayDrawStr();
}

void loop() {
  // put your main code here, to run repeatedly:
/*  displayDrawStr();
  delay(500);
  displayClear();
  delay(500);
*/
  
}
void displayDrawStr()
{
  u8g.firstPage();
  do {
     u8g.drawStr( 0, 15, oledLine1);
     u8g.drawStr( 0, 31, oledLine2);
     u8g.drawStr( 0, 47, oledLine3);
     u8g.drawStr( 0, 63, oledLine4);
  } while( u8g.nextPage() );
}
void displayClear() {
  u8g.firstPage();
  do {
  }while(u8g.nextPage());
}
