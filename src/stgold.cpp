#include "stgold.h"

StGold::StGold(QWidget *parent) :
    StStone(parent)
{
    gold = QPixmap::QPixmap(":/images/gold.png");
    goldX = (qrand() % 10) + 5;
    goldY = (qrand() % 20) + 5;
}

void StGold::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0,0,*pict);
    painter.drawPixmap(goldX,goldY,gold);
}


