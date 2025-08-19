#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <poll.h>
#include <string.h>

#define DEVICE_FILENAME "/dev/ledkey"

int main(int argc, char *argv[])
{
	int dev;
	char buff;
	int ret;
	int num = 1;
	struct pollfd Events[2];
	char keyStr[80];

    if(argc != 2)
    {
        printf("Usage : %s [led_data(0x00~0xff)]\n",argv[0]);
        return 1;
    }
    if(access(DEVICE_FILENAME,F_OK) != 0)   //파일 없을시
    {
        int ret = mknod(DEVICE_FILENAME, S_IRWXU | S_IRWXG | S_IFCHR, (230 << 8) | 0);
        if(ret < 0)
            perror("mknod()");
    }

    buff = (char)strtoul(argv[1],NULL,16);
    if((buff < 0x00) || (0xff < buff))
    {
        printf("Usage : %s [led_data(0x00~0xff)]\n",argv[0]);
        return 2;
    }

//  dev = open(DEVICE_FILENAME, O_RDWR | O_NONBLOCK);
    dev = open(DEVICE_FILENAME, O_RDWR );
	if(dev < 0)
	{
		perror("open");
		return 2;
	}
	write(dev,&buff,sizeof(buff));

	fflush(stdin);
	memset( Events, 0, sizeof(Events));
  	Events[0].fd = fileno(stdin);
  	Events[0].events = POLLIN;
	Events[1].fd = dev;
	Events[1].events = POLLIN;
	while(1)
	{
		ret = poll(Events, 2, 2000);  //2000ms
		if(ret<0)
		{
			perror("poll");
			exit(1);
		}
		else if(ret==0)
		{
  			printf("poll time out : %d Sec\n",2*num++);
			continue;
		}
		if(Events[0].revents & POLLIN)  //stdin
		{
			fgets(keyStr,sizeof(keyStr),stdin);
//			if(keyStr[0] == 'q')
			if(!strcmp(keyStr, "q\n"))
				break;
			keyStr[strlen(keyStr)-1] = '\0';  //'\n' clear
			printf("STDIN : %s\n",keyStr);
			buff = (char)atoi(keyStr);
			if(buff != 0)
				buff = 1 << buff-1;
			write(dev,&buff,sizeof(buff));
		}
		else if(Events[1].revents & POLLIN) //ledkey
		{
			ret = read(dev,&buff,sizeof(buff));
			printf("key_no : %d\n",buff);
			if(buff == 8)
				break;
			buff = 1 << buff-1;
			write(dev,&buff,sizeof(buff));
		}
	}
	close(dev);
	return 0;
}
