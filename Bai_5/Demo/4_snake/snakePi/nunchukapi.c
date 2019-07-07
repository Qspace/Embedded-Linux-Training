/*
 * nunchukapi.c
 *
 *  Created on: Aug 13, 2018
 *      Author: qspace
 */
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include "nunchukapi.h"
#include "bbbuart.h"

#ifndef ADDR
#define NUNCHUK_ADDR 0x52 //wii nunchuck address : 0x52
#endif
#define NUNCHUK_DATA_NUM_BYTES 6
#define STX 0x02
#define ETX 0x03
static int s_fdI2c;
const char *g_device_i2c="/dev/i2c-1"  ;

int nunchuk_i2cInit(void)
{
	s_fdI2c = open(g_device_i2c ,O_RDWR);
	if(s_fdI2c == -1)
	{
		perror("I2C: Failed to open the file.\n");
		return -1;

	}
	//Handshake with nunchuk
	if(ioctl(s_fdI2c,I2C_SLAVE,NUNCHUK_ADDR) < 0) perror("Can't ioctl  \n ");

	/*Khoi tao nunchuck */
	if (write(s_fdI2c, "\xF0\x55", 2) != 2)
	{
		fprintf(stderr, "ERROR: Cannot initialize device 0x%02x@0xF0 on \"%s\": %m\n", NUNCHUK_ADDR, g_device_i2c);
		exit(-1);
	}
	if (write(s_fdI2c, "\xFB\x00", 2) != 2)
	{
		fprintf(stderr, "ERROR: Cannot initialize device 0x%02x@0xF0 on \"%s\": %m\n", NUNCHUK_ADDR, g_device_i2c);
		exit(-1);
	}
	return 0;
}

int nunchuk_read(char* buf, unsigned char numBytes)
{
	int n = read(s_fdI2c,buf,numBytes);
	if(n<0)
	{
		fprintf(stderr,"Read error %s:0x%02x - %m",g_device_i2c,NUNCHUK_ADDR);
	}
	return n;
}

int nunchuk_write(char* buf, unsigned char numBytes)
{
	int n = write(s_fdI2c, buf, numBytes);
	if (n != numBytes)
	{
		fprintf(stderr,"Read error %s:0x%02x - %m",g_device_i2c,NUNCHUK_ADDR);
	}
	return n;
}

int nunchuk_HandleData(void)
{
	char buf[NUNCHUK_DATA_NUM_BYTES+2];
	buf[0]=STX;
	buf[NUNCHUK_DATA_NUM_BYTES+1]= ETX;
	nunchuk_write("",1);
	usleep(10000);
	nunchuk_read(buf+1,NUNCHUK_DATA_NUM_BYTES);
	for(int i = 0; i < NUNCHUK_DATA_NUM_BYTES+2; i++)
	{
		printf("buf[%d]: %x\n",i,buf[i]);
	}
	printf("****************************\n");
	bbbuart_write(1,buf,NUNCHUK_DATA_NUM_BYTES+2);
	return 0;
}


