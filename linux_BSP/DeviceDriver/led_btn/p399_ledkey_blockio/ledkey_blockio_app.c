#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE_FILENAME  "/dev/ledkey"

void print_led(unsigned char);
int main(int argc,char * argv[])
{
    int dev;
    char buff = 0;
	char oldBuff = 0;
    int ret;
	if(argc < 2)
	{
		printf("USAGE : %s [ledval] \n",argv[0]);
		return 1;
	}
	if(access(DEVICE_FILENAME,F_OK) != 0)   //파일 없을시
    {
        int ret = mknod(DEVICE_FILENAME, S_IRWXU | S_IRWXG | S_IFCHR, (230 << 8) | 0);
        if(ret < 0)
            perror("mknod()");
    }

	buff = strtoul(argv[1],NULL,16);
	printf("buff : %#04x\n",buff);

//    dev = open( DEVICE_FILENAME, O_RDWR|O_NDELAY );
    dev = open( DEVICE_FILENAME, O_RDWR );
	if(dev<0)
	{
		perror("open()");
		return 2;
	}
    ret = write(dev,&buff,sizeof(buff));
	printf("ret : %d\n",ret);
	if(ret < 0)
	{
		perror("write()");
		return 3;
	}
	print_led(buff);

	buff = 0;
	do {
		read(dev,&buff,sizeof(buff));
//		if((buff != 0) && (oldBuff != buff))
		if(oldBuff != buff)
		{
			if(buff != 0)
			{
				printf("key : %d\n",buff);
 				buff = 0x01 << (buff-1);	
				print_led(buff);
    			write(dev,&buff,sizeof(buff));
				if(buff == 0x80) //key:8
					break;
			}
			oldBuff = buff;
		}
	} while(1);
    close(dev);
    return 0;
}
void print_led(unsigned char led)
{
	int i;
	puts("1:2:3:4:5:6:7:8");
	for(i=0;i<=7;i++)
	{
		if(led & (0x01 << i))
			putchar('O');
		else
			putchar('X');
		if(i < 7 )
			putchar(':');
		else
			putchar('\n');
	}
	return;
}
