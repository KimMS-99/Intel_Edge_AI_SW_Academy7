#define motorPin 9
#define BUTTON_OFF 0
#define BUTTON1_ON 1
#define BUTTON2_ON 2
const int BUTTON_1_PIN = 2;
const int BUTTON_2_PIN = 3;
int motorPwm = 0;
volatile int buttonState;
void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON_1_PIN,INPUT);
  pinMode(BUTTON_2_PIN,INPUT);
  pinMode(motorPin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(BUTTON_1_PIN), button1Isr, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2_PIN), button2Isr, RISING);
  interrupts();
  Serial.begin(9600);
  Serial.println("Start setup()");
}

void loop() {
  // put your main code here, to run repeatedly:

  if(buttonState != BUTTON_OFF)
  {
    if (buttonState == BUTTON1_ON) {
      if(motorPwm > 0)
      {
        motorPwm-=25;  

      }
    }
    else if(buttonState == BUTTON2_ON) {
      if(motorPwm < 250)
      {
        motorPwm+=25; 
      }
    }
    analogWrite(motorPin,motorPwm);
    Serial.println(motorPwm);
    buttonState = BUTTON_OFF;
  }
  delay(50);
}

void button1Isr()
{
  buttonState = BUTTON1_ON;
}
void button2Isr()
{
  buttonState = BUTTON2_ON;
}
