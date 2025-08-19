
//int AnalogPin = A0;    // Analog input
int DigitalPin = 7;  // Digital input
int LedPin = 13;     // select the pin for the LED
int gValue = 0;     // variable for Sensor Data
void setup ()
{
  pinMode (LedPin, OUTPUT);
  pinMode (DigitalPin, INPUT);
  Serial.begin (115200);
}
void loop ()
{
  gValue = digitalRead(DigitalPin);
  if (gValue){            
    digitalWrite (LedPin, HIGH);
  }else {
     digitalWrite (LedPin, LOW);
  }
  Serial.print ("Sensor Value : ");
  Serial.println (gValue, DEC);
  delay(500);
}
