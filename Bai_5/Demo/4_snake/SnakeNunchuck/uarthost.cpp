/*
 * uarthost.c
 *
 *  Created on: Aug 15, 2018
 *      Author: qspace
 */

#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
//#include <termios.h>
#include <stdlib.h>
#include <string.h>
#include "uarthost.h"
#include <QDebug>

UartHost* UartHost::S_Instance = NULL;

UartHost::UartHost(const char* uartPort)
{
//    this->s_fd_uart1 = 0;
//    if(uarthost_init(uartPort) == -1)
//    {
//        exit(-1);
//    }
}

int UartHost::uarthost_config(int fd, int speed, int parity)
{
//    struct termios tty;
//    memset (&tty, 0, sizeof tty);
//    if (tcgetattr (fd, &tty) != 0)
//    {
//        fprintf(stderr,"error %d from tcgetattr", errno);
//        return -1;
//    }

//    cfsetospeed (&tty, speed);
//    cfsetispeed (&tty, speed);

//    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
//    // disable IGNBRK for mismatched speed tests; otherwise receive break
//    // as \000 chars
//    tty.c_iflag &= ~IGNBRK;         // disable break processing
//    tty.c_lflag = 0;                // no signaling chars, no echo,
//    // no canonical processing
//    tty.c_oflag = 0;                // no remapping, no delays
//    tty.c_cc[VMIN]  = 0;            // read doesn't block
//    tty.c_cc[VTIME] = 0;            // seconds read timeout

//    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

//    tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
//    // enable reading
//    tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
//    tty.c_cflag |= parity;
//    tty.c_cflag &= ~CSTOPB;
//    tty.c_cflag &= ~CRTSCTS;

//    if (tcsetattr (fd, TCSANOW, &tty) != 0)
//    {
//        fprintf(stderr,"error %d from tcgetattr", errno);
//        return -1;
//    }
//    return 0;
//}

//int UartHost::uarthost_init(const char* uartPort)
//{
//    qDebug()<<uartPort;
//    this->s_fd_uart1 = open(uartPort,O_RDWR | O_NOCTTY | O_NONBLOCK);
//    if(this->s_fd_uart1 == -1)
//    {
//        perror("Uart: Failed to open the file.\n");
//        return -1;
//    }
//    uarthost_config(this->s_fd_uart1, B115200, 0);
    return 0;
}

int UartHost::uarthost_read(unsigned char* buf, unsigned int numBytes)
{
//    int nByteActual;
//    nByteActual = read (this->s_fd_uart1, buf, numBytes);
//    if(nByteActual<0)
//    {
//        perror("Error reading uart\n");
//        return -1;
//    }
//    else
//    {
//        return nByteActual;
//    }
}

int UartHost::uarthost_write(char* buf,unsigned char numBytes)
{
//    int nByteActual =0;
//    nByteActual = write(this->s_fd_uart1,buf,numBytes);
//    if(nByteActual <0 )
//    {
//        perror("Failed to write to the output\n");
//        return -1;
//    }
//    else
//    {
//        printf("Send data successful !\r\n");
//        return nByteActual;
//    }
}
