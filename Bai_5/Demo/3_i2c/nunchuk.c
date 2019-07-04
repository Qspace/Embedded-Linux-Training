#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

int main(int argc, char** argv)
{
	int fd =0;
	int ret=0;
	char buf[6];
	fd = open("/dev/i2c-1",O_RDWR);
	if(fd < 0)
	{
		perror("Failed to open i2c dev \n");
		return -1;
	}
	ret = ioctl(fd,I2C_SLAVE,0x52);
	if(ret < 0)
	{
		perror("Error ioclt set up slave add\n");return -1;
	}
	ret = write(fd,"\xF0\x55",2);
	if(ret != 2)
	{
		perror("cannot init 1st 2 byte\n");return -1;
	}
	ret = write(fd,"\xFB\x00",2);
	if(ret != 2)
	{
		perror("cannot init 2nd 2 byte\n");return -1;
	}
	while(1)
	{
		ret = write(fd,"",1);
		usleep(10000);
		ret = read(fd,buf,6);
		if(ret)
		{
			for (int i=0; i< ret; i++)
			{
				printf("buf[%d]: %2x\n",i,buf[i]);
			}
			printf("*******************\n");
		}
	}
	return 0;
}

