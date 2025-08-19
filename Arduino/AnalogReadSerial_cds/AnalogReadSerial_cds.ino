/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/AnalogReadSerial/
*/
#define motorPin 9
// the setup routine runs once when you press reset:

int sensorValueOld;
int pwm;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  Serial.println("Start");
}

// the loop routine runs over and over again forever:
void loop() {

  // read the input on analog pin 0:
  int sensorValue = analogRead(A1);
  // print out the value you read:
  if(sensorValue > 180 && sensorValueOld == 1){
    pwm = 250;
    Serial.println("LED ON");
    sensorValueOld = 0;
  }
  else if(sensorValue < 150 && sensorValueOld == 0)
  {
    pwm = 0;
    Serial.println("LED OFF");
    sensorValueOld = 1;
  }
    analogWrite(motorPin, pwm);
  delay(30);  // delay in between reads for stability
}

void print(int sensorValue, int pwm){
    pwm = map(sensorValue, 0, 1023, 0, 255);
    Serial.print(sensorValue);
    Serial.print(" V : ");
    Serial.print(5/1024.0 * sensorValue, 4);
    Serial.print(" pwm : ");
    Serial.println(pwm);
}
