

//Set anode interface
int a = 5;
int b = 6;
int c = A2;
int d = A4;
int e = A5;
int f = 3;
int g = 2;
int p = A3; //The decimal point

//Set DIG1
int d1 = A0;

int val = 0;

#define _0 { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW}
#define _1 { LOW, HIGH, HIGH, LOW, LOW, LOW, LOW}
#define _2 { HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH}
#define _3 { HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH}
#define _4 { LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH}
#define _5 { HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH}
#define _6 { HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH}
#define _7 { HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW}
#define _8 { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH}
#define _9 { HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH}
int num_bit[10][7] = { _0, _1, _2, _3, _4, _5, _6, _7, _8, _9 };

void setup()
{
 Serial.begin(115200); //Set baud rate 115200

 pinMode(d1, OUTPUT);
 digitalWrite(d1, LOW);

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
 val = millis() / 1000 %10;

 if (val >= 0)
 {
 pickNumber(val);
 }
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

void dpoint() //Light the decimal point
{
 digitalWrite(p, HIGH);
}
