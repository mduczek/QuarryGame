#include "stmorph.h"

StMorph::StMorph(QWidget *parent) :
    StStone(parent)
{
    morph = QPixmap::QPixmap(":/images/morph.png");
}



void StMorph::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0,0,*pict);
    painter.drawPixmap(0,0,morph);
}
