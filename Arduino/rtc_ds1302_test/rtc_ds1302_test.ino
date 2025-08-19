// RTC DS1302 라이브러리 : http://www.rinkydinkelectronics.com/library.php?id=5
//DS1302.zip

// VCC -> Arduino 5V
// GND -> Arduino GND
// CE(RST) pin -> Arduino Digital 4
// DATA pin -> Arduino Digital 5
// CLK pin -> Arduino Digital 6

#include <DS1302.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <MsTimer2.h>
#include <LowPower.h>

// DS1302 용 pin 설정
DS1302 rtc(4, 5, 6);
Time t;
LiquidCrystal_I2C lcd(0x27,16,2); 
int h, m, s, a, hh, mm, ss, flag = 1;
char line1[16], line2[16];
char temp[10], temp2[16];
bool timer2Flag;

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.init();
 rtc.halt(false); // 동작 모드로 설정
 rtc.writeProtect(false); // 시간 변경이 가능하도록 설정
 
 Serial.begin(115200); // 시리얼 통신 초기화
 Serial.println("Arduino Examples - RealTime Clock DS1302");
 Serial.println(" http://docs.whiteat.com/?p=2171");
  lcd.backlight();

  t = rtc.getTime();

  a = t.year;
  Serial.print(a);
  sprintf(temp, "%d", a);
  strcat(line1, temp);

  a = t.mon;
  line1[strlen(line1)] = ' ';
  if(a < 10)
    line1[strlen(line1)] = '0';
  sprintf(temp, "%d", a);
  strcat(line1, temp);

  a = t.date;
  line1[strlen(line1)] = ' ';
      if(a < 10)
        line2[strlen(line1)] = '0';
      sprintf(temp, "%d", a);
      strcat(line1, temp);
    hh = t.hour;
    if(hh < 10)
      line2[0] = '0';
    sprintf(temp, "%d", hh);
    strcat(line2, temp);
    line2[strlen(line2)] = ':';

    mm = t.min;
    if(mm < 10)
      line2[strlen(line2)] = '0';
    sprintf(temp, "%d", mm);
    strcat(line2, temp);
    line2[strlen(line2)] = ':';
      
    ss = t.sec;
    if(ss < 10)
      line2[strlen(line2)] = '0';
    sprintf(temp, "%d", ss);
    strcat(line2, temp);
    line2[strlen(line2)] = ' ';
    sscanf(rtc.getDOWStr(), "%s", temp);
    for(int i = 0; i < 3; i++)
      line2[strlen(line2)] = temp[i];

    strcpy(temp, line2);
  MsTimer2::set(1000, flash); // 500ms period
  MsTimer2::start();  

//  rtc.setDOW(FRIDAY); // SUNDAY 로 설정
//  rtc.setTime(17, 10, 00); // 시간을 12:00:00로 설정 (24시간 형식)
//  rtc.setDate(16, 5, 2025); // 2015년 8월 16일로 설정
}

void loop()
{
  if(flag == 1)
  {
    t = rtc.getTime();
    h = t.hour;
    m = t.min;
    s = t.sec;
    if(hh != h)
    { 
      sprintf(temp, "%d", h);
      if(h < 10)
      {
        line2[0] = '0';
        line2[1] = temp[0];
      }
      else
        strncpy(&line2[0], temp, 2);
    }
    if(mm != m)
    {
      sprintf(temp, "%d", m);
      if(m < 10)
      {
        line2[3] = '0';
        line2[4] = temp[0];
      }
      else
        strncpy(&line2[3], temp, 2);
    }
    if(ss != s)
    {
      sprintf(temp, "%d", s);
      if(s < 10)
      {
        line2[6] = '0';
        line2[7] = temp[0];
      }
      else
        strncpy(&line2[6], temp, 2);
    }
    Serial.println(line1);
    Serial.println(line2);

    lcd.setCursor(1, 0);
    lcd.print(line1);
    lcd.setCursor(1, 1);
    lcd.print(line2);
    flag = 0;
  }

  LowPower.idle(SLEEP_FOREVER, ADC_OFF, TIMER2_ON, TIMER1_OFF, TIMER0_OFF, 
                SPI_OFF, USART0_OFF, TWI_OFF);
}

void flash()
{
  flag = 1;
  Serial.println("Test");
}
