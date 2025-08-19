# 4. TCP 기반 서버 / 클라이언트 1

## 목차
1. [TCP와 UDP에 대한 이해](#1-tcp와-udp에-대한-이해)
2. [TCP기반 서버, 클라이언트의 구현](#2-tcp기반-서버-클라이언트의-구현)
3. [Iterative 기반의 서버, 클라이언트의 구현](#3-iterative-기반의-서버-클라이언트의-구현)

## 1. TCP와 UDP에 대한 이해

### ⦁ TCP / IP 프토로콜 스택이란?
- 인터넷 기반의 데이터 송수신을 목적으로 설계된 스택
- 큰 문제를 작게 나눠서 계층화 한 결과
- 데이터 송수신의 과정을 네 개의 영역으로 계층화 한 결과
- 각 스택 별 영역을 전문화하고 표준화 함.
- 7계층으로 세분화 되며, 4계층으로도 표현함.

### ⦁ LINK & IP계층

#### - LINK 계층의 기능 및 역할
- 물리적인 영역의 표준화 결과
- LAN, WAN, MAN과 같은 물리적인 네트워크 표준 관련 프로토콜이 정의된 영역

#### - IP 계층의 기능 및 역할
- IP는 Internet protocol을 의미함
- 경로의 설정과 관련이 있는 프로토콜

### ⦁ TCP/UDP 계층

#### - TCP/UDP 계층의 기능 및 역할
- 실제 데이터의 송수신과 관련 있는 계층
- 그래서 전송(Transport) 계층이라고도 함
- TCP는 데이터의 전송을 보장하는 프로토콜(신뢰성 있는 프로토콜), UDP는 보장하지 않는 프로토콜
- TCP는 신뢰성을 보장하기 때문에 UDP에 비해 복잡한 프로토콜이다.

### ⦁ APPLICATION 계층

#### - 프로그래머에 의해서 완성되는 APPLICATION계층
- 응용프로그램의 프로토콜을 구성하는 계층
- 소켓을 기반으로 완성하는 프로토콜을 의미함
- 소켓을 생성하면, 앞서 보인 LINK, IP, TCP/UDP 계층에 대한 내용은 감춰진다.
- 그러니 응용 프로그래머는 APPLICATION 계층의 완성에 집중하게 된다.

## 2. TCP기반 서버, 클라이언트의 구현

### ⦁ TCP 서버의 기본적인 함수 호출 순서

`socket()` 소켓 생성 -> `bind()` 소켓 주소할당 -> <br>
`listen()`연결요청 대기상태 -> `accept()`연결허용 -> <br>
`read()/wrtie()`데이터 송수신 -> `close()`연결 종료

bind 함수까지 호출이 되면 주소가 할당된 소켓을 얻게 된다.
따라서 listen 함수의 호출을 통해서 연결요청이 가능한 상태가 되어야 한다.

### ⦁ 연결요청이 대기 상태로의 진입
```c
#include <sys/type.h>

int listen(int sock, int backlog);
// -> 성공 시 0, 실패 시 -1 반환
// sock : 연결요청 대기상태에 두고자 하는 소켓의 파일 디스크립터 전달, 이 함수의 인자로 전달된 디스크립터의 소켓이 서버 소켓(리스닝 소켓)이 된다.
// backlog : 연결요청 대기 큐(Quque)의 크기정보 전달, 5가 전달되면 큐의 크기가 5가 되어 클라이언트의 연결요청을 5개까지 대기시킬 수 있다.
```
연결요청도 일종의 데이터 전송이다. 따라서 연결요청을 받아들이기 위해서는 하나의 소켓이 필요하다. 그리고 이 소켓을 가리켜 서버소켓 또는 리스닝 소켓이라고 한다. listen 함수의 호출은 소켓을 리스닝 소켓이 되게한다.

### ⦁ 클라이언트의 연결요청 수락
```c
#include <sys/socket.h>

int accept(int sock, struct sockaddr * addr, socklen_t * addrlen);
// -> 성공 시 생성된 소켓의 파일 디스크립터, 실패 시 -1 반환
// sock : 서버 소켓의 파일 디스크립터 전달.
// addr : 연결요청 한 클리이언트의 주소정보를 담을 변수의 주소 값 전달, 함수호출이 완료되면 인자로 전달된 주소의 변수에는 클라이언트의 주소정보가 채워진다.
// addrlen : 두 번째 매개변수 addr에 전달된 주소의 변수 
```

### ⦁ TCP 클라이언트의 기본적인 함수호출 순서
```c
#include <sys/socket.h>

int connect(int sock, const struct sockaddr * servaddr, socklen_t adddrlen);
// -> 성공 시 생성된 소켓의 파일 디스크럽터, 실패 시 -1 반환
// sock : 클라이언트 소켓의 파일 디스크립터 전달.
// servaddr : 연결요청 한 클라이언트의 주소정보를 담을 변수의 주소 값 전달, 함수호출이 완료되면 인자로 전달된 주소의 번수에는 클라이언트의 주소정보가 채워진다.
// addrlen : 두 번째 매개변수 servaddr에 전달된 주소의 변수 크기를 바이트 단위로 전달, 단, 크기정보를 변수에 저장한 다음에 변수의 주소 값을 전달한다. 그리고 함수호출이 완료되면 크기정보로 채워져 있던 변수에는 클라이언트의 주소정보 길이가 바이트 단위로 채워진다.
```

`socket()`소켓생성 -> `connect()`연결요청 ->
`read()/write()`데이터 송수신 -> `close()`연결종료

클라이언트의 경우 소켓을 생성하고, 이 소켓을 대상으로 연결의 요청을 위해서 connect 함수를 호출하는 거싱 전부이다. 그리고 connect 함수를 호출할 때 연결할 서버의 주소정보도 전달한다.

### ⦁ TCP 기반 서버, 클라이언트의 함수호출 관계  

확인할 사항은, 서버의 listen 함수호출 이후에야 클라이언트의 connect 함수호출이 유효하다는 점이다. 더불어 그 이유까지도 설명할 수 있어야 한다.

## 3. Iterative 기반의 서버, 클라이언트의 구현

### ⦁ Iterative 서버의 구현

반복적으로 accept 함수를 호출하면, 계속해서 클라이언트의 연결요청을 수락할 수 있다. 그러나, 동시에 둘 이상의 클라이언트에게 서비스를 제공할 수 있는 모델은 아니다.
즉, 한 클라이언트를 처리하는 동안 다른 클라이언트의 요청은 기다려야 한다.

### ⦁ Iterative 서버와 클라이언트의 일부

- `echo_server.c`코드의 일부
```c
for(i=0; i<5; i++)
{
	clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
	if(clnt_sock==-1)
		error_handling("accept() error");
	else
		printf("Connected client %d \n", i+1);
	
	while((str_len=read(clnt_sock, message, BUF_SIZE))!=0)
		write(clnt_sock, message, str_len);

	close(clnt_sock);
}
```
- `echo_client.c`코드의 일부
```c
while(1) 
{
	fputs("Input message(Q to quit): ", stdout);
	fgets(message, BUF_SIZE, stdin);
		
	if(!strcmp(message,"q\n") || !strcmp(message,"Q\n"))
		break;

	write(sock, message, strlen(message));
	str_len=read(sock, message, BUF_SIZE-1);
	message[str_len]=0;
	printf("Message from server: %s", message);
}
```

### ⦁ 에코 클라이언트의 문제점

- 제대로 동작은 하나 문제의 발생 소지가 있는 TCP `echo_client.c`의 코드
```c
write(sock, message, strlen(message));
str_len=read(sock, message, BUF_SIZE-1);
message[str_len]=0;
printf("Message from server: %s", message);
```

TCP의 데이터 송수신에는 경계가 존재하지 않는다. 그런데 위의 코드는 다음 사항알 가정하고 있다.
"한 번의 read 함수호출로 앞서 전송된 문자열 전체를 읽어 들일 수 있다."
그러나 이는 잘못된 가정으로, TCP에는 데이터의 경계가 존재하지 않기 때문에 서버가 전송한 문자열의 일부만 읽혀질 수도 있다.