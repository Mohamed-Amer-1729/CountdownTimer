#include "countdowntimer.h"
#include "ui_countdowntimer.h"
#include <QTime>
#include <QTimer>
CountdownTimer::CountdownTimer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CountdownTimer)
{
    ui->setupUi(this);

    //Set style of the widget
    setWindowSize(QSize(200, 70));
    this->setFixedSize(windowSize);
    setStyleSheet("background-color: #000000;");
    ui->TimerLabel->setStyleSheet("color: #1DCD9F");
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    //Set font
    int id = QFontDatabase::addApplicationFont(":/font/digital-7 (mono).ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    font = QFont(family);
    ui->TimerLabel->setFont(font);
    setFontSize(19);

    //Set style for text
    ui->TimerLabel->setAlignment(Qt::AlignCenter);
    ui->TimerLabel->setFixedSize(windowSize);

    //Set timers
    ui->TimerLabel->setText("CALIBRATING TIME");
    QTimer::singleShot(1000-QTime::currentTime().msec(),this,SLOT(updateTime()));

    ui->backBtn->move(-7,0);
    ui->backBtn->resize(40,30);
    ui->backBtn->setFlat(true);
    QFont fontBack = QFont(family,15);
    ui->backBtn->setStyleSheet("color: #1DCD9F");
    ui->backBtn->setFont(fontBack);
}

CountdownTimer::~CountdownTimer()
{

    delete ui;
}


QString CountdownTimer::remainingTime()
{
    //String to hold the value of how many time left in HH:mm format
    QString timeTillTen;
    QTime time = QTime::currentTime();
    int hour = time.hour();
    int min = time.minute();
    int sec = time.second();
    int hourRemain;
    int minRemain;
    int secRemain;

    if(flippedDay){
        if(hour < 24){//In case we are before midnight
            hourRemain = hourStop + 24 - hour;
        }else{//After midnight
            hourRemain = hourStop - hour;
        }
    }else{
        hourRemain = hourStop - hour;
    }

    minRemain = (59 - min + minStop) % 60;
    if(min < minStop)
        hourRemain++;
    secRemain = 59 - sec;
    hourRemain--;

    timeTillTen = formatNumber(hourRemain) + ":" + formatNumber(minRemain) + ":" + formatNumber(secRemain);
    return timeTillTen;
}

QString CountdownTimer::formatNumber(int x)
{
    if(x / 10 == 0){
        return "0" + QString::number(x);
    }else{
        return QString::number(x);
    }
}

bool CountdownTimer::isActive()
{
    QTime time = QTime::currentTime();
    if(flippedDay){
        if(time.hour() > hourStart || (time.hour() == hourStart && time.minute() >= minStart)){
            return true;
        }else{
            if(time.hour() < hourStop)
                return true;
            else{
                if(time.hour() == hourStop){
                    if(time.minute() < minStop)
                        return true;
                    else
                        return false;
                }else
                    return false;
            }
        }
    }else{
        if(time.hour() > hourStart || (time.hour() == hourStart && time.minute() >= minStart)){
            if(time.hour() < hourStop || (time.hour() == hourStop && time.minute() < minStop))
                return true;
        }
        return false;
    }
}

void CountdownTimer::updateTime()
{
    if(!isActive()){
        setFontSize(10);
        ui->TimerLabel->setText("Countdown Has Not Started Yet");
        return;
    }
    QTimer *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &CountdownTimer::updateTimeSlot);
    connect(this, &CountdownTimer::stop, timer, &QTimer::stop);

    timer->start(1000);
}

void CountdownTimer::updateFontSlot(int x)
{
    setFontSize(x);
}

void CountdownTimer::updateTimeSlot()
{
    if(!isActive()){
        setFontSize(17);
        ui->TimerLabel->setText("Countdown Complete");
        emit stop();
        return;
    }

    ui->TimerLabel->setText(remainingTime());
    setFontSize(30);
}


//Setters
void CountdownTimer::setFontSize(int pointSize)
{
    if(pointSize == font.pointSize())
        return;
    font.setPointSize(pointSize);
    ui->TimerLabel->setFont(font);
}

void CountdownTimer::setWindowSize(QSize size)
{
    windowSize = size;
}

void CountdownTimer::setParent(QWidget * x)
{
    parentPtr = x;
}

void CountdownTimer::setWorkingHours(int x, int y, int z, int w)
{
    //x and z should be between 0-23, y and w between 0-59
    hourStop = x;
    minStop = y;
    hourStart = z;
    minStart = w;

    if(hourStop < hourStart)
        flippedDay = true;
    else
        flippedDay = false;
}



void CountdownTimer::on_backBtn_clicked()
{
    parentPtr->show();
    delete this;
}

