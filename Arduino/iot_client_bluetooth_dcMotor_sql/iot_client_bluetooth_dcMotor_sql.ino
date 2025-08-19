/*
  blue test: 
  http://www.kccistc.net/
  작성일 : 2024.03.22
  작성자 : IoT 임베디드 KSH
*/
#include <SoftwareSerial.h>
#include <Wire.h>
#include <DHT.h>
#include <MsTimer2.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DEBUG
#define CDS_PIN A0
#define BUTTON_PIN 2
#define DHTPIN 4 
#define MOTOR_PIN 6
#define LED_BUILTIN_PIN 13

#define DHTTYPE DHT11
#define ARR_CNT 5
#define CMD_SIZE 60
char lcdLine1[17] = "Smart IoT By KSH";
char lcdLine2[17] = "";
char sendBuf[CMD_SIZE];
char recvId[10] = "KMS_SQL";  // SQL 저장 클라이이언트 ID
bool lastButton = LOW;       // 버튼의 이전 상태 저장
bool currentButton = HIGH;    // 버튼의 현재 상태 저장
bool ledOn = false;      // LED의 현재 상태 (on/off)
bool timerIsrFlag = false;
unsigned int secCount;
int cds=0;
float humi;
float temp;
bool cdsFlag = false;
int getSensorTime;
DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial BTSerial(10, 11); // RX ==>BT:TXD, TX ==> BT:RXD
int varValue;
int varValueold;
void setup()
{
#ifdef DEBUG
  Serial.begin(115200);
  Serial.println("setup() start!");
#endif
  lcd.init();
  lcd.backlight();
  lcdDisplay(0, 0, lcdLine1);
  lcdDisplay(0, 1, lcdLine2);
  pinMode(BUTTON_PIN,INPUT);
  pinMode(LED_BUILTIN_PIN, OUTPUT);
 
  BTSerial.begin(9600); // set the data rate for the SoftwareSerial port
  MsTimer2::set(1000, timerIsr); // 1000ms period
  MsTimer2::start();
  dht.begin();
}

void loop()
{
  if (BTSerial.available())
    bluetoothEvent();

/*
  varValue = analogRead(A1);  //0~1023
  varValue = map(varValue,0,1023,0,100);
  if(abs(varValue-varValueold) > 1)
  {
  //  Serial.println(varValue);
    varValueold = varValue;
    sprintf(sendBuf,"[%s]MOTOR@%d\n","KSH_BT",varValue);
    BTSerial.write(sendBuf);   
  }
*/
  if (timerIsrFlag)
  {
    timerIsrFlag = false;
    cds = map(analogRead(CDS_PIN), 0, 1023, 0, 100);
    humi = dht.readHumidity();
    temp = dht.readTemperature();

    sprintf(lcdLine2,"C:%d T:%d H:%d",cds,(int)temp,(int)humi);
#ifdef DEBUG
 //   Serial.println(lcdLine2);
#endif
    
    lcdDisplay(0, 1, lcdLine2);

    if(getSensorTime != 0 && !(secCount % getSensorTime)) {
      char tempStr[5];
      char humiStr[5];
      dtostrf(humi, 4, 1, humiStr);  //50.0 4:전체자리수,1:소수이하 자리수
      dtostrf(temp, 4, 1, tempStr);  //25.1
      sprintf(sendBuf,"[%s]SENSOR@%d@%s@%s\r\n",recvId,cds,tempStr,humiStr);
      BTSerial.write(sendBuf);   
    }    
    
    if ((cds >= 50) && cdsFlag)
    {
      cdsFlag = false;
      sprintf(sendBuf, "[%s]CDS@%d\n", recvId, cds);
      BTSerial.write(sendBuf, strlen(sendBuf));
    } 
    else if ((cds < 50) && !cdsFlag)
    {
      cdsFlag = true;
      sprintf(sendBuf, "[%s]CDS@%d\n", recvId, cds);
      BTSerial.write(sendBuf, strlen(sendBuf));
    }
  }
  currentButton = debounce(lastButton);   // 디바운싱된 버튼 상태 읽기
  if (lastButton == HIGH && currentButton == LOW)  // 버튼을 누르면...
  {
    ledOn = !ledOn;       // LED 상태 값 반전
    digitalWrite(LED_BUILTIN_PIN, ledOn);     // LED 상태 변경
    sprintf(sendBuf, "[%s]BUTTON@%s\n", recvId, ledOn ? "ON" : "OFF");
    BTSerial.write(sendBuf);
#ifdef DEBUG
    Serial.println(sendBuf);
#endif
  }
  lastButton = currentButton;     // 이전 버튼 상태를 현재 버튼 상태로 설정

#ifdef DEBUG
  if (Serial.available())
    BTSerial.write(Serial.read());
#endif
}
void bluetoothEvent()
{
  int i = 0;
  char * pToken;
  char * pArray[ARR_CNT] = {0};
  char recvBuf[CMD_SIZE] = {0};
  int len = BTSerial.readBytesUntil('\n', recvBuf, sizeof(recvBuf) - 1);

#ifdef DEBUG
  Serial.print("Recv : ");
  Serial.println(recvBuf);
#endif

  pToken = strtok(recvBuf, "[@]");
  while (pToken != NULL)
  {
    pArray[i] =  pToken;
    if (++i >= ARR_CNT)
      break;
    pToken = strtok(NULL, "[@]");
  }
  //recvBuf : [XXX_BTM]LED@ON
  //pArray[0] = "XXX_LIN"   : 송신자 ID
  //pArray[1] = "LED"
  //pArray[2] = "ON"
  //pArray[3] = 0x0
  if ((strlen(pArray[1]) + strlen(pArray[2])) < 16)
  {
    sprintf(lcdLine2, "%s %s", pArray[1], pArray[2]);
    lcdDisplay(0, 1, lcdLine2);
  }
   if (!strcmp(pArray[0], "KMS_ARD")) {
    return ;
   }
  if (!strcmp(pArray[1], "LAMP")) {
    if (!strcmp(pArray[2], "ON")) {
      digitalWrite(LED_BUILTIN_PIN, HIGH);
    }
    else if (!strcmp(pArray[2], "OFF")) {
      digitalWrite(LED_BUILTIN_PIN, LOW);
    }
//    sprintf(sendBuf, "[%s]%s@%s\n", pArray[0], pArray[1], pArray[2]);
    sprintf(sendBuf, "[KMS_SQL]SETDB@%s@%s@%s\n",pArray[1],pArray[2],pArray[0]);
  }
  else if (!strcmp(pArray[1], "MOTOR")) {
    int speed = atoi(pArray[2]);
    speed = map(speed,0,100,0,255);
    analogWrite(MOTOR_PIN,speed);
  //  sprintf(sendBuf, "[%s]%s@%s\n", pArray[0], pArray[1], pArray[2]);
    return;
  }
  else if(!strcmp(pArray[1],"GETSENSOR"))
  {
    if(pArray[2] == NULL){
      getSensorTime = 0;
    }else {
      getSensorTime = atoi(pArray[2]);
      //strcpy(recvId,pArray[0]);
    }
    sprintf(sendBuf,"[%s]SENSOR@%d@%d@%d\n",recvId,cds,(int)temp,(int)humi);
  }
  else if (!strncmp(pArray[1], " New", 4)) // New Connected
  {
    return ;
  }
  else if (!strncmp(pArray[1], " Alr", 4)) //Already logged
  {
    return ;
  }
  else 
  { 
    return;
  }

#ifdef DEBUG
  Serial.print("Send : ");
  Serial.print(sendBuf);
#endif
  BTSerial.write(sendBuf);
}
void timerIsr()
{
  timerIsrFlag = true;
  secCount++;
}
void lcdDisplay(int x, int y, char * str)
{
  int len = 16 - strlen(str);
  lcd.setCursor(x, y);
  lcd.print(str);
  for (int i = len; i > 0; i--)
    lcd.write(' ');
}
boolean debounce(boolean last)
{
  boolean current = digitalRead(BUTTON_PIN);  // 버튼 상태 읽기
  if (last != current)      // 이전 상태와 현재 상태가 다르면...
  {
    delay(5);         // 5ms 대기
    current = digitalRead(BUTTON_PIN);  // 버튼 상태 다시 읽기
  }
  return current;       // 버튼의 현재 상태 반환
}
