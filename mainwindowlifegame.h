#ifndef MAINWINDOWLIFEGAME_H
#define MAINWINDOWLIFEGAME_H

#include <QMainWindow>
#include <QFontDatabase>
#include <QTcpSocket>
#include <QScrollBar>
#include <QRegExp>
#include <QSettings>
#include <QTextCursor>
#include <QTimer>
#include <QDebug>
#include "mmapGpio.h"

namespace Ui {
class MainWindowLifeGame;
}

class MainWindowLifeGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowLifeGame(QWidget *parent = 0);
    void pushButton();
    ~MainWindowLifeGame();

private slots :
    void readTcpData();
    void autoReconnect();
    void updateDots();
    void changeBG();
    void readGPIO();

private:
    int dataTab[4] ;
    unsigned int pinNumIn = 4;
    mmapGpio *rpiGpio;
    QString ip;
    quint16 port;

    Ui::MainWindowLifeGame *ui;
    QTimer *timerDots;
    QTimer *timerButt;
    QTimer *timerGpio;
    QTcpSocket *socket;

    QRegExp *tnbr;
    QRegExp *herbr;
    QRegExp *carbr;
    QRegExp *invbr;
    QRegExp *yearBr;
    QString data;
    QTextCursor cursor;

    /*QScrollBar *sbTree;
    QScrollBar *sbHerbi;
    QScrollBar *sbCarni;
    QScrollBar *sbInvad;
    QScrollBar *sbBrut;*/
};

#endif // MAINWINDOWLIFEGAME_H
