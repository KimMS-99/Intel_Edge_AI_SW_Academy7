int LED = 9;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  // put your setup code here, to run once:

}

void loop() {
  int val = analogRead(A5) / 4;
  Serial.println(val);
  analogWrite(LED, val);
  // put your main code here, to run repeatedly:

}
