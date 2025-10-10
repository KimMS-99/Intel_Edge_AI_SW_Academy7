# 1. 네트워크 프로그래밍과 소켓의 이해

## 목차

1. [네트워크 프로그래밍과 소켓의 이해](#1-네트워크-프로그래밍과-소켓의-이해)
2. [리눅스 기반 파일 조작하기](#2-리눅스-기반-파일-조작하기)

---

## 1. 네트워크 프로그래밍과 소켓의 이해

### ⦁ 네트워크 프로그래밍과 소켓에 대한 이해

#### - 네트워크 프로그래밍이란?
+ 소켓이라는 것을 기반으로 프로그래밍을 하기 때문에 소켓 프로그래밍이 라고도 함.
+ 네트워크로 연결된 둘 이상의 컴퓨터 사이에서의 데이터 송수신 프로그램의 작성을 의미함.

#### - 소켓에 대한 간단한 이해
+ 네트워크(인터넷)의 연결 도구
+ 운영체제에 의해 제공이 되는 소프트웨어적인 장치
+ 소켓은 프로그래머에게 데이터 송수신에 대한 물리적, 소프트웨어적 세세한 내용을 신경 쓰지 않게 한다.

### ⦁ 전화 받는 소켓의 생성

#### - 소켓의 비유와 분류
+ TCP 소켓은 전화기에 비유될 수 있다.
+ 소켓은 socket 함수의 호출을 통해서 생성한다.
+ 단, 전화를 거는 용도의 소켓과 전화를 수신하는 용도의 소켓 생성 방법에는 차이가 있다.
```c
/* 소켓의 생성 */
#include <sys/socket.h>
int socket(int domain, int type, int protocol);
// -> 성공 시 파일 디스크립터, 실패 시 -1 반환
```

### ⦁ 전화번호의 부여

#### - 소켓의 주소 할당 및 연결
+ 전화기에 전화번호가 부여되듯이 소켓에도 주소정보가 할당된다.
+ 소켓의 주소정보는 IP와 PORT번호로 구성이 된다.
```c
/* 주소의 할당 */
#include <sys/socket.h>
int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);
// -> 성공 시 0, 실패 시 -1 반환
```

### ⦁ 전화기의 연결

#### - 연결요칭이 가능한 상태의 소켓
+ 연결요청이 가능한 상태의 소켓은 걸려오는 전화를 받을 수 있는 상태에 비유할 수 있다.
+ 전화를 거는 용도의 소켓은 연결요청이 가능한 상태의 소켓이 될 필요가 없다. 이는 걸려오는 전화를 받는 용도의 소켓에서 필요한 상태이다.
```c
/* 연결요청이 가능한 상태로 변경 */
#include <sys/socket.h>
int listen(int sockfd, int backlog);
// -> 성공 시 0, 실패 시 -1 반환
// 소켓에 할당된 IP와 PORT번호로 연결요청이 가능한 상태가 된다.
```

### ⦁ 수화기를 드는 상황

#### - 연결요청의 수락
+ 걸려오는 전화에 대한 수락의 의미로 수화기를 드는 것에 비유 가능.
+ 연결요청이 수락되어야 데이터의 송수신이 가능.
+ 수락된 이후에 데이터의 송수신은 양방향으로 가능.
```c
/* 연결요청 가능한 상태로 변경 */
#include <sys/socket.h>
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
// -> 성공 시 파일 디스크립터, 실패 시 -1 반환
// accept 함수호출 이후에는 데이터의 송수신이 가능함. 단, 연결요청이 있을 때에만 accept 함수가 반환을 한다.
```

### ⦁ 정리하기!

#### - 연결요청을 허용하는 소켓의 생성과정
+ 1단계. 소켓의 생성 socket 함수호출
+ 2단계. IP와 PORT번호의 할당 bind 함수호출
+ 3단계. 연결요청 가능한 상태로 변경 listen 함수호출
+ 4단계. 연결요청에 대한 수락 accept 함수호출

### ⦁ 전화 거는 소켓의 구현

#### - 연결을 요청하는 소켓의 구현
+ 전화를 거는 상황에 비유 가능.
+ 리스닝 소켓과 달리 구현의 과정이 매우 간단함.
+ '소켓의 생성'과 '연결의 요청'으로 구분됨.
```c
/* 연결의 요청 */
#include <sys/socket.h>
int connect(int sockfd, struct sockaddr *serv_addr, socklen_t addrlen);
// 성공 시 0, 실패 시 -1 반환
```

### ⦁ 리눅스 기반에서의 실행결과

#### - 예제의 실행결과

+ `hello_server.c` 실행 결과
```bash
ubuntug@ubuntug:~/c_c++/Tcp:Ip/Ch1$ gcc hello_server.c -o hello_server
ubuntug@ubuntug:~/c_c++/Tcp:Ip/Ch1$ ./hello_server 5000
```

+ `hello_client.c` 실행 결과
```bash
ubuntug@ubuntug:~/c_cpp/tcpip/Ch1$ gcc hello_client.c -o hello_client
ubuntug@ubuntug:~/c_cpp/tcpip/Ch1$ ./hello_client 127.0.0.1 5000
Message from server: Hello World! 
```

## 2. 리눅스 기반 파일 조작하기

### ⦁ 저 수준 파일 입출력과 파일 디스크립터

#### - 저 수준 파일 입출력
+ ANSI의 표준함수가 아닌, 운영체제가 제공하는 함수 기반의 파일 입출력.
+ 표준이 아니기 때문에 운영체제에 대한 호환성이 없음.
+ 리눅스는 소켓도 파일로 간주하기 때문에 저 수준 파일 입출력 함수를 기반으로 서켓 기반의 데이터 송수신이 가능.

#### - 파일 디스크립터
+ 운영체제가 만든 파일(그리고 소켓)을 구분하기 위한 일종의 숫자
+ 저 수준 파일 입출력 함수는 입출력을 목적으로 파일 디스크립터를 요구함.
+ 저 수준 파일 입출력 함수에게 소켓의 파일 디스크립터를 전달하면, 소켓을 대상으로 입출력을 진행.

| 파일 디스크립터 | 대상 | 
|:---:|:---:|
| 0 | 표준입력 : Standard Input |
| 1 | 표준출력 : Standard Output |
| 2 | 표준에러 : Standard Error |

### ⦁ 파일 열기와 닫기

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open (const char *path, int flag);
// -> 성공 시 파일 디스크립터, 실패 시 -1 반환
// path : 파일 이름을 나타내는 문자열 주소 값 전달
// flag : 파일의 오픈 모드 정보 전달
// open 함수 호출 시 반환된 파일 디스크립터를 이용해서 파일 입출력을 진햄함.
```
```c
#include <unistd.h>

int close(int fd);
// 성공 시 0, 실패 시 -1 반환
// fd : 닫고자 하는 파일 소켓의 파일 디스크립터 전달.
```

| 오픈모드 | 의미|
|:---:|:---:|
| O_CREAT | 필요하면 파일을 생성|
| O_TRUNC | 기존 데이터 전부 삭제|
| O_APPEND | 기존 데이터 보존하고, 뒤에 이어서 저장|
| O_REONLY | 읽기 전용으로 파일 오픈 |
| O_WRONLY | 쓰기 전용으로 파일 오픈 | 
| O_RDWR | 읽기, 쓰기 겸용으로 파일 오픈 |

### ⦁ 파일에 데이터 쓰기

```c
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t nbytes);
// -> 성공 시 전달한 바이트 수, 실패 시 -1 반환
// fd : 데이터 전송대상을 나타내는 파일 디스크립터 전달.
// buf : 전송할 데이터가 저장된 버퍼의 주소 값 전달.
// nbytes : 전송할 데이터의 바이트 수 전달.
```
+ ***low_open.c*** 실행 결과
```bash
ubuntug@ubuntug:~/c_c++/Tcp:Ip/Ch1$ gcc low_open.c -o loepn
ubuntug@ubuntug:~/c_c++/Tcp:Ip/Ch1$ ./lopen 
file descriptor: 3 
ubuntug@ubuntug:~/c_c++/Tcp:Ip/Ch1$ cat data.txt 
Let's go!
ubuntug@ubuntug:~/c_c++/Tcp:Ip/Ch1$
```

### ⦁ 파일에 저장된 데이터 읽기

```c
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t nbytes);
// -> 성공 시 전달한 바이트 수, 실패 시 -1 반환
// fd : 데이터 전송대상을 나타내는 파일 디스크립터 전달
// buf : 전송할 데이터가 저장된 버퍼의 주소 값 전달.
// nbytes : 전송할 데이터의 바이트 수 전달.
```

+ `low_read.c` 실행 결과
```c
ubuntug@ubuntug:~/c_c++/Tcp:Ip/Ch1$ gcc low_read.c -o lread
ubuntug@ubuntug:~/c_c++/Tcp:Ip/Ch1$ ./lread 
file descriptor: 3 
file data: Let's go!
ubuntug@ubuntug:~/c_c++/Tcp:Ip/Ch1$
```

### ⦁ 파일 디스크립터와 소켓

+ `fd_seri.c` 실행 결과
```c
ubuntug@ubuntug:~/c_c++/Tcp:Ip/Ch1$ gcc fd_seri.c -o fds
ubuntug@ubuntug:~/c_c++/Tcp:Ip/Ch1$ ./fds 
file descriptor 1: 3
file descriptor 2: 4
file descriptor 3: 5
ubuntug@ubuntug:~/c_c++/Tcp:Ip/Ch1$
```
실행결과를 통해서 소켓과 파일을 일련의 파일 디스크립터 정수 값이 할당됨을 알 수 있다. 그리고 이를 통해서 리눅스는 파일과 소켓을 동일하게 간주함을 확인할 수 있다.

### ⦁ 그 외

윈도우 소켓은 다르므로 참고.