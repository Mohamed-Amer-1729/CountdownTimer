#ifndef COUNTDOWNTIMER_H
#define COUNTDOWNTIMER_H

#include <QWidget>
#include <QString>
#include <QSize>
#include <QFontDatabase>
#include <QFont>

namespace Ui {
class CountdownTimer;
}

class CountdownTimer : public QWidget
{
    Q_OBJECT

public:
    explicit CountdownTimer(QWidget *parent = nullptr);
    ~CountdownTimer();

    //setter
    void setWorkingHours(int, int, int, int);
    void setParent(QWidget*);

    QSize windowSize;

private:
    //Variables
    Ui::CountdownTimer *ui;

    QFont font;
    int hourStop, hourStart, minStop, minStart;
    bool flippedDay;
    QWidget* parentPtr;

    //Setters
    void setFontSize(int);
    void setWindowSize(QSize);


    //Functions
    QString remainingTime();
    QString formatNumber(int);
    bool isActive();



private slots:
    void updateTimeSlot();
    void updateTime();
    void updateFontSlot(int);
    void on_backBtn_clicked();

signals:
    void stop();
};

#endif // COUNTDOWNTIMER_H
