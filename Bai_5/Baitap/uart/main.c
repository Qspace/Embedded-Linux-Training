#include <stdio.h>
#include <stdlib.h>
#include "uart.h"

int main(int argc, char** argv)
{
	char buf[8] ={0};
	while(1)
	{
		if(bbbuart_read(1,buf,8))
		{
			bbbuart_write(1,buf,8);
		}
	}
	return 0;
}
