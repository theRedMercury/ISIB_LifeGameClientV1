#ifndef MAINWINDOWLIFEGAME_H
#define MAINWINDOWLIFEGAME_H

#include <QMainWindow>
#include <QFontDatabase>
#include <QTcpSocket>
#include <QScrollBar>
#include <QRegExp>
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
    ~MainWindowLifeGame();

private slots :
    void readTcpData();
    void updateDots();

private:
    int dataTab[4] ;

    Ui::MainWindowLifeGame *ui;
    QTimer *timerDots;
    QTcpSocket *socket;
    QScrollBar *sbTree;
    QScrollBar *sbHerbi;
    QScrollBar *sbCarni;
    QScrollBar *sbBrut;

};

#endif // MAINWINDOWLIFEGAME_H
