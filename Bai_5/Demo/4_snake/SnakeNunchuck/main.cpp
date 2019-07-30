#include "mysnake.h"
#include "uarthost.h"
#include "nuchukhost.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UartHost::S_getInstance("/dev/ttyUSB0");
    NunchuckHost::S_getInstance();
    MySnake w;
    w.show();

    return a.exec();
}
