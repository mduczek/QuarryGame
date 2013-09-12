#include "stmulti.h"

StMulti::StMulti(QWidget *parent) :
    StStone(parent)
{
    pict = new QPixmap(":/images/multi.png");
    StColor cl;
    cl.path = "multi";
    this->color = cl;
}
