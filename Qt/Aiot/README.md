# Qt 기반 Aiot 애플리케이션

라즈베리파이에서 [디바이스 드라이버(ledkey_poll_dev.c)](https://github.com/KimMS-99/IntelAISW_LinuxBsp/blob/main/DeviceDriver/p432_ledkey_poll/ledkey_poll_dev.c)를 이용해 LED 및 버튼(Key)을 제어하고, 소켓 통신을 통해 [서버(iot_server.c)](https://github.com/KimMS-99/C_CPP/blob/main/Tcp%3AIp/iot_server/iot_server.c)와 연결하여 데이터를 주고받기 위해 만든 예제이다.

## 주요 기능

*   **디바이스 직접 제어 (`tab1devcontrol`):** 커널 모듈(`ledkey_poll_dev`)을 이용해 라즈베리파이의 LED를 켜고 끄며, 버튼 입력 상태를 실시간으로 확인한다.
*   **원격 서버 연동 (`tab2socketclient`):** TCP/IP 소켓 클라이언트를 구현하여 원격 IoT 서버와 연결하고, 명령을 보내거나 센서 데이터를 수신한다.
*   **통합 제어 패널 (`tab3controlpannel`):** 1번 탭의 디바이스 제어와 2번 탭의 소켓 통신 기능을 통합하여, UI 버튼으로 LED 제어 명령을 서버에 전송하는 등 복합적인 제어를 수행한다.
*   **실시간 데이터 시각화 (`tab4sensorchart`):** 서버로부터 수신한 조도(Light) 및 온도(Temperature) 센서 값을 실시간 라인 차트로 시각화하여 보여준다.
*   **센서 데이터 관리 (`tab5sensordatabase`):** 수집된 센서 데이터를 SQLite 데이터베이스에 저장하고, 테이블 뷰를 통해 저장된 데이터를 조회 및 관리할 수 있다.
*   **웹캠 스트리밍 (`tab6webcamera`):** `mjpg-streamer`를 원격으로 실행하고, 그 영상을 `QWebEngineView`를 통해 실시간으로 스트리밍하여 보여준다.
*   **로컬 캠 뷰어 (`tab7camviewerthread`):** OpenCV와 `QThread`를 사용하여 로컬 웹캠 영상을 별도 스레드에서 처리하고 GUI에 표시하며, 스냅샷 기능을 제공한다.

## 사전 준비 사항

Qt 애플리케이션을 실행하기 전에, 타겟 보드(라즈베리파이)에서 다음 작업이 반드시 선행되어야 한다.

1.  **커널 모듈 적재**: 컴파일된 디바이스 드라이버 파일(`ledkey_poll_dev.ko`)을 커널에 로드.
    ```bash
    sudo insmod ledkey_poll_dev.Ko
    ```

2.  **디바이스 파일 생성**: 애플리케이션이 드라이버와 통신할 수 있도록 `/dev` 디렉토리에 캐릭터 디바이스 파일을 생성. 이때 주 번호(Major Number)는 드라이버 코드에 명시된 `230`을 사용해야 한다.
    ```bash
    sudo mknod /dev/ledkey c 230 0
    ```

3.  **서버 실행**: 소켓 통신을 위해 라즈베리파이에서 서버 프로그램을 실행해야 한다.
    ```bash
    ./iot_server 5000
    ```

## 출력 화면

[`tab1devcontrol`](../docs/Markdown/tab1.md) 클래스<br>
[`tab2socketclient`](../docs/Markdown/tab2.md) 클래스<br>
[`tab3controlpannel`](../docs/Markdown/tab3.md) 클래스 <br>
[`tab4linechart`](../docs/Markdown/tab4.md) 클래스 <br>
[`tab5sensordatabase`](../docs/Markdown/tab5.md) 클래스 <br>
[`tab6webcamera`](../docs/Markdown/tab6.md) 클래스 <br>
[`tab7camviewerthread`](../docs/Markdown/tab7.md) 클래스 <br>