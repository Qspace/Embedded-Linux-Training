/*
 * nuchukhost.h
 *
 *  Created on: Aug 16, 2018
 *      Author: qspace
 */

#ifndef NUCHUKHOST_H_
#define NUCHUKHOST_H_

#define NU_BUTTON_PRESS 0
#define NU_BUTTON_RELEASE 1

//#define X_ZERO 124
//#define X_MIN 24
//#define X_MAX 225
//#define Y_ZERO 133
//#define Y_MIN 24
//#define Y_MAX 225
//#define OFFSET_ZERO 10

#define X_ZERO 0x7f
#define X_MIN 0x00
#define X_MAX 0xff
#define Y_ZERO 0x80
#define Y_MIN 0x00
#define Y_MAX 0xff
#define OFFSET_ZERO 10

typedef struct
{
    int xaxis;
    int yaxis;
    float angle;
    int xacc;
    int yacc;
    int zacc;
    int z;//1 release 0 push
    int c;//1 release 0 push
}NUNCHUK_DATA_T;

typedef enum
{
    CENTER,
    LEFT,
    RIGHT,
    UP,
    DOWN
} E_NunchuckDirection;

class NunchuckHost
{
public:
    NunchuckHost();
    E_NunchuckDirection nunchuckhost_handle(const char* buf, unsigned short len);
    NUNCHUK_DATA_T nunchukhost_getData(void);
    static NunchuckHost* S_getInstance()
    {
        if (S_Instance == nullptr)
        {
            S_Instance = new NunchuckHost();
        }
        return S_Instance;
    }

private:
    void nunchuckhost_decode(unsigned char byteData);
    E_NunchuckDirection DecodeDirection(NUNCHUK_DATA_T stData);
    NUNCHUK_DATA_T s_stNunchukData;
    E_NunchuckDirection direction;
    static NunchuckHost* S_Instance;

};

#endif /* NUCHUKHOST_H_ */
