#include "stfragile.h"

StFragile::StFragile(QWidget *parent) :
    StStone(parent)
{
    t=0;
}
void StFragile::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0,0,*pict);
    if(t!=0){
        QString str = ":/images/crack" + QString::number((int) std::min(3,t)) + ".png";
        QPixmap crack = QPixmap::QPixmap(str);
        painter.drawPixmap(0,0,crack);
    }
}
