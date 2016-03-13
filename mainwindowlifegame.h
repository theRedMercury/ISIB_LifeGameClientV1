#ifndef MAINWINDOWLIFEGAME_H
#define MAINWINDOWLIFEGAME_H

#include <QMainWindow>
#include <QFontDatabase>
#include <QTcpSocket>
#include <QScrollBar>
#include <QRegExp>
#include <QSettings>
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
    void updateDots();
    void changeBG();
    void readGPIO();

private:
    int dataTab[4] ;
    unsigned int pinNumIn = 3;
    mmapGpio *rpiGpio;

    Ui::MainWindowLifeGame *ui;
    QTimer *timerDots;
    QTimer *timerButt;
    QTimer *timerGpio;
    QTcpSocket *socket;
    QScrollBar *sbTree;
    QScrollBar *sbHerbi;
    QScrollBar *sbCarni;
    QScrollBar *sbInvad;
    QScrollBar *sbBrut;

};

#endif // MAINWINDOWLIFEGAME_H
