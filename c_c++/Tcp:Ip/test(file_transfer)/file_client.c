#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUFSIZE 100
void error_handling(char *message);
int main(int argc, char* argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[BUFSIZE];
	char buf[BUFSIZE];
	int str_len, size = BUFSIZE;
	int in, n;
	if(argc != 4){
		printf("Usage : %s <IP> <port> <file>\n", argv[0]);
		exit(1);
	}
	sock=socket(PF_INET, SOCK_STREAM, 0);
	if(sock < 0)
		error_handling("socket() error");
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) 
		error_handling("connect() error!");

	if ((in = open(argv[3], O_RDONLY)) < 0) {
		  fputs("<file_client.c> file open error\n", stderr);
          perror(argv[1]);
          return 2;
    }
	do {
          n = read(in, buf, BUFSIZE);
          if(n > 0)
		  {
              str_len = write(sock ,buf, n);
			  if(str_len <= 0)
				break;
		  }
          else if(n == 0)
          {
              fputs("Done ...\n",stderr);
			  close(sock);
              break;
          }
		  else if(n < 0)
			break;
          else
          {
              perror("read()");
              break;
          }
      } while(1);
	close(sock);
	return 0;
}
void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
