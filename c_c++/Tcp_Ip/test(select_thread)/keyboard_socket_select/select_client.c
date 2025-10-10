#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUFFSIZE 100
void error_handling(char *message);
int main(int argc, char* argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[BUFFSIZE];
	int str_len;
	int stdin_fd=fileno(stdin);
	int put_check = 0; // 출력 조건 분기체크
	fd_set reads;
	struct timeval timeout;

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

	do {
		FD_ZERO(&reads);
		FD_SET(stdin_fd, &reads); // 표준 입력
		FD_SET(sock, &reads); // 소켓
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;

		if(put_check == 0) // 출력 분기 체크
		{
			fputs("문자열을 입력하세요 (quit:종료) : ", stdout);
			fflush(stdout);
			put_check = 1;
		}

		int result = select(sock + 1, &reads, NULL, NULL, &timeout);
		if(result == -1)
            error_handling("select() error");
		else if(result == 0)
		{
			fputs("Time Out\n\n", stderr);
			put_check = 0;
		}
		else if(FD_ISSET(stdin_fd, &reads))
		{
			fgets(message, sizeof(message), stdin);
			str_len = strlen(message)-1;
			message[str_len] = '\0';	//'\n'제거
			if(!strcmp(message, "quit"))
				break;
			str_len=write(sock,message,str_len) ;	//키보드 입력 문자열을 서버로 전송
			if(str_len <= 0)
				error_handling("write() error");
		}
		else if(FD_ISSET(sock, &reads))
		{
			str_len=read(sock, message, sizeof(message)-1);
			if(str_len > 0)
			{
				message[str_len] = '\0';
				printf("Message from server: %s \n\n", message);
				put_check = 0;
			}
			else if(str_len == 0) //서버 소켓 종료시
			{
				fputs("server exit\n", stderr);
				break;
			}
			else
				error_handling("read() error!");
		}
	} while(1);
	close(sock);
	return 0;
}
void error_handling(char *message)
{
//	perror("error_handling()");
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

