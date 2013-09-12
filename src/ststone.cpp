#include "ststone.h"

StStone::StStone(QWidget *parent) :
    QWidget(parent)
{
    pict = 0;
    this->setFixedSize(size,size);
    setColor( colors[(qrand() % colorNum) ]);
}
StColor StStone::colors [6] = {0,0,0,0,0,0};
int StStone::colorNum = 5;

void StStone::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0,0,*pict);
}
void StStone::mouseReleaseEvent(QMouseEvent *){
    emit clicked(this);
}

void StStone::initialise(){
    StColor color;
    color.path = ":/images/black.png";
    color.value = 5;
    colors[3] = color;
    StColor color1;
    color1.path = ":/images/yellow.png";
    color1.value = 3;
    colors[1]=color1;
    StColor color2;
    color2.path = ":/images/white.png";
    color2.value = 2;
    colors[0]=color2;
    StColor color3;
    color3.path = ":/images/gray.png";
    color3.value = 4;
    colors[2]=color3;
    StColor color4;
    color4.path = ":/images/red.png";
    color4.value = 5;
    colors[4] = color4;
    StColor color5;
    color5.path = ":/images/mud.png";
    color5.value = 1;
    colors[5] = color5;
}

bool StStone::matches(StStone * st){
    return (this->color.path == st->color.path || st->color.path=="multi");
}
int StStone::multiplyer(){
    return 1;
}
void StStone::setColor(StColor cl){
    this->color = cl;
    if(pict==0){
        pict = new QPixmap(color.path);
    }else{
        delete pict;
        pict = new QPixmap(color.path);
    }
    this->update();
}
void StStone::changeColor(){
    StColor cl = color;
    while(cl.path == color.path){
        cl = colors[qrand() % colorNum];
    }
    setColor(cl);
}

int StStone::getValue(){
    return this->color.value;
}
