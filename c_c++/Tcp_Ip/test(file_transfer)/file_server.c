#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUFSIZE 100
void error_handling(char *message);
int main(int argc, char *argv[])
{
	int serv_sock;
	int clnt_sock;
	int str_len, out;
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;
	char message[BUFSIZE];
	if(argc != 3){
		printf("Usage : %s <port> <file>\n", argv[0]);
		exit(1);
	}
	if ((out = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) < 0) {
          perror(argv[2]);
          return 3;
      }
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock < 0)
		error_handling("socket() error");
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));
	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr) )< 0 )
		error_handling("bind() error"); 
	if(listen(serv_sock, 5) < 0)
		error_handling("listen() error");
	clnt_addr_size=sizeof(clnt_addr);  
	clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
	if(clnt_sock < 0)
		error_handling("accept() error");  

/*	do{
		str_len = read(clnt_sock, message, sizeof(message));
		//message[strlen(message)] = '\0';
		if(str_len <= 0)
			break;
		int s =	write(out, message, str_len);	
		printf("%d \n", s);
		if(s <= 0)
			break;
	}while(1);
	fputs("Done ...\n", stderr);
	*/
	do {
    	str_len = read(clnt_sock, message, sizeof(message));
        if(str_len > 0)
		{
        	printf("size : %d\n", str_len);
        	write(out, message, str_len);
		}
        else if(str_len == 0)
        {
        	fputs("Done ...\n",stderr);
            break;
        }
        else
        {
            perror("read()");
        	break;
        }
    } while(1);
	close(clnt_sock);	
	close(serv_sock);
	return 0;
}
void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
