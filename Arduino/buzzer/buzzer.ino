#define pin 4

int Tones[7] = {261, 294, 330, 349, 392, 440, 494};
int n;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  for(n = 0; n < 7; n++)
  {
    tone(pin, Tones[n]);
    delay(500);
  }
  noTone(pin);
  delay(1000);
}
