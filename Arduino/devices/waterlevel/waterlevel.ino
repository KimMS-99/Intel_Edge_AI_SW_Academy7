
int S = A0;  // INPUT PIN

// 프로그램 시작 - 초기화 작업
void setup()
{
  Serial.begin(115200);     // 시리얼 통신 초기화
  Serial.println("Arduino Examples - Water Level Detector");
  pinMode(S, INPUT);
}

void loop()
{
  Serial.print("LEVEL="); Serial.println(analogRead(S), DEC);
  delay(100);
}
