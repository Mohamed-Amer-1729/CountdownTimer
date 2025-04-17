#include "mainwindow.h"
#include <QApplication>
#include <QIcon>
#include <QScreen>
#include <QStyle>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setWindowIcon();
    MainWindow w;

    w.show();
    //cd.show();
    return a.exec();
}
