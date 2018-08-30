#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QMainWindow>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QMediaPlaylist>

namespace Ui {
class PlayerWidget;
}

class PlayerWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlayerWidget(QWidget *parent = 0);
    ~PlayerWidget();
    void showfun(QString filepath);
    void progresschangefun(int position);

signals:
    void startsignal(int position);
    void closeplay();
    void progresschange(int pos);

private:
    Ui::PlayerWidget *ui;
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QMediaPlaylist *Playlist;
    QString m_fileName="";
    QMediaPlayer::State m_playerState;
    void startfun();
    void stopfun();
    void fullfun();
    void valuechangefun(int value);
    void positionchangefun(int position);
    void textchangefun();
protected:
     void closeEvent(QCloseEvent *event);
//     void durationchangefun(int du);
};

#endif // PLAYERWIDGET_H
