#include "mainwindow.h"
#include "filewidget.h"
#include "playerwidget.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w=new MainWindow();
    FileWidget* f=new FileWidget();
    PlayerWidget* p=new PlayerWidget();
    w->show();
    QObject::connect(w,&MainWindow::matched,f,&FileWidget::show);
    QObject::connect(f,&FileWidget::Playsignal,p,&PlayerWidget::showfun);
    QObject::connect(p,&PlayerWidget::startsignal,w,&MainWindow::sendstart);
    QObject::connect(f,&FileWidget::readyplaysignal,w,&MainWindow::readyplayfun);
    QObject::connect(w,&MainWindow::receivestartsignal,p,&PlayerWidget::progresschangefun);
    QObject::connect(w,&MainWindow::bothready,f,&FileWidget::bothreadyfun);
    QObject::connect(p,&PlayerWidget::closeplay,f,&FileWidget::closeplayfun);
    QObject::connect(p,&PlayerWidget::closeplay,w,&MainWindow::closeplayfun);
    return a.exec();
}
