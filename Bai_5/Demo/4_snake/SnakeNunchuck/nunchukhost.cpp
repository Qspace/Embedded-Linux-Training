/*
 * nunchukhost.c
 *
 *  Created on: Aug 16, 2018
 *      Author: qspace
 */

#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "nuchukhost.h"
#include "uarthost.h"

#define STX 0x02
#define ETX 0x03
#define NUNCHUK_DATA_NUM_BYTES 6
//#define X_ZERO 124
//#define X_MIN 24
//#define X_MAX 225
//#define Y_ZERO 133
//#define Y_MIN 24
//#define Y_MAX 225


typedef enum
{
    WAIT_STX,
    WAIT_DATA,
    WAIT_ETX
}E_DataState;

NunchuckHost* NunchuckHost::S_Instance = NULL;
NunchuckHost::NunchuckHost()
{
    this->s_stNunchukData = {
        .xaxis =0,
        .yaxis =0,
        .angle = 0,
        .xacc =0,
        .yacc =0,
        .zacc =0,
        .z = 0,//1 release 0 push
        .c = 0//1 release 0 push
    };
    this->direction = CENTER;
}

E_NunchuckDirection NunchuckHost::nunchuckhost_handle(const char* buf, unsigned short len)
{
//    unsigned char buf[MAX_BUF_READ]={0};
//    int n = UartHost::S_getInstance("/dev/ttyUSB0")->uarthost_read(buf,MAX_BUF_READ);
    if (len > 0)
    {
        for(int i =0; i<len;i++)
        {
            printf("buf[%d]: %x\n",i,buf[i]);
            this->nunchuckhost_decode(buf[i]);
        }
    }
    return this->direction;
}

NUNCHUK_DATA_T NunchuckHost::nunchukhost_getData(void)
{
    return this->s_stNunchukData;
}

void NunchuckHost::nunchuckhost_decode(unsigned char byteData)
{
    static E_DataState s_dataState = WAIT_STX;
    static unsigned char s_Id = 0;
    static unsigned char buf[NUNCHUK_DATA_NUM_BYTES] = {0};
    switch (s_dataState) {
    case WAIT_STX:
        if(byteData == STX)
        {
            s_dataState = WAIT_DATA;
            s_Id = 0;
        }
        break;
    case WAIT_DATA:
        buf[s_Id]=byteData;
        //		printf("data[%d]: %x\n",s_Id,buf[s_Id]);
        if(s_Id==NUNCHUK_DATA_NUM_BYTES-1)
        {
            s_dataState = WAIT_ETX;
        }
        s_Id++;
        break;
    case WAIT_ETX:
        if(byteData == ETX)
        {
            s_dataState = WAIT_STX;
            //correct packet, decode it
            this->s_stNunchukData.xaxis = buf[0]-X_ZERO;
            this->s_stNunchukData.yaxis = buf[1]-Y_ZERO;
            this->s_stNunchukData.angle = atan2((float)this->s_stNunchukData.yaxis,
                                                (float)this->s_stNunchukData.xaxis);
            this->s_stNunchukData.xacc = (buf[2] << 2) | ((buf[5] >> 2) & 3);
            this->s_stNunchukData.yacc = (buf[3] << 2) | ((buf[5] >> 4) & 3);
            this->s_stNunchukData.zacc = (buf[4] << 2) | ((buf[5] >> 6) & 3);
            this->s_stNunchukData.z = (buf[5] >> 0) & 1;
            this->s_stNunchukData.c = (buf[5] >> 1) & 1;
            this->direction = DecodeDirection(this->s_stNunchukData);
            memset(buf,0,NUNCHUK_DATA_NUM_BYTES);
            printf("xAxis: %d\n",this->s_stNunchukData.xaxis);
            printf("yAxis: %d\n",this->s_stNunchukData.yaxis);
            printf("Angle: %0.2lf\n",this->s_stNunchukData.angle);
            printf("xAcc: %d\n",this->s_stNunchukData.xacc);
            printf("yAcc: %d\n",this->s_stNunchukData.yacc);
            printf("zAcc: %d\n",this->s_stNunchukData.zacc);
            printf("z button: %d\n",this->s_stNunchukData.z);
            printf("c button: %d\n",this->s_stNunchukData.c);
        }
        else
        {
            perror("Wrong Nunchuk packet \n");
            s_dataState = WAIT_STX;
        }
        break;
    default:
        break;
    }
}

E_NunchuckDirection NunchuckHost::DecodeDirection(NUNCHUK_DATA_T stData)
{
    if((abs(stData.xaxis)+abs(stData.yaxis))> OFFSET_ZERO)//check joy not at zero position
    {
        //		printf("angle: %0.2lf",stData.angle);
        if ((stData.angle >= -M_PI_4)&&(stData.angle < M_PI_4))
        {
            //			printf("quard 1\n");
            return RIGHT;
        }
        else if ((stData.angle >= M_PI_4)&&(stData.angle < 3*M_PI_4))
        {
            //			printf("quard 4\n");
            return UP;
        }
        else if ((stData.angle >= -3*M_PI_4)&&(stData.angle < -M_PI_4))
        {
            //			printf("quard 2\n");
            return DOWN;
        }
        else
        {
            //			printf("quard 3\n");
            return LEFT;
        }
    }
    else
    {
        return CENTER;
    }
}
