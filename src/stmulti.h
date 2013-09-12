#ifndef STMULTI_H
#define STMULTI_H
#include "ststone.h"
class StMulti : public StStone
{
    Q_OBJECT
public:
    explicit StMulti(QWidget *parent = 0);
    bool matches(StStone *){
        return true;
    }
    void setColor(StColor){return;}
    void changeColor(){return;}
    int getValue(){return 0;}
signals:
    
public slots:
    
};

#endif // STMULTI_H
