#ifndef STMORPH_H
#define STMORPH_H

#include "ststone.h"

class StMorph : public StStone
{
    Q_OBJECT
public:
    explicit StMorph(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);
    QPixmap morph;
signals:
    
public slots:
    void newTurn(){qDebug("change"); changeColor();}
};

#endif // STMORPH_H
