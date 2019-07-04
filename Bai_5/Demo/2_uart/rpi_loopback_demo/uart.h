/*
 * bbbuart.h
 *
 *  Created on: Aug 14, 2018
 *      Author: qspace
 */

#ifndef BBBUART_H_
#define BBBUART_H_

int bbbuart_init(int uartPort);
int bbbuart_write(char uartPort, char* buf,unsigned char numBytes);
int bbbuart_read(char uartPort, char* buf, unsigned char numBytes);
int bbbuart_shutdown(void);
#endif /* BBBUART_H_ */