#ifndef PARAMCURVEANIMATION_H
#define PARAMCURVEANIMATION_H

#include <QObject>
#include <QtGui>

enum ParamCurves{
    Tremble
};

class ParamCurveAnimation : public QObject
{
    Q_OBJECT
public:
    explicit ParamCurveAnimation(QObject *parent = 0);
    void add(QWidget* w);
    QPoint tremble (int);
protected:
    QList<QWidget*> data;
    QList<QPoint> dataStartPos;
    void timerEvent(QTimerEvent *event);
    ParamCurves current;
    int timerId;
    int t;
    bool animating;
    int duration;
signals:
    void ended();
public slots:
    void animate(ParamCurves, int duration);
    
};

#endif // PARAMCURVEANIMATION_H
