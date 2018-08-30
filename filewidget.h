#ifndef FILEWIDGET_H
#define FILEWIDGET_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QHBoxLayout>

namespace Ui {
class FileWidget;
}

class FileWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileWidget(QWidget *parent = 0);
    ~FileWidget();
    void closeplayfun();
    void bothreadyfun();
signals:
    void Playsignal(QString filepath);
    void readyplaysignal(QString q);

private:
    Ui::FileWidget *ui;
    void ChooseFun();
    void PlayFun();
    QString filepath="";
    QString filemd5="";
};

#endif // FILEWIDGET_H
