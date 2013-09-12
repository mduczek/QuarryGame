#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "prhuman.h"
#include "prcomputer.h"
#include "prmonkey.h"

#include <QtAlgorithms>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setWindowTitle("Quarry");
    gm =0;
    QTime midnight(0, 0, 0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    this->ui->mainToolBar->hide();
    scoreOne = new QLabel(this);
    scoreTwo = new QLabel(this);
    scoreOne->setGeometry(10,0,50,30);
    scoreOne->setAlignment(Qt::AlignCenter);
    scoreTwo->setAlignment(Qt::AlignCenter);
    scoreTwo->setGeometry(this->width()-60,0,50,30);
    this->setFixedSize(360,360);
    ui->options->hide();
    ui->statusBar->hide();
    ui->options->move(0,0);
    endGame = new QPushButton("End",this);
    endGame->adjustSize();
    endGame->hide();
    connect(endGame,SIGNAL(clicked()),this,SLOT(endGameSlot()));
    getProbs();
    ui->closeHigh->hide();
    ui->highScoresLabel->hide();
}
void MainWindow::setupGame(){
    if(gm!=0){
        delete gm;
        gm = 0;
    }
    gm = new Game(this);
    gm->move(0,scoreOne->height());

    scoreOne->setText("0");
    scoreTwo->setText("0");
    gm->colorNum = ui->colorsSlider->value();
    StStone::colorNum =ui->colorsSlider->value();
    gm->boardSize = ui->boardSlider->value();
    scoreTwo->move(StStone::size*gm->boardSize-60,0);
    endGame->move((StStone::size*gm->boardSize-endGame->width())/2,5);
    this->setFixedSize(StStone::size*gm->boardSize,StStone::size*gm->boardSize+scoreOne->height());
    gm->setFixedSize(StStone::size*gm->boardSize,StStone::size*gm->boardSize);
    getProbs();
    if(gm->boardSize>5)
        multiProb *= 5.0/gm->boardSize;

    for(int i=80; i<90; i++)
        gm->probabilites[i] = Mud;
    for(int i=10+multiProb+fragileProb+morphProb; i<80; i++){
        gm->probabilites[i] = Normal;
    }
    for(int i=10+multiProb+fragileProb; i<10+multiProb+fragileProb+morphProb; i++)
        gm->probabilites[i] = Morph;
    for(int i=10+multiProb; i <10+multiProb+fragileProb; i++)
        gm->probabilites[i] = Fragile;
    for(int i=10; i<10+multiProb; i++)
        gm->probabilites[i] = Multi;
    for(int i=0; i<10; i++){
        gm->probabilites[i] = Gold;
    }
    StStone::initialise();
    gm->fillBoard();
    gm->hide();
    endGame->show();
    endGame->raise();
    ui->title->hide();
    connect(gm,SIGNAL(newTurn()),this,SLOT(newTurn()));

}
void MainWindow::changeScore(int score, PrPlayer *player){
    if(player == gm->playerOne){
        scoreOne->setText(QString::number(score));
    }else{
        scoreTwo->setText(QString::number(score));
    }
}
void MainWindow::newTurn(){
    if(gm->playerOneTurn || gm->playerOne== gm->playerTwo){
        qDebug("one");
        QFont bfont;
        bfont.setBold(true);
        scoreOne->setFont(bfont);
        QFont ffont;
        scoreTwo->setFont(ffont);
    }else{
        qDebug("two");
        QFont bfont;
        bfont.setBold(true);
        scoreTwo->setFont(bfont);
        QFont ffont;
        scoreOne->setFont(ffont);
    }
}

void MainWindow::endGameSlot(){
    endGame->hide();
    this->setFixedSize(360,360);
    gm->hide();
    scoreOne->hide();
    scoreTwo->hide();
    if(gm->playerOne==gm->playerTwo){
        QFile scores("scores.txt");
        if (!scores.open(QIODevice::Append | QIODevice::Text))
            return;
        QTextStream scStrm(&scores);
        scStrm << scoreOne->text() << "\n";
    }
    ui->title->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_opttionsBtn_clicked()
{
    ui->options->show();
    ui->highscores->hide();
    this->setFixedSize(250,590);
}


void MainWindow::on_playBtn_clicked()
{
    setupGame();
    scoreOne->show();
    scoreTwo->show();
    gm->playerOne = new PrHuman(gm);
    gm->playerTwo = new PrHuman(gm);
    connect(gm->playerOne,SIGNAL(scoreChanged(int,PrPlayer*)),this,SLOT(changeScore(int,PrPlayer*)));
    connect(gm->playerTwo,SIGNAL(scoreChanged(int,PrPlayer*)),this,SLOT(changeScore(int,PrPlayer*)));
    gm->show();
    timerId = this->startTimer(1000);
}
void MainWindow::timerEvent(QTimerEvent *event){
    gm->start();
    this->killTimer(timerId);
}

void MainWindow::on_playBtn_2_clicked()
{
    setupGame();
    scoreOne->show();
    scoreTwo->hide();
    gm->playerOne = new PrHuman(gm);
    gm->playerTwo = gm->playerOne;
    connect(gm->playerOne,SIGNAL(scoreChanged(int,PrPlayer*)),this,SLOT(changeScore(int,PrPlayer*)));
    gm->show();
    timerId = this->startTimer(1000);
}

void MainWindow::on_playBtn_3_clicked()
{
    setupGame();
    scoreOne->show();
    scoreTwo->show();
    gm->playerOne = new PrHuman(gm);
    if(ui->computerCh->value()==0)
        gm->playerTwo = new PrMonkey(gm);
    else
        gm->playerTwo = new PrComputer(gm);
    connect(gm->playerOne,SIGNAL(scoreChanged(int,PrPlayer*)),this,SLOT(changeScore(int,PrPlayer*)));
    connect(gm->playerTwo,SIGNAL(scoreChanged(int,PrPlayer*)),this,SLOT(changeScore(int,PrPlayer*)));
    gm->show();
    timerId = this->startTimer(1000);
}

void MainWindow::on_pushButton_clicked()
{
    ui->options->hide();
    ui->highscores->show();
    this->setFixedSize(360,360);

}
void MainWindow::getProbs(){

    morphProb = ui->kameleonProb->value()*5;
    qDebug()<<morphProb;
    multiProb = ui->jokerProb->value();
    switch(multiProb){
    case 0:
        multiProb = 0;
        break;
    case 1:
        multiProb = 3;
        break;
    case 2:
        multiProb = 5;
        break;
    case 3:
        multiProb = 10;
        break;
    }

    fragileProb = ui->kelpsydraProb->value()*5;
}

void MainWindow::on_highscores_clicked()
{
    ui->highScoresLabel->show();
    ui->closeHigh->show();
    QFile scores("scores.txt");

    if (scores.open(QIODevice::ReadOnly | QIODevice::Text)){
        QVector<int> best;
        QString scoresStr="Highscores: \n";
        QTextStream scStrm(&scores);
        while(!scStrm.atEnd())
           best.append(scStrm.readLine().toInt());
        qSort(best);
        for(int i=best.size()-1; i>=0 && i>=best.size()-10 ; i--)
            scoresStr += QString::number(best[i]) + "\n";
        ui->highScoresLabel->setText(scoresStr);
    }else{
        ui->highScoresLabel->setText("Highscores: \n");
    }
}



void MainWindow::on_closeHigh_clicked()
{
    ui->closeHigh->hide();
    ui->highScoresLabel->hide();
}
