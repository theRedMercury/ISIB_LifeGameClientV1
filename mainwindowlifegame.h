#ifndef MAINWINDOWLIFEGAME_H
#define MAINWINDOWLIFEGAME_H

#include <QMainWindow>
#include <QFontDatabase>
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

private slots:
    void updateDots();
private:
    Ui::MainWindowLifeGame *ui;
    QTimer *timerDots;

};

#endif // MAINWINDOWLIFEGAME_H
