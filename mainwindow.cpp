#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFontDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QDir>
#include <QScreen>
#include <countdowntimer.h>
#include <QRect>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    size = QSize(600, 400);

    QFile settings("settings.txt");
    if(!settings.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "File open failed\n";
        return;
    }


    int index = 0;
    while(!settings.atEnd()){
        QString line = settings.readLine();
        timeSettings[index++] = line.toInt();
    }
    settings.close();
    ui->hourEditStart->setText(QString::number(timeSettings[0]));
    ui->minEditStart->setText(QString::number(timeSettings[1]));
    ui->hourEditEnd->setText(QString::number(timeSettings[2]));
    ui->minEditEnd->setText(QString::number(timeSettings[3]));

    QFile styleFile( ":/style/main.qss" );
    styleFile.open( QFile::ReadOnly );

    // Apply the loaded stylesheet
    QString style( styleFile.readAll() );
    setStyleSheet( style );


    //Set font
    int id = QFontDatabase::addApplicationFont(":/font/digital-7 (mono).ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    font = QFont(family, 30);
    fontNormal = QFont(family, 13);
    ui->title->setFont(font);


    //Set style for text
    ui->title->setAlignment(Qt::AlignCenter);
    setFixedSize(size);
    QRect rect(0,0,size.width(), size.height());
    ui->colonLabelEnd->setFont(fontNormal);
    ui->colonLabelStart->setFont(fontNormal);

    ui->fromLabel->setFont(fontNormal);
    ui->toLabel->setFont(fontNormal);

    ui->startBtn->setFont(fontNormal);
    ui->startBtn->setFlat(true);
    ui->updateBtn->setFont(fontNormal);
    ui->updateBtn->setFlat(true);

    ui->hourEditStart->setFont(fontNormal);

    ui->minEditStart->setFont(fontNormal);

    ui->hourEditEnd->setFont(fontNormal);

    ui->minEditEnd->setFont(fontNormal);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_updateBtn_clicked()
{
    qDebug() << "btn clicked\n";
    if( ui->hourEditEnd->text().isEmpty() ||
        ui->minEditEnd->text().isEmpty() ||
        ui->hourEditStart->text().isEmpty() ||
        ui->minEditStart->text().isEmpty()){
        qDebug() << "String empty\n";
        QMessageBox::warning(
            this,
            tr("CountDownTimer"),
            tr("Please fill out all information") );
        return;
    }

    bool ok[4];
    int num[4];
    num[0] = ui->hourEditStart->text().toInt(&ok[0]);
    num[1] = ui->minEditStart->text().toInt(&ok[1]);
    num[2] = ui->hourEditEnd->text().toInt(&ok[2]);
    num[3] = ui->minEditEnd->text().toInt(&ok[3]);
    if(!(ok[0] && ok[1] && ok[2] && ok[3])){
        qDebug() << "String NaN\n";
        QMessageBox::warning(
            this,
            tr("CountDownTimer"),
            tr("Please Input Numbers") );
        return;
    }

    if(num[0] < 0 || num[0] > 23//hour start
        || num[1] < 0 || num[1] > 59//min start
        || num[2] < 0 || num[2] > 23//hour end
        || num[3] < 0 || num[3] > 59)//min end
    {
        qDebug() << "out of bound number\n";
        QMessageBox::warning(
            this,
            tr("CountDownTimer"),
            tr("Please Input within accepted values (0-23) & (0-59)") );
        return;
    }


    QFile settings("settings.txt");
    qDebug() << QDir::currentPath();
    if(!settings.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "File open failed\n";
        return;
    }
    for(int i = 0 ; i < 4; i++)
        timeSettings[i] = num[i];
    qDebug() << "File updated?\n";
    QTextStream out(&settings);

    out << ui->hourEditStart->text() << "\n"
        << ui->minEditStart->text() << "\n"
        << ui->hourEditEnd->text() << "\n"
        << ui->minEditEnd->text();
    settings.close();
}


void MainWindow::on_startBtn_clicked()
{
    CountdownTimer* timer = new CountdownTimer;
    timer->setParent(this);

    timer->setWorkingHours(timeSettings[2],timeSettings[3],timeSettings[0],timeSettings[1]);

    QScreen * screen = QGuiApplication::primaryScreen();


    timer->setGeometry(screen->geometry().width() - timer->windowSize.width(),
                   0,
                   0,
                   0);

    hide();
    timer->show();

}

