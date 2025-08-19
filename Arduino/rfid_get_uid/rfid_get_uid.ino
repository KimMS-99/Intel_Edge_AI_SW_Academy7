#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9   // Reset pin
#define SS_PIN 10   // Slave select pin

MFRC522 rfid(SS_PIN, RST_PIN);  // MFRC522 객체 생성

void setup() {
  Serial.begin(115200);  // 시리얼 통신 시작
  SPI.begin();         // SPI 통신 시작
  rfid.PCD_Init();     // RFID 초기화
  Serial.println("RFID 리더기 준비됨. 태그를 가까이 대세요.");
}

void loop() {
  // 카드가 감지되지 않으면 return
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i]);
  }
  Serial.println();

  rfid.PICC_HaltA();  // 카드 멈춤
  rfid.PCD_StopCrypto1();  // 암호화 종료
}
