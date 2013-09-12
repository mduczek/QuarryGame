#include "stmud.h"

StMud::StMud(QWidget *parent) :
    StStone(parent)
{
    skull = QPixmap::QPixmap(":/images/skull.png");
}

void StMud::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0,0,*pict);
    painter.drawPixmap(0,0,skull);
}
