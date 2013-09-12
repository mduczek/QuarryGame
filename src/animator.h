#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <QObject>
#include <QtGui>

class Animator : public QObject
{
    Q_OBJECT
public:
    explicit Animator(QObject *parent = 0);
    void add(QWidget* w, QPoint endPos);
    float accelerationX;
    float accelerationY;
protected:
    void timerEvent(QTimerEvent *event);
private:
    float vX;
    float vY;
    int timerId;
    bool animating;
    QList<QPair< QWidget*, QPoint> > data;
    void setup();//resets animator
signals:
    void ended();
public slots:
    void animate();
};

#endif // ANIMATOR_H
