# 3. 주소체계와 데이터 정렬

## 목차
1. [소켓에 할당되는 IP주소와 PORT번호](#1-소켓에-할당되는-ip주소와-port번호)
2. [주소정보의 표현](#2-주소정보의-표현)
3. [네트워크 바이트 순서와 인터넷 주소 변환](#3-네트워크-바이트-순서와-인터넷-주소-변환)
4. [인터넷 주소의 초기화와 할당](#4-인터넷-주소의-초기화와-할당)

## 1. 소켓에 할당되는 IP주소와 PORT번호

### ⦁ 소켓의 구분에 활용되는 PORT번호

#### - PORT 번호
- IP는 컴퓨터를 구분하는 용도로 사용되며, PORT번호는 소켓을 구분하는 용도로 사용된다.
- 하나의 프로그램 내에서는 둘 이상의 소켓이 존해할 수 있으므로, 둘 이상의 PORT가 하나의 프로그램에 의해 할당될 수 있다.
- PORT번호로 16비트로 표현, 따라서 그 값은 0 이상 65535 이하
- 0~1023은 잘 알려진 PORT(Well-known PORT)라 해서 이미 용도가 결정되어 있다.

## 2. 주소정보의 표현

### ⦁ IPv4 기반의 주소표현을 위한 구조체
```c
struct sockaddr_in
{
    sa_family_t sin_family; // 주소체계
    uint16_t sin_port; // PORT 번호
    struct in_addr; // 32비트 IP주소
    char sin_zero[8]; // 사용되지 않음
};
```
```c
struct in_addr
{
    in_addr_t s_addr; // 32비트 IPv4 인터넷 주소
};
```

| 자료형 이름 | 자료형에 담길 정보
|:---:|:---:
| int8_t | signed 8-bit int|
| uint8_t | unsigned 8-bit int (unsigned char)
| int16_t | signed 16-bit int
| uint16_t | unsigned 16-bit (unsigned short)
| int32_t | signed 32-bit int
| uint32_t | unsigned 32-bit int (unsigned long)
| sa_family_t | 주소체계(address famliy)
| socklen_t | 길이정보(length of struct)
| in_addr_t | IP주소정보, uint32_t 정의되어 있음
| in_port_t | PORT번호정보, uint16_t로 정의되어 있음

### ⦁ 구조체 sockaddr_in의 멤버에 대한 분석

#### - 멤버 sin_family
- 주소체계 정보 저장

#### - 멤버 sin_port
- 16비트 PORT번호 저장
- 네트워크 바이트 순서로 저장

#### - 멤버 sin_addr
- 32비트 IP주소정보 저장
- 네트워크 바이트 순서로 저장
- 멤버 sin_addr의 구조체 자료형 in_addr 사실상 32비트 정수 자료형

#### - 멤버 sin_zero
- 특별한 의미를 지니지 않는 멤버
- 반드시 0으로 채워야 한다.

| 주소체계(Address Family) | 의미
|:---:|:---:|
|AF_INET| IPv4 인터넷 프로토콜에 적용하는 주소체계
|AF_INET6|IPv6 인터넷 프로토콜에 적용하는 주소체계
|AF_LOCAL|로컬 통신을 위한 유닉스 프로토콜의 주소체계

### ⦁ 구조체 sockaddr_in의 활용의 예
```c
struct sockaddr_it serv_addr;

if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == 1)
    error_handling("bind() error");
// 구조체 변수 sockaddr_in은 bind 함수의 인자로 전달되는데, 매개변수 형이 sockaddr이므로 형 변환을 해야만 한다.
```
```c
struct sockaddr
{
    sa_family sin_family; // 주소체계(Address Family)
    char sa_data[14] // 주소정보
}
// 구조체 sockaddr은 다양한 주소체계의 주소정보를 담을 수 있도록 정의되었다. 그래서 IPv4의 주소정보를 담기가 불편하다. 이에 동일한 바이트 열을 구성하는 구조체 sockaddr_in이 정의되어 있으며, 이를 이용해서 쉽게 IPv4의 주소정보를 담을 수 있다.
```

## 3. 네트워크 바이트 순서와 인터넷 주소 변환

### ⦁ 바이트 순서(Order)와 네트워크 바이트 순서

#### - 빅 엔디안(Big Endian)
- 상위 바이트의 값을 작은 번지수에 저장

#### - 리틀 엔디안(Little Endian)
- 상위 바이트의 값을 큰 번지수에 저장

#### - 호스트 바이트 순서
- CPU별 데이터 저장방식을 의미함

#### - 네트워크 바이트 순서
- 통일된 데이터 송수신 기준을 의미함
- 빅 엔디안이 기준.

### ⦁ 바이트 순서의 변환

- **바이트 변환함수**
```c
unsigned short htons(unsigned short);
unsigned short ntohs(unsigned short);
unsigned long htonl(unsigned long);
unsigned long ntohl(unsigned long);
```
- htons에서 h는 호스트(host) 바이트 순서를 의미
- htons에서 n은 네트워크(network) 바이트 순서를 의미
- htons에서 s는 자료형 short를 의미
- htiol에서 l은 자료형 l을 의미

### ⦁ 바이트 변환의 예

- `endian_conv.c` 실행 결과
```bash
ubuntug@ubuntug:~/c_c++/Tcp:Ip/Ch3$ gcc endian_conv.c -o conv
ubuntug@ubuntug:~/c_c++/Tcp:Ip/Ch3$ ./conv 
Host ordered port: 0x1234 
Network ordered port: 0x3412 
Host ordered address: 0x12345678 
Network ordered address: 0x78563412 
ubuntug@ubuntug:~/c_c++/Tcp:Ip/Ch3$
```

## 4. 인터넷 주소의 초기화와 할당

### ⦁ 문자열 정보를 네트워크 바이트 순서의 정수로 변환

#### - inet_addr
"211.214.107.99"와 같이 점이 찍힌 10진수로 표현된 문자열을 전달하면, 해당 문자열 정보를 참조해서 IP주소정보를 32비트 정수형으로 반환!
```c
#include <arpa/inet.h>

in_addr_t inet_addr(const char * string);
// -> 성공 시 빅 엔디안으로 변환된 32비트 정수 값, 실패 시 INADDR_NONE 반환
```
- `inet_addr.c` 실행 결과
```bash
ubuntug@ubuntug:~/c_c++/Tcp:Ip/Ch3$ gcc inet_addr.c -o addr
ubuntug@ubuntug:~/c_c++/Tcp:Ip/Ch3$ ./addr 
Network ordered integer addr: 0x4e7cd47f 
Error occureded 
ubuntug@ubuntug:~/c_c++/Tcp:Ip/Ch3$
```

#### - inet_aton
기능상으로 inet_addr 함수와 동일하나 in_addr형 구조체 변수에 변환의 결과가 저장된다는 점에서 차이가 있다.
```c
#include <arpa/inet.h>

int inet_aton(const char * string, struct in_addr * addr);
// -> 성공 시 1(true), 실패 시 0(false) 반환
// string : 변환할 IP주소 정보를 담고 있는 문자열의 주소 값 전달.
// addr : 변환된 정보를 저장할 in_addr 구조체 변수의 주소 값 전달.
```
- `inet_aton.c` 실행 결과
```bash
ubuntug@ubuntug:~/c_c++/Tcp:Ip/Ch3$ gcc inet_aton.c -o aton
ubuntug@ubuntug:~/c_c++/Tcp:Ip/Ch3$ ./aton 
Network ordered integer addr: 0x4f7ce87f 
ubuntug@ubuntug:~/c_c++/Tcp:Ip/Ch3$ 
```

#### - inet_nota
inet_aton 함수의 반대기능 제공.
네트워크 바이트 순서로 정렬된 정수형 IP주소 정보를 우리가 눈으로 쉽게 인식할 수 있는 문자열의 형태로 변환.
```c
#include <arpa/inet.h>

char * inet_ntoa(struct in_addr adr);
// -> 성공 시 변환된 문자열의 주소 값, 실패 시 -1 반환
```
- `inet_ntoa.c` 실행 결과
```bash
ubuntug@ubuntug:~/c_c++/Tcp:Ip/Ch3$ gcc inet_ntoa.c -o ntoa
ubuntug@ubuntug:~/c_c++/Tcp:Ip/Ch3$ ./ntoa 
Dotted-Decimal notation1: 1.2.3.4 
Dotted-Decimal notation2: 1.1.1.1 
Dotted-Decimal notation3: 1.2.3.4 
ubuntug@ubuntug:~/c_c++/Tcp:Ip/Ch3$ 
```

### ⦁ 인터넷 주소의 초기화

- 일반적인 인터넷 주소의 초기화 과정
```c
struct sockaddr_in addr;
char *serv_ip = "211.217.168.13"; // IP주소 문자열 선언
char *serv_port = "9190" // PORT번호 문자열 선언
memset(&addr, 0, sizeof(addr)); // 구조체 변수 addr의 모든 멤버 0으로 초기화
addr.sin_family=AF_INET; // 주소체계 지정
addr.sin_addr.s_addr=inet_addr(serv_ip); // 문자열 기반의 IP주소 초기화
addr.sin_port=htons(atoi(serv_port)); // 문자열 기반의 PORT번호 초기화
```

### ⦁ INADDR_ANY
현재 실행중인 컴퓨터의 IP소켓에 부여할 때 사용되는 것이 INADDR_ANY이다.
이는 서버 프로그램의 구현에 주로 사용된다.
```c
struct sockaddr_in addr;
char *serv_port = "9190";
memset(&addr, 0, sizeof(addr));
addr.sin_family=AF_INET;
addr.sin_addr.s_addr=htonl(INADDR_ANY);
addr.sin_port=htons(atoi(serv_port));
```

### ⦁ Ch1의 예제 실행방식의 고찰

- [./hello_server 5000](../Ch1/README.md#--예제의-실행결과)
서버의 실행방식, 서버의 리스닝 소켓 주소는 INADDR_ANY로 지정을 하니, 소켓의 PORT번호만 인자를 통해 전달하면 된다.

- [./hello_client 127.0.0.1 5000](../Ch1/README.md#--예제의-실행결과)
클라이언트의 실행방식, 연결할 서버의 IP와 PORT번호를 인자로 전달한다.
127.0.0.1은 루프백 주소라 하며, 이는 클라이언트를 실행하는 컴퓨터의 IP주소를 의미한다.
루프백 주소를 전달한 이유는, 서버와 클라이언트를 한 대의 컴퓨터에서 실행시켰기 때문이다.

### ⦁ 소켓에 인터넷 주소 할당하기
```c
#include <sys/socket.h>

int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);
// -> 성공 시 0, 실패 시 -1 반환
// sockfd 주소정보를(IP와 PORT를) 할당한 소켓의 디스크립터.
// myaddr 할당하고자 하는 주소정보를 지니는 구조체 변수의 주소 값.
// addrlen 두 번째 인자로 전달된 구조체 변수의 길이정보.
```

- 서버프로그램에서의 일반적인 주소할당의 과정
```c
int serv_sock;
struct sockaddr_in serv_addr;
char *serv_port="5000"

/* 서버 소켓(리스닝 소켓) 생성 */
serv_sock = socket(PF_INET, SOCK_STREAM, 0);

/* 주소정보 초기화 */
memset(&serv_addr, 0, sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
serv_addr.sin_port = htons(atoi(serv_port));

/* 주소정보 할당 */
bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
```