/*
 * bbbuart.c
 *
 *  Created on: Aug 14, 2018
 *      Author: qspace
 */

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include <stdlib.h>

const char* g_uart1="/dev/ttyAMA0";
static int s_fd_uart1;

static int bbbuart_config(int fd)
{
	struct termios  UART_TypeDef ;

	UART_TypeDef.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR |
			PARMRK | INPCK | ISTRIP | IXON);
	UART_TypeDef.c_oflag = 0;
	UART_TypeDef.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
	UART_TypeDef.c_cflag &= ~(CSIZE | PARENB);
	UART_TypeDef.c_cflag |= CS8;
	UART_TypeDef.c_cc[VMIN]  = 1;
	UART_TypeDef.c_cc[VTIME] = 0;

	if (cfsetispeed (&UART_TypeDef,B115200) < 0 || cfsetospeed (&UART_TypeDef, B115200) < 0)
	{
		printf ("-E- cannot setg baudrate \r\n");
		return -1;
	}

	if (tcsetattr (fd, TCSAFLUSH, &UART_TypeDef) < 0)
	{
		printf ("-E- config failed \r\n");
		return -1;
	}

	printf ("-I- config success \r\n");
	return 0;
}

int bbbuart_init(int uartPort)
{
	switch (uartPort) {
	case 1:
		s_fd_uart1 = open(g_uart1,O_RDWR | O_NOCTTY | O_NDELAY);
		if(s_fd_uart1 == -1)
		{
			perror("Uart: Failed to open the file.\n");
			return -1;

		}
		bbbuart_config(s_fd_uart1);
		break;
	default:
		break;
	}
	return 0;
}

int bbbuart_write(char uartPort, char* buf,unsigned char numBytes)
{
	int nByteActual =0;
	switch (uartPort) {
	case 1:
		nByteActual = write(s_fd_uart1,buf,numBytes);
		if(nByteActual <0 )
		{
			perror("Failed to write to the output\n");
			return -1;
		}
		else
		{
			printf("Send data successful !\r\n");

		}
		break;
	default:
		break;
	}
	return nByteActual;
}
