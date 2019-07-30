/*
 * uarthost.h
 *
 *  Created on: Aug 16, 2018
 *      Author: qspace
 */

#ifndef UARTHOST_H_
#define UARTHOST_H_

#define MAX_BUF_READ 1000

class UartHost
{
public:
    UartHost(const char* uartPort);
    int uarthost_init(const char* uartPort);
    int uarthost_config(int fd, int speed, int parity);
    int uarthost_read(unsigned char* buf, unsigned int numBytes);
    int uarthost_write(char* buf,unsigned char numBytes);

    static UartHost* S_getInstance(const char* uartPort)
    {
        if(S_Instance == NULL)
        {
            S_Instance = new UartHost(uartPort);
        }
        return S_Instance;
    }

private:
    int s_fd_uart1;
    static UartHost* S_Instance;
};


#endif /* UARTHOST_H_ */
