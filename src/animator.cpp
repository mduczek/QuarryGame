#include "animator.h"

Animator::Animator(QObject *parent) :
    QObject(parent)
{
    this->setup();
}
void Animator::add(QWidget* w, QPoint endPos){
    if(!animating){
        data.push_back(qMakePair(w,endPos));
    }
}
void Animator::animate(){
    timerId = this->startTimer(80);
    animating = true;
}
void Animator::timerEvent(QTimerEvent *event){
    vX += accelerationX;
    vY += accelerationY;
    for(int i=data.length()-1; i>=0; i--){
        QWidget* w = data.at(i).first;
        QPoint p = w->pos();
        int end = 2;
        if((vX > 0 && p.x() + (int) vX < data.at(i).second.x() )||
           (vX < 0 && p.x() + (int) vX > data.at(i).second.x()))
            p.setX(p.x()+ (int) vX);
        else{
            p.setX(data.at(i).second.x());
            end--;
        }

        if((vY > 0 && p.y() + (int) vY < data.at(i).second.y() )||
           (vY < 0 && p.y() + (int) vY > data.at(i).second.y()))
            p.setY(p.y()+ (int) vY);
        else{
            p.setY(data.at(i).second.y());
            end--;
        }
        w->move(p);
        if(end==0){
            data.removeAt(i);
        }
    }
    if(data.length()==0){
        this->setup();
        emit ended();
    }
}
void Animator::setup(){
    vX =0;
    vY =0;
    animating = false;
    data.clear();
    this->killTimer(timerId);
}
