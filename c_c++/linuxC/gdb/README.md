# GDB와 코어 덤프(Core Dump)를 이용한 디버깅 가이드

## 1. 코어 덤프(Core Dump)란?

코어 덤프는 프로그램이 세그멘테이션 폴트(Segmentation Fault)와 같은 심각한 오류로 인해 비정상적으로 종료될 때, **오류 발생 순간의 프로그램 상태를 기록한 파일**입니다. 비행기 사고의 원인을 분석하기 위한 '블랙박스'와 유사한 역할을 합니다.

### 주요 특징

- **생성 시점**: 프로그램이 운영체제에 의해 강제 종료될 때 생성됩니다.
- **포함된 정보**:
    - 오류 발생 시점의 메모리 상태 (변수 값 등)
    - CPU 레지스터 값
    - 호출 스택 (Call Stack): 오류 지점까지 어떤 함수들이 순서대로 호출되었는지에 대한 정보
- **파일 이름 형식**: 보통 `core.프로그램이름.프로세스ID` 와 같은 형식으로 생성됩니다. (예: `core.like.5807`)
- **목적**: 이미 종료된 프로그램의 오류 원인을 분석하는 **사후 디버깅(Post-mortem Debugging)**을 위해 사용됩니다.

---

### 1.1 코어 덤프 활성화 및 확인 방법

리눅스 환경에서 코어 덤프를 수집하려면 시스템과 셸 설정이 올바르게 되어 있어야 합니다.

#### ▶ ulimit 설정 (현재 셸에서 활성화)

```bash
ulimit -c unlimited       # 코어 덤프 크기 제한 제거
ulimit -c                 # 설정 확인 (출력: unlimited)
```

#### ▶ core 파일 저장 위치 및 형식 확인

```bash
cat /proc/sys/kernel/core_pattern
```

**출력 예시:**
```
|/usr/share/apport/apport %p %s %c %P
```

이 경우, Ubuntu에서 Apport라는 시스템이 core 파일 저장을 가로채므로 실제로 파일이 생성되지 않을 수 있습니다.

#### ▶ core 파일 직접 저장되게 설정

1. **Apport 비활성화:**
```bash
sudo systemctl disable apport
sudo systemctl stop apport
```

또는 `/etc/default/apport` 파일에서:

```bash
enabled=0
```

2. **core 파일명 형식 변경:**
```bash
echo "core" | sudo tee /proc/sys/kernel/core_pattern
```

또는 특정 폴더에 저장:
```bash
sudo mkdir -p /tmp/corefiles
sudo chmod 777 /tmp/corefiles
echo "/tmp/corefiles/core.%e.%p" | sudo tee /proc/sys/kernel/core_pattern
```

3. **프로그램에서 세그멘테이션 오류 발생 시 core 파일 확인:**
```bash
ls -l core*                # 현재 디렉토리에 생성된 core 파일
ls -l /tmp/corefiles       # 설정한 위치에 core 파일 있는지 확인
```

---

## 2. GDB (GNU Debugger) 기본 사용법

GDB는 리눅스/유닉스 환경에서 가장 널리 사용되는 강력한 커맨드 라인 디버거입니다.

### 컴파일 옵션

GDB를 효과적으로 사용하려면, 컴파일할 때 `-g` 옵션을 추가해야 소스 코드 수준의 디버깅이 가능합니다.

```bash
gcc -g -o bugprg bugprg.c
```

### GDB 시작하기

#### 가. 실행 중인 프로그램 디버깅

```bash
gdb ./프로그램이름
```

#### 나. 코어 덤프 파일 분석 (사후 디버깅)

```bash
gdb ./프로그램이름 코어덤프파일
# 예시
gdb ./like core.like.5807
```


---

### 2.1 코어 파일 분석 명령어 예시

코어 덤프 파일이 생성되었고, 원래 프로그램 실행 파일(`like`)이 존재할 경우 아래와 같이 GDB를 실행할 수 있습니다:

```bash
gdb ./like core
```

GDB가 실행되면 다음과 같은 명령어를 사용할 수 있습니다:

```gdb
(gdb) bt         # backtrace: 함수 호출 스택 확인
(gdb) list       # 오류가 난 지점의 소스 코드 보기
(gdb) print 변수명   # 특정 변수의 값 출력
```

예시 출력:
```
Program terminated with signal SIGSEGV, Segmentation fault.
#0  0x000000000040114e in main () at like.c:10
10          *ptr = 42;
```

이처럼 `bt` 명령어를 통해 오류가 발생한 함수 호출 흐름을 확인하고, `list`, `print` 등을 활용해 원인을 상세히 분석할 수 있습니다.


### 주요 GDB 명령어

| 명령어 (축약형) | 설명 |
|---|---|
| `run` (r) | 프로그램을 실행합니다. |
| `break` (b) | 중단점(Breakpoint)을 설정합니다. (예: `b 10`, `b main`) |
| `continue` (c) | 다음 중단점까지 프로그램을 계속 실행합니다. |
| `next` (n) | 현재 줄의 코드를 실행하고 다음 줄로 넘어갑니다. (함수 안으로 들어가지 않음) |
| `step` (s) | 현재 줄의 코드를 실행하고 다음 줄로 넘어갑니다. (함수 안으로 들어감) |
| `print` (p) | 변수의 현재 값을 출력합니다. (예: `p 변수명`) |
| `list` (l) | 소스 코드를 보여줍니다. |
| `backtrace` (bt) | 현재까지의 함수 호출 스택을 보여줍니다. (오류 발생 시 원인 파악에 매우 유용) |
| `info breakpoints` | 설정된 중단점 목록을 보여줍니다. |
| `quit` (q) | GDB를 종료합니다. |

---

### 디버깅 시나리오 예시

1.  **GDB 시작**: `gdb ./bugprg`
2.  **중단점 설정**: `break main` (main 함수 시작 지점에 중단점 설정)
3.  **프로그램 실행**: `run`
4.  **한 줄씩 실행**: `next` 또는 `step` 명령어로 코드 진행
5.  **변수 값 확인**: `print my_variable`
6.  **문제 분석**: 특정 구간에서 `next`로 진행하며 변수 값들을 `print`로 확인하여 예상과 다른 동작을 하는 부분을 찾습니다.
7.  **코어 덤프 분석**: `gdb ./like core.like.5807` 실행 후, `backtrace` 명령어를 입력하면 어떤 함수 호출 과정에서 오류가 발생했는지 즉시 확인할 수 있습니다.