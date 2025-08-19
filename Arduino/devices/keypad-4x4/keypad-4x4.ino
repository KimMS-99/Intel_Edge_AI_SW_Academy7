/*
Keypad 라이브러리 : Keypad Mark Stanley, Alexander Brevig
pin 연결
keypad pin 1 --> arduino pin 10
      : 
keypad pin 8 --> arduino pin 2
*/
#include <Keypad.h>

const byte ROWS = 4; // 4 Rows
const byte COLS = 4; // 4 Columns

// key pad 정의
char hexaKeys[ROWS][COLS] = {
  { '0', '1', '2', '3' },
  { '4', '5', '6', '7' },
  { '8', '9', 'A', 'B' },
  { 'C', 'D', 'E', 'F' }
};
//byte rowPins[ROWS] = { 2, 3, 4, 5 }; // ROW 열에 연결할 핀
byte rowPins[ROWS] = { 5, 4, 3, 2 }; // ROW 열에 연결할 핀
byte colPins[COLS] = { 6, 7, 8, 9 }; // COLUMN 열에 연결할 핀

//Keypad 인스턴스 생성
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup(){
  Serial.begin(115200);     // 시리얼 통신 초기화
  Serial.println("Arduino Examples - Keypad 4x4");
}

void loop(){
  char customKey = customKeypad.getKey();

  if (customKey){
    Serial.println(customKey);
  }
}
