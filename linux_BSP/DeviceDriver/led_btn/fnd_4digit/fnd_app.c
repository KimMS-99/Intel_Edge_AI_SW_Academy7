#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
 #include <string.h>

#define NODE_NAME "/dev/fnd_dev"

int main(int argc, char * argv[]) 
{
	int fd;
	char buf[128];
	int data;

	if(access(NODE_NAME, F_OK)) {       /* 노드 파일이 존재하는지 검사 */
		system("insmod /mnt/nfs_ubuntu/fnd_dev.ko");      /* 드라이버 적재 */
	}
	fd = open(NODE_NAME, O_WRONLY);
	if(fd < 0)
	{
		perror("open()");
		return 2;
	}

	while(1){
		printf("Input data: ");
		fgets(buf,sizeof(buf),stdin);
		if(memcmp(buf, "quit", 4) == 0) {
			break;
		}

		data = atoi(buf);
		write(fd, &data, sizeof(data));
		printf("#### data = %d\n", data);
	}

	close(fd);

	system("rmmod fnd_dev");         /* 드라이버 제거 */

	printf("#### Exit program.\n");

	exit(0);
}
