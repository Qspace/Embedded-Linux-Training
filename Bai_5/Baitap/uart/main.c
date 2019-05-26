#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "uart.h"

int main(int argc, char** argv)
{
	char buf[8]={1,2,3,4,5,6,7,8};
	bbbuart_init(1);
	while(1)
	{
		usleep(10000);
		if(bbbuart_read(1,buf,8))
		{
			printf("recv uart data:%s\n",buf);
			bbbuart_write(1,buf,8);
			bbbuart_shutdown();
			return 0;
		}
	}
	return 0;
}
