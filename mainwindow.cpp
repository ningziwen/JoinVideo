#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include <QHostInfo>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->MatchButton,&QPushButton::clicked,this,&MainWindow::matchfun);
    this->server=new QTcpServer(this);
    this->server->listen(QHostAddress::Any,12345);
    QObject::connect(this->server,&QTcpServer::newConnection,this,&MainWindow::newconnect);
    /*
    this->socket=new QTcpSocket();
    this->socket->connectToHost("127.0.0.1",12345);
    if(!socket->waitForConnected(30000))
    {
        ui->Your_idText->setText("fail");
        return;
    }
    QObject::connect(this->socket,&QTcpSocket::readyRead, this, &MainWindow::ReadData);*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::matchfun()
{
    QHostAddress targetaddress(ui->Target_idText->text());
    this->socket=new QTcpSocket();
    this->socket->connectToHost(targetaddress,12345);
    if(!socket->waitForConnected(30000))
    {

        QMessageBox message(QMessageBox::NoIcon, "Error", "Invalid IP.");
        return;
    }
    ui->MatchButton->setEnabled(false);
    QObject::connect(this->socket,&QTcpSocket::readyRead,this,&MainWindow::receivestart);
}

void MainWindow::newconnect()
{
    if(QMessageBox::Yes==QMessageBox::question(this,tr("New connect"),tr("New connect applying! Do you admit?"),QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes))
    {
        this->socket=this->server->nextPendingConnection();
        QObject::connect(this->socket,&QTcpSocket::readyRead,this,&MainWindow::receivestart);
        QByteArray arr;
        QDataStream dst(&arr,QIODevice::ReadWrite);
        dst<<QString("y");
        this->socket->write(arr);
        ui->MatchButton->setEnabled(false);
        emit matched();
    }
    else
    {
        this->socket=this->server->nextPendingConnection();
        QByteArray arr;
        QDataStream dst(&arr,QIODevice::ReadWrite);
        dst<<QString("n");
        this->socket->write(arr);
    }
}

void MainWindow::sendstart(int position)
{
    QByteArray arr;
    QDataStream dst(&arr,QIODevice::ReadWrite);
    dst<<QString::number(position,10);
    this->socket->write(arr);
}

void MainWindow::receivestart()
{
    QByteArray buffer=this->socket->readAll();
    QDataStream* dst=new QDataStream(&buffer,QIODevice::ReadOnly);
    QString s;
    (*dst)>>s;
    if(s=="y")
    {
        emit matched();
    }
    else if(s=="n")
    {
        QMessageBox message(QMessageBox::NoIcon, "Error", "The matching process has been rejected.");
        message.exec();
        this->socket->disconnectFromHost();
        ui->MatchButton->setEnabled(true);
    }
    else if(s=="ready")
    {
        otherready=true;
        if(iready) emit bothready();
    }
    else
    {
        int position=s.toInt();
        emit receivestartsignal(position);
    }
}

void MainWindow::readyplayfun(QString q)
{
    QByteArray arr;
    QDataStream dst(&arr,QIODevice::ReadWrite);
    dst<<q;
    this->socket->write(arr);
    iready=true;
    if(otherready)
    {
        emit bothready();
    }
}

void MainWindow::closeplayfun()
{
    iready=false;
    otherready=false;
}

/*
void MainWindow::ReadData()
{
    QByteArray buffer=this->socket->readAll();
    ui->Target_idText->setText("2");
    if(!buffer.isEmpty())
    {
        ui->Target_idText->setText("1");
        QString str=ui->Your_idText->text();
        str=str+tr(buffer);
        ui->Your_idText->setText(str);
    }
}
*/
