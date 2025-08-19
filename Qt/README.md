# Qt
Windows, Ubuntu, Raspberry Pi OS 환경에서 실습 및 테스트 하였습니다.

[Qt 공식문서](https://doc.qt.io/qt-6.8/index.html)
+ Qt 6.8 버전의 기능/클래스 설명
+ 개발자 가이드 / 튜토리얼
+ 모듈별 설명

## Qt 클래스 상속 관계 정리

> Qt는 대부분의 클래스가 `QObject`을 기반으로 하며, 위젯 계열은 `QWidget` 계열로 구성됩니다.

---

### ✅ 기본 클래스 계층 구조

```plaintext
QObject
 ├── QCoreApplication
 │    └── QApplication
 ├── QTimer
 ├── QThread
 ├── QWidget
 │    ├── QMainWindow
 │    ├── QDialog
 │    ├── QFrame
 │    │    ├── QLabel
 │    │    ├── QLineEdit
 │    │    ├── QGroupBox
 │    ├── QPushButton
 │    ├── QCheckBox
 │    ├── QRadioButton
 │    ├── QComboBox
 │    ├── QTableWidget
 │    ├── QOpenGLWidget
 │    └── ...
 └── QAbstractItemModel
      ├── QStringListModel
      ├── QStandardItemModel
      └── ...
```

---

### ✅ 주요 클래스 설명

### 🔹 `QObject`
- 모든 Qt 클래스의 최상위 부모
- 시그널/슬롯 시스템 지원
- 메모리 관리(parent/child 관계)

### 🔹 `QWidget`
- 모든 GUI 위젯의 기반 클래스
- 창, 버튼, 텍스트박스 등 시각적 컴포넌트 제공

### 🔹 `QApplication`
- 이벤트 루프와 GUI 환경 초기화 담당
- `main()` 함수에서 사용

### 🔹 `QMainWindow`
- 메뉴, 툴바, 상태바를 포함한 표준 창 제공

### 🔹 위젯들 (`QPushButton`, `QLabel`, `QLineEdit` 등)
- `QWidget`을 상속하여 사용자와의 인터페이스 역할

---

### ✅ 시각적 요약 (UML 스타일)

```plaintext
QObject
├── QCoreApplication
│   └── QApplication
│       └── QWidget
│           ├── QMainWindow
│           ├── QDialog
│           ├── QPushButton
│           ├── QLineEdit
│           ├── QLabel
│           ├── QCheckBox
│           ├── QRadioButton
│           └── ...
├── QTimer
├── QThread
└── QAbstractItemModel
```

---

### ✅ 상속 경로 예시

| 기능            | 상속 구조                                    |
|-----------------|-----------------------------------------------|
| 메인 GUI 창     | `QObject` → `QWidget` → `QMainWindow`         |
| 버튼            | `QObject` → `QWidget` → `QPushButton`         |
| 입력창          | `QObject` → `QWidget` → `QLineEdit`           |
| 쓰레드 처리     | `QObject` → `QThread`                         |
| 타이머          | `QObject` → `QTimer`                          |
| 모델 클래스     | `QObject` → `QAbstractItemModel` → 하위 모델 |


## Qt 프로젝트 파일(.pro)이란?

`.pro` 파일은 Qt 프로젝트의 설정 파일입니다. `qmake` 빌드 시스템이 이 파일을 사용하여 프로젝트를 어떻게 빌드할지 결정합니다.

파일 안에는 다음과 같은 정보가 포함됩니다:
- **SOURCES**: 컴파일할 소스 코드 파일 목록
- **HEADERS**: 헤더 파일 목록
- **QT**: 프로젝트에서 사용할 Qt 모듈 (예: `core`, `gui`, `widgets`)
- **TARGET**: 생성될 실행 파일의 이름
- 기타 빌드 관련 설정 (예: 라이브러리 추가, 컴파일러 옵션)

`qmake`는 `.pro` 파일을 읽어 플랫폼에 맞는 `Makefile`을 생성하고, 이 `Makefile`을 통해 프로젝트가 컴파일됩니다.

### Qt 프로젝트(.pro) 생성 및 실행파일 만드는 방법(직접 만들 경우)

#### ✅ 기본으로 만들기

```bash
- qmake -project
- vi raspi.pro
```
.pro 파일이 자동 생성됨.
raspi.pro 파일 5번째 줄쯤에 아래 항목을 추가 또는 수정:
```bash
QT += widgets
``
```bash
qmake      # Makefile 생성
make       # 컴파일
./raspi    # 실행파일 실행 (기본 TARGET 이름 기준)
```

#### ✅ .pro 파일과 실행파일 이름 바꾸기
```bash
qmake -project -o helloqt.pro
vi helloqt.pro
```
- helloqt.pro 파일에 아래 내용을 추가 또는 수정:
```bash
QT += widgets
TARGET = helloqt
```
```bash
qmake      # Makefile 생성
make       # 컴파일
./helloqt  # 실행
```
---