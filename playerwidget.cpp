#include "playerwidget.h"
#include "ui_playerwidget.h"
#include <QBoxLayout>
#include <QCloseEvent>

PlayerWidget::PlayerWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayerWidget)
{
    ui->setupUi(this);

    QWidget *widget=new QWidget;
    this->setCentralWidget(widget);

    player=new QMediaPlayer;

    videoWidget=new QVideoWidget(widget);
    player->setVideoOutput(videoWidget);
    player->setVolume(50);

    ui->VolumeSlider->setRange(0, 100);
    ui->VolumeSlider->setValue(50);

    QBoxLayout *ctlLayout=new QHBoxLayout;
    ctlLayout->addWidget(ui->label);
    ctlLayout->addWidget(ui->PositionLabel);
    ctlLayout->addWidget(ui->label_3);
    ctlLayout->addWidget(ui->PositionText);
    ctlLayout->addWidget(ui->StartButton);
    ctlLayout->addWidget(ui->StopButton);
    ctlLayout->addWidget(ui->VolumeLabel);
    ctlLayout->addWidget(ui->VolumeSlider);



    QBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addWidget(videoWidget);
    mainLayout->addLayout(ctlLayout);

    widget->setLayout(mainLayout);

    connect(ui->StartButton,&QPushButton::clicked,this,&PlayerWidget::startfun);
    connect(ui->StopButton,&QPushButton::clicked,this,&PlayerWidget::stopfun);
    connect(ui->VolumeSlider,&QSlider::valueChanged,this,&PlayerWidget::valuechangefun);
    connect(player,&QMediaPlayer::positionChanged,this,&PlayerWidget::positionchangefun);
    connect(ui->PositionText,&QLineEdit::textChanged,this,&PlayerWidget::textchangefun);
//    connect(player,&QMediaPlayer::durationChanged,this,&PlayerWidget::durationchangefun);
}

PlayerWidget::~PlayerWidget()
{
    delete ui;
}

void PlayerWidget::startfun()
{
    if(m_playerState==QMediaPlayer::PausedState||m_playerState==QMediaPlayer::StoppedState)
    {
        m_playerState=QMediaPlayer::PlayingState;
        ui->StartButton->setText("Pause");
        player->play();
        emit startsignal(player->position()/1000);
    }
    else
    {
        m_playerState=QMediaPlayer::PausedState;
        ui->StartButton->setText("Start");
        player->pause();
    }
}

void PlayerWidget::stopfun()
{
    m_playerState=QMediaPlayer::StoppedState;
    ui->StartButton->setText("Start");
    player->stop();
}

void PlayerWidget::fullfun()
{
    if(!videoWidget->isFullScreen())
    {
        videoWidget->setFullScreen(true);
    }
}

void PlayerWidget::showfun(QString filepath)
{
    this->show();
    m_playerState=QMediaPlayer::StoppedState;
    ui->StartButton->setText("Start");
    m_fileName=filepath;
    player->setMedia(QUrl::fromLocalFile(m_fileName));
    ui->PositionLabel->setText(QString::number(0));
}

void PlayerWidget::valuechangefun(int value)
{
    player->setVolume(value);
}

void PlayerWidget::positionchangefun(int position)
{
    ui->PositionLabel->setText(QString::number(position/1000));
}

void PlayerWidget::textchangefun()
{
    this->progresschangefun(ui->PositionText->text().toInt());
}

void PlayerWidget::progresschangefun(int position)
{
    m_playerState=QMediaPlayer::PlayingState;
    ui->StartButton->setText("Pause");
    player->play();
    player->setPosition(position*1000);
    ui->PositionLabel->setText(QString::number(position));
}

void PlayerWidget::closeEvent(QCloseEvent *event)
{
    this->hide();
    emit closeplay();
    event->ignore();
}

/*
void PlayerWidget::durationchangefun(int du)
{
    ui->progressBar->setRange(0,du/1000+1);
}*/
