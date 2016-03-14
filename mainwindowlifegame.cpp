#include "mainwindowlifegame.h"
#include "ui_mainwindowlifegame.h"

MainWindowLifeGame::MainWindowLifeGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowLifeGame)
{

    this->rpiGpio = new mmapGpio();
    this->rpiGpio->setPinDir(this->pinNumIn,mmapGpio::INPUT);

    int id = QFontDatabase::addApplicationFont("://data/Greenscr.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont Greenscr(family,18);

    this->socket = new QTcpSocket(this);
    this->connect(this->socket, SIGNAL(readyRead()), SLOT(readTcpData()) );

    QSettings settings("conf.ini", QSettings::IniFormat);
    QString ip = settings.value("OPTIONS/IP","127.0.0.1").toString();
    quint16 port = settings.value("OPTIONS/PORT", 11900).toInt();

    this->socket->connectToHost(ip,port);
    qDebug() << "Address "<<ip<<":"<<port;

    if( this->socket->waitForConnected(500) ) {
       qDebug() << "Connected"  ;
       this->socket->write("HELLO SERVER[/TCP]");
       this->socket->flush();
    }

    this->timerDots = new QTimer();
    this->timerDots->connect(this->timerDots, SIGNAL(timeout()),this, SLOT(updateDots()));
    this->timerDots->start(500);

    this->timerButt = new QTimer();
    this->timerButt->connect(this->timerButt, SIGNAL(timeout()),this, SLOT(changeBG()));

    this->timerGpio = new QTimer();
    this->timerGpio->connect(this->timerGpio, SIGNAL(timeout()),this, SLOT(readGPIO()));


    this->dataTab[0]=0;
    this->dataTab[1]=0;
    this->dataTab[2]=0;
    this->dataTab[3]=0;

    ui->setupUi(this);

    this->sbTree = ui->textEditTree->verticalScrollBar();
    this->sbTree->setValue(this->sbTree->maximum());

    this->sbHerbi = ui->textEditHerbi->verticalScrollBar();
    this->sbHerbi->setValue(this->sbHerbi->maximum());

    this->sbCarni = ui->textEditCarni->verticalScrollBar();
    this->sbCarni->setValue(this->sbCarni->maximum());

    this->sbBrut = ui->textEditBrut->verticalScrollBar();
    this->sbBrut->setValue(this->sbBrut->maximum());

    this->sbInvad = ui->textEditInvad->verticalScrollBar();
    this->sbInvad->setValue(this->sbInvad->maximum());

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
    ui->textEditInvad->setFont(Greenscr);

    this->timerGpio->start(250);

}


void MainWindowLifeGame::readTcpData()
{
    QRegExp Tnbr("Tree NBR ([0-9]+)");
    QRegExp Herbr("Herbi NBR ([0-9]+)");
    QRegExp Carbr("Carni NBR ([0-9]+)");
    QRegExp Invbr("Invad NBR ([0-9]+)");
    QRegExp YearBr("YEAR ([0-9]+)");

    QString data =  this->socket->readAll();
    //this->socket->flush();

    ui->textEditBrut->setText(ui->textEditBrut->toPlainText()+">"+data);
    this->sbBrut->setValue(sbBrut->maximum());

    //qDebug() << Tnbr.indexIn(data);
    if(Tnbr.indexIn(data)==0)
    {
        this->dataTab[0]=Tnbr.cap(1).toInt() / 10.0;
        ui->textEditTree->setText(ui->textEditTree->toPlainText()+"\n"+Tnbr.cap(1));
        this->sbTree->setValue(sbTree->maximum());
    }

    if(Herbr.indexIn(data)==0)
    {
        this->dataTab[1]=Herbr.cap(1).toInt();
        ui->textEditHerbi->setText(ui->textEditHerbi->toPlainText()+"\n"+Herbr.cap(1));
        this->sbHerbi->setValue(sbHerbi->maximum());
    }

    if(Carbr.indexIn(data)==0)
    {
        this->dataTab[2]=Carbr.cap(1).toInt();
        ui->textEditCarni->setText(ui->textEditCarni->toPlainText()+"\n"+Carbr.cap(1));
        this->sbCarni->setValue(sbCarni->maximum());
    }

    if(Invbr.indexIn(data)==0)
    {
        this->dataTab[3]=Invbr.cap(1).toInt();
        ui->textEditInvad->setText(ui->textEditInvad->toPlainText()+"\n"+Invbr.cap(1));
        this->sbInvad->setValue(sbInvad->maximum());
    }

    if(YearBr.indexIn(data)==0)
    {
        ui->labelYear->setText("Annee : "+YearBr.cap(1));
    }

    //qDebug() << this->dataTab[0] << " - " << this->dataTab[1] << " - " << this->dataTab[2] << "\n";
    int sumD = this->dataTab[0]+this->dataTab[1]+this->dataTab[2]+this->dataTab[3];
    ui->progressBarTree->setValue((int)((double)(this->dataTab[0]/(float)sumD)*100.0f));
    ui->progressBarHerbi->setValue((int)((double)(this->dataTab[1]/(float)sumD)*100.0f));
    ui->progressBarCarni->setValue((int)((double)(this->dataTab[2]/(float)sumD)*100.0f));
    ui->progressBarInvade->setValue((int)((double)(this->dataTab[3]/(float)sumD)*100.0f));
}

void MainWindowLifeGame::readGPIO()
{
   if(this->rpiGpio->readPin(this->pinNumIn) == mmapGpio::HIGH){
       this->pushButton();
   }
}

void MainWindowLifeGame::pushButton()
{
    if(!this->timerButt->isActive()){
        QString d = "PUSH But[/TCP]";
        qDebug() << d;
        this->socket->write(d.toStdString().c_str());
        this->socket->flush();
        ui->centralWidget->setStyleSheet("QWidget#centralWidget{border-image: url(:/data/bgRed.png) 0 0 0 0 stretch stretch;}");
        this->timerButt->start(4000);
    }
}

void MainWindowLifeGame::changeBG()
{
     ui->centralWidget->setStyleSheet("QWidget#centralWidget{border-image: url(:/data/bg.png) 0 0 0 0 stretch stretch;}");
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
