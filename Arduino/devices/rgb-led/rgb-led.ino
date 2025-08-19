
int R = 11; // OUTPUT PIN red
int G = 10; // OUTPUT PIN green
int B = 9; // OUTPUT PIN blue

// 프로그램 시작 - 초기화 작업
void setup()
{
 Serial.begin(115200); // 시리얼 통신 초기화
 Serial.println("Arduino Examples - RGB LED");
 pinMode(R, OUTPUT);
 pinMode(G, OUTPUT);
 pinMode(B, OUTPUT);
}

void loop()
{ 
 // RED
 digitalWrite(R, HIGH);
 delay(1000);

 // GREEN
 digitalWrite(R, LOW);
 digitalWrite(G, HIGH);
 delay(1000);

 // BLUE
 digitalWrite(G, LOW);
 digitalWrite(B, HIGH);
 delay(1000);

 // RED + GREEN = YELLOW
 digitalWrite(B, LOW);
 digitalWrite(R, HIGH);
 digitalWrite(G, HIGH);
 delay(1000);

 // RED + BLUE = MAGENTA
 digitalWrite(B, HIGH);
 digitalWrite(R, HIGH);
 digitalWrite(G, LOW);
 delay(1000);

 // GREEN + BLUE = CYON
 digitalWrite(B, HIGH);
 digitalWrite(R, LOW);
 digitalWrite(G, HIGH);
 delay(1000);

 // RED + GREEN + BLUE = WHITE
 digitalWrite(B, HIGH);
 digitalWrite(R, HIGH);
 digitalWrite(G, HIGH);
 delay(1000);

 // ALL OFF
 digitalWrite(B, LOW);
 digitalWrite(R, LOW);
 digitalWrite(G, LOW);
 delay(1000);
}
