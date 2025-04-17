#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFont>
#include <QSize>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSize size;
private slots:
    void on_updateBtn_clicked();

    void on_startBtn_clicked();

private:
    Ui::MainWindow *ui;

    int timeSettings[4];
    QFont font;
    QFont fontNormal;

};
#endif // MAINWINDOW_H
