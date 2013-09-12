#ifndef STMUD_H
#define STMUD_H
#include "ststone.h"
class StMud : public StStone
{
    Q_OBJECT
public:
    explicit StMud(QWidget *parent = 0);
    int multiplyer(){
        return 0;
    }
protected:
    void paintEvent(QPaintEvent *);
    QPixmap skull;
signals:
    
public slots:
    
};

#endif // STMUD_H
