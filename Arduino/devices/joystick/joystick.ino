
int X = A0; // x
int Y = A1; // y

int S = 2;

// 프로그램 시작 - 초기화 작업
void setup()
{
 Serial.begin(115200); // 시리얼 통신 초기화
 pinMode(X, INPUT);
 pinMode(Y, INPUT);
 pinMode(S, INPUT);
 digitalWrite(S, HIGH); 
}
void loop()
{
 int x, y, s;
 x = analogRead(X);
 y = analogRead(Y);
 s = digitalRead(S);
 Serial.print("X="); Serial.print(x, DEC);
 Serial.print(", Y=");
 Serial.print(y, DEC);
 Serial.print(",S=");
 Serial.println(s, DEC);
 delay(100);
}
