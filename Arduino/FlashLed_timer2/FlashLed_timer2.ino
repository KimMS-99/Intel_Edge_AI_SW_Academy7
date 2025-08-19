/*
  MsTimer2 is a small and very easy to use library to interface Timer2 with
  humans. It's called MsTimer2 because it "hardcodes" a resolution of 1
  millisecond on timer2
  For Details see: http://www.arduino.cc/playground/Main/MsTimer2
*/
#include <MsTimer2.h>

// Switch on LED on and off each half second

#if ARDUINO >= 100
const int led_pin = LED_BUILTIN;	// 1.0 built in LED pin var
#else
const int led_pin = 13;			// default to pin 13
#endif

volatile bool timer2Flag=false;
volatile unsigned long timer2Cnt;
boolean state = LOW;
void flash()
{
  timer2Flag = true;
  timer2Cnt++;
}

void setup()
{
  pinMode(led_pin, OUTPUT);
  MsTimer2::set(1000, flash); // 500ms period
  MsTimer2::start();
}

void loop()
{
    if(timer2Flag)
    {
      if(!(timer2Cnt%2))  //2초 마다
      {
        state = !state;
        digitalWrite(led_pin, state);
        timer2Flag = false;
      }
    }
}
