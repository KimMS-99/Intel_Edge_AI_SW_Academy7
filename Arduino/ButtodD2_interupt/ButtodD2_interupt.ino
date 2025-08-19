#include <LowPower.h>
#include <MsTimer2.h>

const byte ledPin = 13;
const byte interruptPin = 2;  // input pin that the interruption will be attached to
volatile byte state = LOW;  // variable that will be updated in the ISR
volatile bool intFlag = false;
volatile bool timer2Flag = false;
void flash()
{
  timer2Flag = true;
}

void setup() {
  pinMode(ledPin, OUTPUT);
  // pinMode(interruptPin, INPUT_PULLUP);
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, FALLING);
  Serial.begin(9600);
  Serial.println("Setup Start!!");   
  MsTimer2::set(3000, flash); // 500ms period
  MsTimer2::start(); 
}

void loop() {
  if(intFlag)
  {
    state = !state;
    digitalWrite(ledPin, state);
    intFlag = false;
  }

  if(timer2Flag)
  {
    state = !state;
    digitalWrite(ledPin, state);
    timer2Flag = false;
  }
  // delay(500);
  // digitalWrite(ledPin, !digitalRead(ledPin));
  //Serial.println(state);    
  //Serial.flush();
  LowPower.idle(SLEEP_FOREVER, ADC_OFF, TIMER2_ON, TIMER1_OFF, TIMER0_OFF, 
              SPI_OFF, USART0_OFF, TWI_OFF);
}

void blink() {
  intFlag = true;
}