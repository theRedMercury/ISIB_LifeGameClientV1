#include "mainwindowlifegame.h"
#include "ui_mainwindowlifegame.h"

MainWindowLifeGame::MainWindowLifeGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowLifeGame)
{

    int id = QFontDatabase::addApplicationFont("://data/Greenscr.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont Greenscr(family,24);

    //f.setStyleStrategy(QFont::PreferAntialias);


    ui->setupUi(this);
     ui->label->setFont(Greenscr);




}

MainWindowLifeGame::~MainWindowLifeGame()
{
    delete ui;
}
