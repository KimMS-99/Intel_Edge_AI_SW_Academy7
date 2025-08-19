#include <IRremote.h>

#define RECV_PIN  7  // 신호선 연결 핀
IRrecv irrecv(RECV_PIN); // 수신기 객체 생성
decode_results results;
int remote_value;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();  // IR 수신 시작
  Serial.println("start");
}

void loop() {
  if (irrecv.decode(&results)) {

    remote_value = results.value; // 값 받아오기

    // if(remote_value == 0x6897 || remote_value == 0xFFFFE57B)
    //   Serial.println("1번");
    // else if(remote_value == 0xFFFF9867)
    //   Serial.println("2번");
    // else if(remote_value == 0xFFFFB04F)
    //   Serial.println("3번");
    if(remote_value != 0xFFFFFFFF)
    {
      Serial.print("값 : ");
      Serial.println(remote_value, HEX);  // 16진수로 출력
    }

    irrecv.resume();  // 다음 신호 수신 준비
  }
}
