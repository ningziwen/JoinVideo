#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
//    void ReadData();
    QTcpSocket* socket;
    QTcpServer* server;
    void sendstart(int position);
    void receivestart();
    void readyplayfun(QString q);
    void closeplayfun();
signals:
    void matched();
    void notmatched();
    void receivestartsignal(int position);
    void bothready();

private:
    Ui::MainWindow *ui;
    void matchfun();
    void newconnect();
    bool iready=false;
    bool otherready=false;
};

#endif // MAINWINDOW_H
