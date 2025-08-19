
int R = 2;

// 프로그램 시작 - 초기화 작업
void setup()
{
 Serial.begin(115200); // 시리얼 통신 초기화
 pinMode(R, OUTPUT);
 digitalWrite(R, LOW);
}

void loop()
{
 digitalWrite(R, HIGH); // relay on (for 2 Second)
 delay(2000);
 digitalWrite(R, LOW); // relay off (for 1 Second)
 delay(1000);
}
