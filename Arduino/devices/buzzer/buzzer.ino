

int S = 2; // OUTPUT PIN

// 프로그램 시작 - 초기화 작업
void setup()
{
 Serial.begin(115200); // 디버깅 포트 초기화
 Serial.println("Arduino Examples - Passive Buzzer");
 Serial.println(" http://docs.whiteat.com/?p=2363");
 pinMode(S, OUTPUT);
}
int i;

void loop()
{ 
 for (i = 0; i <160; i ++) // outputs sound 1
 {
 digitalWrite (S, HIGH) ;// send pulse
 delay (1) ;// delay 1ms
 digitalWrite (S, LOW) ; // do not send pulse
 delay (1) ;// delay 1ms
 }

 for (i = 0; i <80; i ++) // outputs sound 2
 {
 digitalWrite (S, HIGH) ;// send pulse
 delay (2) ;// delay 1ms
 digitalWrite (S, LOW) ; // do not send pulse
 delay (2) ;// delay 1ms
 }
}
