#include "mainwindowlifegame.h"
#include "ui_mainwindowlifegame.h"

MainWindowLifeGame::MainWindowLifeGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowLifeGame)
{
    ui->setupUi(this);
}

MainWindowLifeGame::~MainWindowLifeGame()
{
    delete ui;
}
