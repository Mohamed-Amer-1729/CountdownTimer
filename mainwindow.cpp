#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QDebug>
#include <QTimer>
#include <QFontDatabase>
#include <QFont>
#include <QSize>
#include <QIcon>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    size = QSize(200, 70);
    //Set font
    int id = QFontDatabase::addApplicationFont(":/font/digital-7 (mono).ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont LCD(family, 19);
    ui->TimerLabel->setFont(LCD);

    //Set style for text
    ui->TimerLabel->setAlignment(Qt::AlignCenter);
    ui->TimerLabel->setFixedSize(size);

    //Set timers
    ui->TimerLabel->setText("CALIBRATING TIME");
    QTimer::singleShot(1000-QTime::currentTime().msec(),this,SLOT(updateTime()));

    this->setFixedSize(size);
    setWindowTitle(" ");
    QIcon transparent(":/icon/transparent.ico");
    setWindowIcon(transparent);

    setStyleSheet("background-color: #000000;");
    ui->TimerLabel->setStyleSheet("color: #1DCD9F");
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);


}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::remainingTime()
{
    //String to hold the value of how many time left in HH:mm format
    QString timeTillTen;
    QTime time = QTime::currentTime();
    int hour = time.hour();
    if(hour <= 5)//In case the user has not reached 6AM, the program will say the day has not started yet
        return "Day Has Not Started";
    int min = time.minute();
    int sec = time.second();

    int hourRemain = 22 - hour;
    int minRemain = 60 - min;
    if(minRemain == 60)
        minRemain = 0;
    else
        hourRemain--;

    int secRemain = 60 - sec;
    if(secRemain == 60)
        secRemain = 0;
    else
        minRemain--;
    timeTillTen = formatNumber(hourRemain) + ":" + formatNumber(minRemain) + ":" + formatNumber(secRemain);
    return timeTillTen;
}

QString MainWindow::formatNumber(int x)
{
    if(x / 10 == 0){
        return "0" + QString::number(x);
    }else{
        return QString::number(x);
    }
}

void MainWindow::updateTime()
{
    int id = QFontDatabase::addApplicationFont(":/font/digital-7.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont LCD(family, 30);
    //ui->TimerLabel->setFont(LCD);


    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimeSlot);
    timer->start(1000);
}

void MainWindow::updateTimeSlot()
{
    ui->TimerLabel->setText(remainingTime());
    QTimer::singleShot(0,this,SLOT(updateFontSlot()));
}

void MainWindow::updateFontSlot()
{
    int id = QFontDatabase::addApplicationFont(":/font/digital-7 (mono).ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont LCD(family, 30);
    ui->TimerLabel->setFont(LCD);
}
