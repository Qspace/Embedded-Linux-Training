#include "mysnake.h"
#include "nuchukhost.h"
#include <QDebug>

MySnake::MySnake(QWidget *parent) :
    QWidget(parent),m_serial(new QSerialPort(this))
{
    setWindowOpacity(0.75);
    setStyleSheet("background-color:black;");

    DOT_SIZE    = 30;
    START_DOTS  = 3;
    START_LEVEL = 100;

    startGame = false;

    QRect screen_rect = QApplication::desktop()->rect();

    WINDOW_WIDTH = screen_rect.width();
    WINDOW_HEIGHT = screen_rect.height();

    RAND_POS_X = WINDOW_WIDTH  / DOT_SIZE - 1;
    RAND_POS_Y = WINDOW_HEIGHT / DOT_SIZE - 1;

    DELTA_LEVEL = START_LEVEL / 10;

    ALL_DOTS = ( WINDOW_WIDTH * WINDOW_HEIGHT ) / ( DOT_SIZE * DOT_SIZE );

    MAX_LEVEL   = ALL_DOTS    / 10;

    m_serial->setPortName("COM34");
    m_serial->setBaudRate(9600);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);
    if (m_serial->open(QIODevice::ReadWrite))
    {

    }
    else
    {
        qDebug()<<"Failed to open Qserial port";
    }

    connect(m_serial, &QSerialPort::errorOccurred, this, &MySnake::handleError);
    connect(m_serial, &QSerialPort::readyRead, this, &MySnake::readData);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(myTimer()));

    setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    connect(this, SIGNAL(closeIt()), this, SLOT(close()));

    loadImages();
    initGame();
}

void MySnake::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    if ( !startGame )
    {
        gameOver("Ctrl+S");
    }
    else
    {
        if ( inGame && !winGame )
        {
            QPainter p(this);

            p.drawImage(apple_x, apple_y, apple);

            for (int z = 0; z < dots; z++)
            {
                if ( z == 0 )
                {
                    p.drawImage(x.at(z), y.at(z), head);
                }
                else
                {
                    p.drawImage(x.at(z), y.at(z), dot);
                }
            }

            keyPressed = false;
        }
        else
        {
            if ( winGame ) gameOver("Win");
            if ( !inGame ) gameOver("Game Over");
        }
    }
}

void MySnake::myTimer()
{
    if ( inGame )
    {
//        handleNunchukEvent();
        move();
        checkApple();
        checkCollision();
    }

    repaint();
}

void MySnake::keyPressEvent(QKeyEvent *e)
{
    //    if ( startGame && e->modifiers() == Qt::NoModifier )
    //    {
    //        switch( e->key() )
    //        {
    //        case Qt::Key_Left: if ( !keyPressed && !rightDirection ) {  = true; leftDirection = true; upDirection = false; downDirection = false; } break;
    //        case Qt::Key_Right: if ( ! && !leftDirection ) {  = true; rightDirection = true; upDirection = false; downDirection = false; } break;
    //        case Qt::Key_Up: if ( ! && !downDirection ) {  = true; upDirection = true; rightDirection = false; leftDirection = false; } break;
    //        case Qt::Key_Down: if ( ! && !upDirection ) {  = true; downDirection = true; rightDirection = false; leftDirection = false; } break;
    //        case Qt::Key_Space: if ( !inGame ) { initGame(); } else { if( !pauseGame ) { pauseGame = true; timer->stop(); } else { pauseGame = false; timer->start( level ); } } break;
    //        default:break;
    //        }
    //    }
    //    else
    //    {
    //        if ( e->modifiers() == Qt::ControlModifier )
    //        {
    //            switch( e->key() )
    //            {
    //            case Qt::Key_S: initGame(); break;
    //            case Qt::Key_W: emit closeIt(); break;
    //            case Qt::Key_Escape: emit closeIt(); break;
    //            default:break;
    //            }
    //        }
    //        else
    //        {
    //            switch( e->key() )
    //            {
    //            case Qt::Key_Escape: emit closeIt(); break;
    //            default:break;
    //            }
    //        }
    //    }

    //    QWidget::keyPressEvent(e);
}

void MySnake::loadImages()
{
    dot.load(":/like_30.png");
    checkImages(dot);
    head.load(":/panda_30.png");
    checkImages(head);
    apple.load(":/injection_30.png");
    checkImages(apple);
}

void MySnake::checkImages(QImage &image)
{
    QSize size;

    size = image.size();

    if ( size.height() != size.width() )
    {
        if ( size.height() > size.width() )
        {
            image = image.scaledToWidth(size.width());
        }
        else
        {
            image = image.scaledToHeight(size.height());
        }

        size = image.size();
    }

    if ( size.height() != DOT_SIZE )
    {
        image = image.scaled(DOT_SIZE, DOT_SIZE);
    }
}

void MySnake::initGame()
{
    x.clear();
    y.clear();

    leftDirection = false;
    rightDirection = true;
    upDirection = false;
    downDirection = false;

    startGame = true;
    pauseGame = false;
    winGame = false;
    inGame = true;
    keyPressed = false;

    dots = START_DOTS;

    level = START_LEVEL;

    new_level = dots;

    for (int z = 0; z < ( dots ); z++)
    {
        x.push_front(DOT_SIZE * dots - (z + 1) * DOT_SIZE);
        y.push_front(0);
    }

    locateApple();

    timer->start( level );
}

void MySnake::locateApple()
{
    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    int r = qrand() % RAND_POS_X;
    apple_x = ( r * DOT_SIZE );

    r = qrand() % RAND_POS_Y,
            apple_y = ( r * DOT_SIZE );
}

void MySnake::checkApple()
{
    if ( ( x.at(0) == apple_x ) && ( y.at(0) == apple_y ) )
    {
        dots++;

        x.push_front(apple_x);
        y.push_front(apple_y);

        if ( dots == ALL_DOTS )
        {
            winGame = true;
            inGame = false;
            timer->stop();
        }
        else
        {
            new_level++;

            if ( new_level % MAX_LEVEL == 0 )
            {
                if ( ( START_LEVEL - level ) > DELTA_LEVEL )
                {
                    level = level + DELTA_LEVEL;
                }

                timer->start( level );
            }

            locateApple();
        }
    }
}

void MySnake::checkCollision()
{
    for (int z = (dots - 1); z > 3; z--)
    {
        if ( x.at(0) == x.at(z) && y.at(0) == y.at(z) )
        {
            inGame = false;
            break;
        }
    }

    if ( y.at(0) >= WINDOW_HEIGHT || y.at(0) < 0 ||
         x.at(0) >= WINDOW_WIDTH || x.at(0) < 0)
    {
        inGame = false;
    }

    if ( !inGame )
    {
        timer->stop();
    }
}

void MySnake::move()
{
    if ( leftDirection )
    {
        x.push_front(x.at(0) - DOT_SIZE);
        y.push_front(y.at(0));
    }

    if ( rightDirection )
    {
        x.push_front(x.at(0) + DOT_SIZE);
        y.push_front(y.at(0));
    }

    if ( upDirection )
    {
        y.push_front(y.at(0) - DOT_SIZE);
        x.push_front(x.at(0));
    }

    if ( downDirection )
    {
        y.push_front(y.at(0) + DOT_SIZE);
        x.push_front(x.at(0));
    }

    x.removeLast();
    y.removeLast();
}

void MySnake::gameOver(QString s)
{
    QPainter p(this);

    QString message = s;
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width(message);

    p.setFont(font);
    p.setPen(Qt::red);

    int h = height();
    int w = width();

    p.translate(QPoint(w/2, h/2));
    p.drawText(-textWidth/2, 0, message);
}


void MySnake::handleNunchukEvent()
{
//    E_NunchuckDirection direction = NunchuckHost::S_getInstance()->nunchuckhost_handle();
//    setDirection(direction);
}

void MySnake::setDirection(E_NunchuckDirection direction)
{
    switch (direction) {
    case LEFT:
        if ( !keyPressed && !rightDirection ) {keyPressed  = true; leftDirection = true; upDirection = false; downDirection = false; }
        break;
    case RIGHT:
        if ( !keyPressed && !leftDirection ) {keyPressed  = true; rightDirection = true; upDirection = false; downDirection = false; }
        break;
    case UP:
         if ( !keyPressed && !downDirection ) {keyPressed  = true; upDirection = true; rightDirection = false; leftDirection = false; }
        break;
    case DOWN:
        if ( !keyPressed && !upDirection ) {keyPressed  = true; downDirection = true; rightDirection = false; leftDirection = false; }
        break;
    default:
        break;
    }
}

//! [7]
void MySnake::readData()
{
    const QByteArray data = m_serial->readAll();
    qDebug()<<"Nunchuck data"<<data;
    E_NunchuckDirection direction = NunchuckHost::S_getInstance()->nunchuckhost_handle(data.data(),data.size());
    setDirection(direction);
//    handleNunchukEvent();
}
//! [7]

//! [8]
void MySnake::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
    }
}

