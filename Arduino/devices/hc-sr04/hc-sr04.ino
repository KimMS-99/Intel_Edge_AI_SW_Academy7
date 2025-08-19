 
 
#define trigPin 2 // Trigger Pin
#define echoPin 3 // Echo Pin

 
#define maximumRange   500  // 최대 거리
#define minimumRange   2 // 최소 거리
long duration, distance; // 펄스 시간, 거리 측정용 변수
 
// 프로그램 시작시 초기화 작업
void setup() 
{
  Serial.begin(115200);     // 시리얼 통신 초기화
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
// 계속 실행할 무한 루프
void loop() 
{
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 
 
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 // 측정된 시간을 cm로 환산
 distance = duration/58.2;
 
 if (distance >= maximumRange || distance <= minimumRange)
 {
   Serial.println("out of range");
 }
 else 
 {
  Serial.println(distance);
 }
 
 delay(500);
}
