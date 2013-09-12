#ifndef STFRAGILE_H
#define STFRAGILE_H

#include "ststone.h"

class StFragile : public StStone
{
    Q_OBJECT
public:
    explicit StFragile(QWidget *parent = 0);
    bool toBeDeleted(){
        return (t==4);
    }

protected:
    int t;
    void paintEvent(QPaintEvent *);
signals:
    
public slots:
    void newTurn(){
        if(t<=3){
            this->update();
            this->color.value--;
            t++;
        }
    }
};

#endif // STFRAGILE_H
