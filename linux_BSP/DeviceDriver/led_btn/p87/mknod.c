#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	if(access("/dev/test", F_OK) != 0)
	{
		int ret = mknod("/dev/test", S_IRWXU | S_IRWXG | S_IFCHR, (230 << 8) | 1);
		if(ret < 0)
			perror("mknod()");
	}
	int fd = open("/dev/test", O_RDWR);
	if(fd < 0)
	{
		perror("open()");
		return ENODEV;
	}
	return 0;
}
