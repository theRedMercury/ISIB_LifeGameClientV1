#ifndef MAINWINDOWLIFEGAME_H
#define MAINWINDOWLIFEGAME_H

#include <QMainWindow>

namespace Ui {
class MainWindowLifeGame;
}

class MainWindowLifeGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowLifeGame(QWidget *parent = 0);
    ~MainWindowLifeGame();

private:
    Ui::MainWindowLifeGame *ui;
};

#endif // MAINWINDOWLIFEGAME_H
