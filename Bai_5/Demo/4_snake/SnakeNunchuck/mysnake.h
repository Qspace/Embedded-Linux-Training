#ifndef MYSNAKE_H
#define MYSNAKE_H

#include <QWidget>

#include <QTime>
#include <QList>
#include <QRect>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QSerialPort>
#include "nuchukhost.h"

class MySnake : public QWidget
{
    Q_OBJECT

public:
    explicit MySnake(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *e);

private:
    QImage dot;
    QImage head;
    QImage apple;

    QTimer *timer;

    QSerialPort *m_serial = nullptr;

    int WINDOW_WIDTH;
    int DOT_SIZE;
    int START_DOTS;
    int START_LEVEL;

    int WINDOW_HEIGHT;
    int ALL_DOTS;
    int RAND_POS_X;
    int RAND_POS_Y;
    int DELTA_LEVEL;
    int MAX_LEVEL;

    int dots;
    int level;
    int new_level;
    int apple_x;
    int apple_y;

    bool leftDirection;
    bool rightDirection;
    bool upDirection;
    bool downDirection;
    bool keyPressed;
    bool inGame;
    bool startGame;
    bool pauseGame;
    bool winGame;

    QList<int> x;
    QList<int> y;

private:
    void loadImages();
    void checkImages(QImage &image);
    void initGame();
    void locateApple();
    void checkApple();
    void checkCollision();
    void move();
    void gameOver(QString s);
    void handleNunchukEvent();
    void setDirection(E_NunchuckDirection direction);

private slots:
    void readData();
    void handleError(QSerialPort::SerialPortError error);
private Q_SLOTS:
    void myTimer();

Q_SIGNALS:
    void closeIt();
};

#endif // MYSNAKE_H
