#define pinPIR A0
#define pinLED 13

// 프로그램 초기화
void setup()
{
  Serial.begin(115200);
  Serial.println("Arduino Examples - PIR Motion Detector Sensor");
  Serial.println("    http://docs.whiteat.com/?p=3627");
  
  pinMode(pinPIR, INPUT);
  pinMode(pinLED, OUTPUT);

}

// 계속 실행할 무한 루프
void loop() 
{
  int i = analogRead(pinPIR);
  int l = map(i,0,1023,0,255);

  Serial.print(i);
  Serial.print(" / ");
  Serial.println(l);
  analogWrite(pinLED, l);

  delay(100);
}
