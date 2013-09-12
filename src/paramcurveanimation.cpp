#include "paramcurveanimation.h"

ParamCurveAnimation::ParamCurveAnimation(QObject *parent) :
    QObject(parent)
{
    t=0;
    duration=0;
}
void ParamCurveAnimation::add(QWidget* w){
    if(!animating){
        data.push_back(w);
    }
}
void ParamCurveAnimation::animate(ParamCurves f, int duration){
    timerId = this->startTimer(80);
    this->duration = duration;
    current = f;
    animating = true;
   for(int i=0; i<data.size();i++){
       dataStartPos.append(data.at(i)->pos());
   }
}
void ParamCurveAnimation::timerEvent(QTimerEvent *event){
    if(t<duration){
        t++;
        for(int i=0; i<data.size();i++){
            if(current == Tremble)
                data.at(i)->move(tremble(t)+dataStartPos.at(i));
        }
    }else{
        this->killTimer(timerId);
        data.clear();
        t=0;
        animating=false;
        dataStartPos.clear();
        emit ended();
    }
}
QPoint ParamCurveAnimation::tremble (int t){
    return QPoint::QPoint((int) 3*cos(3*t),(int) 3*sin(5*t));
}
