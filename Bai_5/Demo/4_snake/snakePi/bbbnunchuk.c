/*
 * bbbnunchuk.c
 *
 *  Created on: Aug 13, 2018
 *      Author: qspace
 */
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include <stdlib.h>
#include "nunchukapi.h"
#include "bbbuart.h"

int main(int argc, char** argv)
{
	if (nunchuk_i2cInit() == -1)
	{
		perror("Err Init I2C \n");
		return -1;
	}
	if (bbbuart_init(1) == -1)
	{
		perror("Err Init Uart \n");
		return -1;
	}
	while(1)
	{
		nunchuk_HandleData();
		usleep(500000);
	}
	return 0;
}
