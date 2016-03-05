#include "mainwindowlifegame.h"
#include "ui_mainwindowlifegame.h"

MainWindowLifeGame::MainWindowLifeGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowLifeGame)
{

    int id = QFontDatabase::addApplicationFont("://data/Greenscr.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont Greenscr(family,18);

    this->socket = new QTcpSocket(this);
    this->connect(this->socket, SIGNAL(readyRead()), SLOT(readTcpData()) );
    this->socket->connectToHost("127.0.0.1", 11900);

    if( this->socket->waitForConnected(500) ) {
       qDebug() << "Connected";
       this->socket->write("HELLO SERVER[/TCP]");
       this->socket->flush();
    }

    this->timerDots = new QTimer();
    this->timerDots->connect(this->timerDots, SIGNAL(timeout()),this, SLOT(updateDots()));
    this->timerDots->start(500);

    this->dataTab[0]=0;
    this->dataTab[1]=0;
    this->dataTab[2]=0;

    ui->setupUi(this);

    this->sbTree = ui->textEditTree->verticalScrollBar();
    this->sbTree->setValue(this->sbTree->maximum());

    this->sbHerbi = ui->textEditHerbi->verticalScrollBar();
    this->sbHerbi->setValue(this->sbHerbi->maximum());

    this->sbCarni = ui->textEditCarni->verticalScrollBar();
    this->sbCarni->setValue(this->sbCarni->maximum());

    this->sbBrut = ui->textEditBrut->verticalScrollBar();
    this->sbBrut->setValue(this->sbBrut->maximum());

    ui->label->setFont(Greenscr);
    ui->label->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed));
    ui->labelYear->setFont(Greenscr);
    ui->label_3->setFont(Greenscr);
    ui->labelDotAnim->setFont(Greenscr);
    ui->progressBarTree->setFont(Greenscr);
    ui->progressBarHerbi->setFont(Greenscr);
    ui->progressBarCarni->setFont(Greenscr);
    ui->progressBarInvade->setFont(Greenscr);

    ui->textEditTree->setFont(Greenscr);
    ui->textEditHerbi->setFont(Greenscr);
    ui->textEditCarni->setFont(Greenscr);
    ui->textEditBrut->setFont(Greenscr);
}


void MainWindowLifeGame::readTcpData()
{
    QRegularExpression Tnbr("Tree NBR ([0-9]+)");
    QRegularExpression Herbr("Herbi NBR ([0-9]+)");
    QRegularExpression Carbr("Carni NBR ([0-9]+)");
    QRegularExpression YearBr("YEAR ([0-9]+)");

    QString data =  this->socket->readAll();
    //this->socket->flush();
    ui->textEditBrut->setText(ui->textEditBrut->toPlainText()+">"+data);
    this->sbBrut->setValue(sbBrut->maximum());

    QRegularExpressionMatch matchT = Tnbr.match(data);
    QRegularExpressionMatch matchH = Herbr.match(data);
    QRegularExpressionMatch matchC = Carbr.match(data);
    QRegularExpressionMatch matchY = YearBr.match(data);

    if(matchT.hasMatch())
    {
        this->dataTab[0]=matchT.captured(1).toInt() / 10.0;
        ui->textEditTree->setText(ui->textEditTree->toPlainText()+"\n"+matchT.captured(1));
        this->sbTree->setValue(sbTree->maximum());
    }
    if(matchH.hasMatch())
    {
        this->dataTab[1]=matchH.captured(1).toInt();
        ui->textEditHerbi->setText(ui->textEditHerbi->toPlainText()+"\n"+matchH.captured(1));
        this->sbHerbi->setValue(sbHerbi->maximum());
    }
    if(matchC.hasMatch())
    {
        this->dataTab[2]=matchC.captured(1).toInt();
        ui->textEditCarni->setText(ui->textEditCarni->toPlainText()+"\n"+matchC.captured(1));
        this->sbCarni->setValue(sbCarni->maximum());
    }
    if(matchY.hasMatch())
    {
        ui->labelYear->setText("Annee : "+matchY.captured(1));
    }

    //qDebug() << this->dataTab[0] << " - " << this->dataTab[1] << " - " << this->dataTab[2] << "\n";
    int sumD = this->dataTab[0]+this->dataTab[1]+this->dataTab[2];
    ui->progressBarTree->setValue((int)((double)(this->dataTab[0]/(float)sumD)*100.0f));
    ui->progressBarHerbi->setValue((int)((double)(this->dataTab[1]/(float)sumD)*100.0f));
    ui->progressBarCarni->setValue((int)((double)(this->dataTab[2]/(float)sumD)*100.0f));


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
