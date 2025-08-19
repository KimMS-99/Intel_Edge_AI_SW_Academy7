# WebEngineWidgets을 사용해서 라즈베리파이에 연결된 카메라 화면 띄우기

## 라즈베리파이 띄우기

라즈베리파이에 카메라 연결 후 
[mjpg-streamer](https://github.com/jacksonliam/mjpg-streamer/tree/master) 를 설치 후 웹 페이지에 (http://raspberrt_ip_address:PORT)로 접속 하여 되는지 확인

## 코드 설명

.pro 파일에 webenginewidgets를 추가해야한다.

헤더파일에
```cpp
#include <QWebEngineView>

// 클래스 내에 선언
QWebEngineView *p; 
```
추가 후 .cpp 파일에
```cpp
p = new QWebEngineView(this);
p->load(QUrl("Ip or Address")); // 특정 URL의 콘텐츠를 불러오도록 지시하는 역할
// p->load(...): QWebEngineView의 멤버 함수로, 주어진 URL의 콘텐츠를 로드
ui->Layout->addWidget(p;)
```

+ **화면**
![WebCamView 실행 화면](../docs/Img/WebCamView.png)
