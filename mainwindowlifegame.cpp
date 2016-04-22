#include "mainwindowlifegame.h"
#include "ui_mainwindowlifegame.h"

MainWindowLifeGame::MainWindowLifeGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowLifeGame)
{
/*
export DISPLAY=":0.0"
xhost +
cd Desktop/ISIB_LifeGameClientV1/
sudo DISPLAY=:0 ./ISIB_LifeGameClient
*/
    this->rpiGpio = new mmapGpio();
    this->rpiGpio->setPinDir(this->pinNumIn,mmapGpio::INPUT);

   this->tnbr = new QRegExp ("Tree ([0-9]+)");
   this->herbr = new QRegExp ("Herbi ([0-9]+)");
   this->carbr  = new QRegExp ("Carni ([0-9]+)");
   this->invbr  = new QRegExp ("Invad ([0-9]+)");
   this->yearBr  = new QRegExp ("YEAR ([0-9]+)");


    int id = QFontDatabase::addApplicationFont("://data/Greenscr.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont Greenscr(family,18);

    this->socket = new QTcpSocket(this);
    this->connect(this->socket, SIGNAL(readyRead()), SLOT(readTcpData()));
    this->connect(this->socket, SIGNAL(disconnected()), SLOT(autoReconnect()));

    QSettings settings("conf.ini", QSettings::IniFormat);
    this->ip = settings.value("OPTIONS/IP","127.0.0.1").toString();
    this->port = settings.value("OPTIONS/PORT", 11900).toInt();


    //qDebug() << "Address "<<this->ip<<":"<<this->port;

    this->timerDots = new QTimer();
    this->timerDots->connect(this->timerDots, SIGNAL(timeout()),this, SLOT(updateDots()));
    this->timerDots->start(500);

    this->timerButt = new QTimer();
    this->timerButt->connect(this->timerButt, SIGNAL(timeout()),this, SLOT(changeBG()));

    this->timerGpio = new QTimer();
    this->timerGpio->connect(this->timerGpio, SIGNAL(timeout()),this, SLOT(readGPIO()));
    this->timerGpio->start(100);

    this->dataTab[0]=0;
    this->dataTab[1]=0;
    this->dataTab[2]=0;
    this->dataTab[3]=0;

    bool connected = false;
    while(!(connected)){
        this->socket->connectToHost(this->ip,this->port);
        if( this->socket->waitForConnected(5000) ) {
           this->socket->write("HELLO SERVER[/TCP]");
           this->socket->flush();
           connected = true;
        }
    }

    ui->setupUi(this);



    ui->label->setFont(Greenscr);
    ui->label->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed));
    ui->labelYear->setFont(Greenscr);
    ui->labelDotAnim->setFont(Greenscr);
    ui->labelArbre->setFont(Greenscr);
    ui->labelArbre_2->setFont(Greenscr);
    ui->labelArbre_3->setFont(Greenscr);
    ui->labelArbre_4->setFont(Greenscr);
    ui->progressBarTree->setFont(Greenscr);
    ui->progressBarHerbi->setFont(Greenscr);
    ui->progressBarCarni->setFont(Greenscr);
    ui->progressBarInvade->setFont(Greenscr);

    ui->textEditTree->setFont(Greenscr);
    ui->textEditHerbi->setFont(Greenscr);
    ui->textEditCarni->setFont(Greenscr);
    ui->textEditBrut->setFont(Greenscr);
    ui->textEditInvad->setFont(Greenscr);

    QMainWindow::showFullScreen();
    QApplication::setOverrideCursor(Qt::BlankCursor);

     /*this->sbHerbi = ui->textEditHerbi->verticalScrollBar();
     this->sbHerbi->setValue(this->sbHerbi->maximum());

     this->sbCarni = ui->textEditCarni->verticalScrollBar();
     this->sbCarni->setValue(this->sbCarni->maximum());

     this->sbBrut = ui->textEditBrut->verticalScrollBar();
     this->sbBrut->setValue(this->sbBrut->maximum());

     this->sbInvad = ui->textEditInvad->verticalScrollBar();
     this->sbInvad->setValue(this->sbInvad->maximum());

    this->sbTree = ui->textEditTree->verticalScrollBar();
    this->sbTree->setValue(this->sbTree->maximum());
*/

}

void MainWindowLifeGame::autoReconnect()
{
    ui->textEditTree->clear();
    ui->textEditHerbi->clear();
    ui->textEditCarni->clear();
    ui->textEditInvad->clear();

    ui->labelYear->setText("Annee : ");
    ui->progressBarTree->setValue(0);
    ui->progressBarHerbi->setValue(0);
    ui->progressBarCarni->setValue(0);
    ui->progressBarInvade->setValue(0);

    bool connected = false;
    while(!(connected)){
        this->socket->connectToHost(this->ip,this->port);
        if( this->socket->waitForConnected(5000) ) {
           this->socket->write("HELLO SERVER[/TCP]");
           this->socket->flush();
           connected = true;
        }
    }

}

void MainWindowLifeGame::readTcpData()
{

    data =  this->socket->readLine();
    this->socket->flush();

    ui->textEditBrut->setText(ui->textEditBrut->toPlainText()+">"+data);
    //this->sbBrut->setValue(sbBrut->maximum());
    if (ui->textEditBrut->toPlainText().size() > 170)
    {
        cursor = ui->textEditBrut->textCursor();
        cursor.setPosition(QTextCursor::Start);
        cursor.select(QTextCursor::BlockUnderCursor);
        cursor.removeSelectedText();
        cursor.deletePreviousChar();
        ui->textEditBrut->setTextCursor(cursor);
    }

    //qDebug() << ui->textEditBrut->toPlainText().size();
    if(this->tnbr->indexIn(data)==0)
    {
        this->dataTab[0]=this->tnbr->cap(1).toInt() / 10.0;
        ui->textEditTree->setText(this->tnbr->cap(1)+"\n"+ui->textEditTree->toPlainText());

        if (ui->textEditTree->toPlainText().size() > 60)
        {
            cursor = ui->textEditTree->textCursor();
            cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
            cursor.movePosition(QTextCursor::PreviousBlock, QTextCursor::MoveAnchor);
            //           cursor.setPosition(QTextCursor::End);
            cursor.select(QTextCursor::BlockUnderCursor);
            cursor.removeSelectedText();
            cursor.deletePreviousChar();
            ui->textEditTree->setTextCursor(cursor);

            /* cursor = ui->textEditTree->textCursor();
             cursor.setPosition(QTextCursor::Start);
             cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, 1);
             cursor.select(QTextCursor::LineUnderCursor);
             cursor.removeSelectedText();
             cursor.deletePreviousChar();
             ui->textEditTree->setTextCursor(cursor);*/
        }
        //qDebug() << ui->textEditTree->toPlainText().size();
        //this->sbTree->setValue(sbTree->maximum());
    }

    if(this->herbr->indexIn(data)==0)
    {
        this->dataTab[1]=this->herbr->cap(1).toInt();
        ui->textEditHerbi->setText(this->herbr->cap(1)+"\n"+ui->textEditHerbi->toPlainText());
        if (ui->textEditHerbi->toPlainText().size() > 60)
        {
            cursor = ui->textEditHerbi->textCursor();
            cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
            cursor.movePosition(QTextCursor::PreviousBlock, QTextCursor::MoveAnchor);

            cursor.select(QTextCursor::BlockUnderCursor);
            cursor.removeSelectedText();
            cursor.deletePreviousChar();
            ui->textEditHerbi->setTextCursor(cursor);
        }
        //this->sbHerbi->setValue(sbHerbi->maximum());
    }

    if(this->carbr->indexIn(data)==0)
    {
        this->dataTab[2]=this->carbr->cap(1).toInt();
        ui->textEditCarni->setText(this->carbr->cap(1)+"\n"+ui->textEditCarni->toPlainText());
        if (ui->textEditCarni->toPlainText().size() > 60)
        {
            cursor = ui->textEditCarni->textCursor();
            cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
            cursor.movePosition(QTextCursor::PreviousBlock, QTextCursor::MoveAnchor);

            cursor.select(QTextCursor::BlockUnderCursor);
            cursor.removeSelectedText();
            cursor.deletePreviousChar();
            ui->textEditCarni->setTextCursor(cursor);
        }
        //this->sbCarni->setValue(sbCarni->maximum());
    }

    if(this->invbr->indexIn(data)==0)
    {
        this->dataTab[3]=this->invbr->cap(1).toInt();
        ui->textEditInvad->setText(this->invbr->cap(1)+"\n"+ui->textEditInvad->toPlainText());
        if (ui->textEditInvad->toPlainText().size() > 60)
        {
            cursor = ui->textEditInvad->textCursor();
            cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
            cursor.movePosition(QTextCursor::PreviousBlock, QTextCursor::MoveAnchor);
            cursor.select(QTextCursor::BlockUnderCursor);
            cursor.removeSelectedText();
            ui->textEditInvad->setTextCursor(cursor);
        }
        //this->sbInvad->setValue(sbInvad->maximum());
    }



    if(this->yearBr->indexIn(data)==0)
    {
        ui->labelYear->setText("Annee : "+this->yearBr->cap(1));
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
   if(this->rpiGpio->readPin(this->pinNumIn) == mmapGpio::LOW){
       this->pushButton();
   }
}

void MainWindowLifeGame::pushButton()
{
    if(!this->timerButt->isActive()){
        QString d = "PUSH But[/TCP]";
        this->socket->write(d.toStdString().c_str());
        this->socket->flush();
        ui->centralWidget->setStyleSheet("QWidget#centralWidget{border-image: url(:/data/bgRed.png) 0 0 0 0 stretch stretch;}");
        this->timerButt->start(1000);
    }
}

void MainWindowLifeGame::changeBG()
{
     ui->centralWidget->setStyleSheet("QWidget#centralWidget{border-image: url(:/data/bg.png) 0 0 0 0 stretch stretch;}");
     this->timerButt->stop();
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
