#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "uart.h"

int main(int argc, char** argv)
{
	char buf[8]={0};
	bbbuart_init(1);
	while(1)
	{
		usleep(10000);
		//bbbuart_write(1,buf,8);
		int nBytes = bbbuart_read(1,buf,8);
		if(nBytes)
		{
			printf("recv uart data:%s\n",buf);
			bbbuart_write(1,buf,nBytes);
		}
	}
	bbbuart_shutdown();
	return 0;
}
