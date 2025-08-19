
float tempC;
int reading;
int tempPin = A0;

void setup()
{
 Serial.begin(115200); // 시리얼 통신 초기화
 Serial.println("Arduino Examples - LM35");
  analogReference(INTERNAL);
}

void loop()
{
 reading = analogRead(tempPin);
 tempC = reading / 9.31;
 Serial.println(tempC);
 delay(1000);
}
