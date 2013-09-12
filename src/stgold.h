#ifndef STGOLD_H
#define STGOLD_H

#include "ststone.h"

class StGold : public StStone
{
    Q_OBJECT
public:
    explicit StGold(QWidget *parent = 0);
    int multiplyer(){
        return 2;
    }
protected:
    void paintEvent(QPaintEvent *);
    QPixmap gold;
    int goldX;
    int goldY;
signals:
    
public slots:
    
};

#endif // STGOLD_H
