
 
// 프로그램 시작 - 초기화 작업
void setup()
{
 Serial.begin(115200); // 시리얼 통신 초기화
 pinMode(A0, INPUT);
}

void loop()
{
 int adcValue = analogRead(A0);
 Serial.println(adcValue);
}
