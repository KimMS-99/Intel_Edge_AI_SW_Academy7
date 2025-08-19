#include <LowPower.h>

const byte ledPin = 13;
const byte interruptPin = 2;  // input pin that the interruption will be attached to
volatile byte state = LOW;  // variable that will be updated in the ISR
volatile bool intFlag = false;
void setup() {
  pinMode(ledPin, OUTPUT);
//  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(interruptPin,INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, FALLING);
  Serial.begin(9600);
  Serial.println("setup start!!");
}

void loop() {

  if(intFlag)
  {
    state = !state;
    digitalWrite(ledPin, state);
    intFlag = false;
  }
  
//  Serial.println(state);
  LowPower.idle(SLEEP_FOREVER, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
               SPI_OFF, USART0_OFF, TWI_OFF);
}

void blink() {
  intFlag = true;
//  state = !state;
}