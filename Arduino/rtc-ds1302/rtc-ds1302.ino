// RTC DS1302 라이브러리 : http://www.rinkydinkelectronics.com/library.php?id=5
//DS1302.zip

// VCC -> Arduino 5V
// GND -> Arduino GND
// CE(RST) pin -> Arduino Digital 4
// DATA pin -> Arduino Digital 5
// CLK pin -> Arduino Digital 6

#include <DS1302.h>

// DS1302 용 pin 설정
DS1302 rtc(4, 5, 6);
Time t;
void setup()
{
 rtc.halt(false); // 동작 모드로 설정
 rtc.writeProtect(false); // 시간 변경이 가능하도록 설정
 
 Serial.begin(115200); // 시리얼 통신 초기화
 Serial.println("Arduino Examples - RealTime Clock DS1302");
 Serial.println(" http://docs.whiteat.com/?p=2171");


//  rtc.setDOW(FRIDAY); // SUNDAY 로 설정
//  rtc.setTime(17, 10, 00); // 시간을 12:00:00로 설정 (24시간 형식)
//  rtc.setDate(16, 5, 2025); // 2015년 8월 16일로 설정
}

void loop()
{
 // 요일 출력
 Serial.print(rtc.getDOWStr());
 Serial.print(" ");
 
 // 날짜 출력
 Serial.print(rtc.getDateStr());
 Serial.print(" -- ");

 // 시간 출력
 Serial.println(rtc.getTimeStr());


   // Get data from the DS1302
  t = rtc.getTime();
  
  // Send date over serial connection
  Serial.print("Today is the ");
  Serial.print(t.date, DEC);
  Serial.print(". day of ");
  Serial.print(rtc.getMonthStr());
  Serial.print(" in the year ");
  Serial.print(t.year, DEC);
  Serial.println(".");
  
  // Send Day-of-Week and time
  Serial.print("It is the ");
  Serial.print(t.dow, DEC);
  Serial.print(". day of the week (counting monday as the 1th), and it has passed ");
  Serial.print(t.hour, DEC);
  Serial.print(" hour(s), ");
  Serial.print(t.min, DEC);
  Serial.print(" minute(s) and ");
  Serial.print(t.sec, DEC);
  Serial.println(" second(s) since midnight.");
 // 1초 기다리기
  delay (1000);
  Serial.println("  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -");
}
