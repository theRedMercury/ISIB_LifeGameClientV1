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

private:
    int dataTab[4] ;

    Ui::MainWindowLifeGame *ui;
    QTimer *timerDots;
    QTimer *timerButt;
    QTcpSocket *socket;
    QScrollBar *sbTree;
    QScrollBar *sbHerbi;
    QScrollBar *sbCarni;
    QScrollBar *sbInvad;
    QScrollBar *sbBrut;

};

#endif // MAINWINDOWLIFEGAME_H
