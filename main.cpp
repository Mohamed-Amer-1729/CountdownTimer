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
    QScreen * screen = QGuiApplication::primaryScreen();


    w.setGeometry(screen->geometry().width() - w.size.width(),
                0,
                0,
                0);

    w.show();
    return a.exec();
}
