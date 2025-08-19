
//Set anode interface
int a = 3;
int b = 7;
int c = A2;
int d = A4;
int e = A5;
int f = 4;
int g = A1;
int p = A3;    //The decimal point

//Set DIG1, DIG2, DIG3, DIG4
int d1 = 2; //Thousand
int d2 = 5; //Hundred
int d3 = 6; //Ten
int d4 = A0;//One


int val4 = 0;  // DIG1 용 변수
int val3 = 0;  // DIG2 용 변수
int val2 = 0;  // DIG3 용 변수
int val1 = 0;  // DIG4 용 변수

const int DELAY = 1000;  // led display delay
int val = 0;

int digitpin[5] = { -1, d4, d3, d2, d1 };

#define _0 {    HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW}
#define _1 {    LOW, HIGH, HIGH, LOW, LOW, LOW, LOW}
#define _2 {    HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH}
#define _3 {    HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH}
#define _4 {    LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH}
#define _5 {    HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH}
#define _6 {    HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH}
#define _7 {    HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW}
#define _8 {    HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH}
#define _9 {    HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH}
int num_bit[10][7] = { _0, _1, _2, _3, _4, _5, _6, _7, _8, _9 };

void setup()
{
  Serial.begin(115200); //Set baud rate 115200

  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  pinMode(p, OUTPUT);
}

void loop()
{
  val = millis() / 1000;

  val4 = (val / 1000) % 10;
  val3 = (val / 100) % 10;
  val2 = (val / 10) % 10;
  val1 = val % 10;

  if (val >= 1000)
  {
    clearLEDs();
    pickDigit(4);
    pickNumber(val4);
    delayMicroseconds(DELAY);
  }

  if (val >= 100)
  {
    clearLEDs();
    pickDigit(3);
    pickNumber(val3);
    delayMicroseconds(DELAY);
  }

  if (val >= 10)
  {
    clearLEDs();
    pickDigit(2);
    pickNumber(val2);
    delayMicroseconds(DELAY);
  }

  if (val >= 0)
  {
    clearLEDs();
    pickDigit(1);
    pickNumber(val1);
    delayMicroseconds(DELAY);
  }
}

void pickDigit(int x)
{
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);

  digitalWrite(digitpin[x], LOW);
}

void pickNumber(int n) 
{
  digitalWrite(a, num_bit[n][0]);
  digitalWrite(b, num_bit[n][1]);
  digitalWrite(c, num_bit[n][2]);
  digitalWrite(d, num_bit[n][3]);
  digitalWrite(e, num_bit[n][4]);
  digitalWrite(f, num_bit[n][5]);
  digitalWrite(g, num_bit[n][6]);
}

void clearLEDs()
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);

  digitalWrite(p, LOW);
}

void dpoint() //Light the decimal point
{
  digitalWrite(p, HIGH);
}
