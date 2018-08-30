#include "filewidget.h"
#include "ui_filewidget.h"
#include <QFileDialog>
#include <QCryptographicHash>
#include <QFile>

#include <QHBoxLayout>

FileWidget::FileWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FileWidget)
{
    ui->setupUi(this);
    connect(ui->ChooseButton,&QPushButton::clicked,this,&FileWidget::ChooseFun);
    connect(ui->PlayButton,&QPushButton::clicked,this,&FileWidget::PlayFun);
}

FileWidget::~FileWidget()
{
    delete ui;
}

void FileWidget::ChooseFun()
{
    filepath = QFileDialog::getOpenFileName(this,
                                                tr("Open File"),
                                                ".");
    ui->FileLabel->setText(filepath);
}


void FileWidget::PlayFun()
{
    emit readyplaysignal("ready");
    ui->PlayButton->setEnabled(false);
}

void FileWidget::bothreadyfun()
{
    emit Playsignal(filepath);
}

void FileWidget::closeplayfun()
{
    ui->PlayButton->setEnabled(true);
}
