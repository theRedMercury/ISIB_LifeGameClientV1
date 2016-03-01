#include "mainwindowlifegame.h"
#include "ui_mainwindowlifegame.h"

MainWindowLifeGame::MainWindowLifeGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowLifeGame)
{

    int id = QFontDatabase::addApplicationFont("://data/Greenscr.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont Greenscr(family,18);

    this->timerDots = new QTimer();
    this->timerDots->connect(this->timerDots, SIGNAL(timeout()),this, SLOT(updateDots()));
    this->timerDots->start(500);

    ui->setupUi(this);
    ui->label->setFont(Greenscr);
    ui->label->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed));
    ui->label_2->setFont(Greenscr);
    ui->label_3->setFont(Greenscr);
    ui->labelDotAnim->setFont(Greenscr);
    ui->progressBar->setFont(Greenscr);
    ui->progressBar_2->setFont(Greenscr);
    ui->progressBar_3->setFont(Greenscr);

}


void MainWindowLifeGame::updateDots()
{
    if(ui->labelDotAnim->text()!="..."){
        ui->labelDotAnim->setText(ui->labelDotAnim->text()+=".");
    }else{
        ui->labelDotAnim->setText("");
    }
}

MainWindowLifeGame::~MainWindowLifeGame()
{
    delete ui;
}
