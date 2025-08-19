#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFSIZE 100
int sock;
int put_check = 0;

void * keyboard_thread(void *arg);
void * socket_thread(void *arg);
void error_handling(char *message);

int main(int argc, char* argv[])
{
	struct sockaddr_in serv_addr;
	int stdin_fd=fileno(stdin);
	pthread_t thread_send, thread_receive;

	printf("stdin_fd : %d\n",stdin_fd);
	if(argc!=3){
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	sock=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock < 0)
		error_handling("socket() error");
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) 
		error_handling("connect() error!");

/* 
//  -------------------- keyboard_thread() ------------------------
	fputs("문자열을 입력하세요(quit:종료) : ",stdout);
	fgets(message, sizeof(message), stdin );
	str_len = strlen(message)-1;
	message[str_len] = '\0';	//'\n'제거
	if(!strcmp(message, "quit"))
		break;
	str_len=write(sock,message,str_len) ;    //입력 문자열을 서버로 전송
	if(str_len <= 0)
		error_handling("write() error");
	//  --------------------------------------------------------------
	//  --------------------- socket_thread() ------------------------
	str_len=read(sock, message, sizeof(message)-1);
	if(str_len > 0)
	{
		message[str_len] = '\0';
		printf("Message from server: %s \n", message);  
	}
	else if(str_len == 0) //서버 소켓 종료시
		break;
	else 
		error_handling("read() error!");
	//  ------------------------------------------------------
*/
	
	pthread_create(&thread_send, NULL, keyboard_thread, NULL);
	pthread_create(&thread_receive, NULL, socket_thread, NULL);

	pthread_join(thread_send, NULL);
	pthread_join(thread_receive, NULL);

	close(sock);
	return 0;
}

void * keyboard_thread(void *arg)
{
	char message[BUFFSIZE];
	int str_len;
	fputs("문자열을 입력하세요 (quit:종료) : ", stdout);
	fflush(stdout); // 버퍼 비우기

	while(1)
	{
		fgets(message, sizeof(message), stdin);
		str_len = strlen(message)-1;
		message[str_len] = '\0';	//'\n'제거
		if(!strcmp(message, "quit"))
			exit(1);
		str_len = write(sock,message,str_len) ;    //입력 문자열을 서버로 전송
		if (str_len <= 0)
			error_handling("write() error");
	}
	return NULL;
}
void * socket_thread(void *arg)
{
	char message[BUFFSIZE];
	int str_len;

	while(1)
	{
		str_len = read(sock, message, sizeof(message)-1);
		if(str_len > 0)
		{
			message[str_len] = '\0';
			printf("Message from server: %s \n\n", message); 
			fputs("문자열을 입력하세요 (quit:종료) : ", stdout);
			fflush(stdout);
		}
		else if(str_len == 0) //서버 소켓 종료시
		{
			fputs("server exit\n", stderr);
			exit(1);
		}
		else 
			error_handling("read() error!");
	}

	return NULL;
}

void error_handling(char *message)
{
//	perror("error_handling()");
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}


