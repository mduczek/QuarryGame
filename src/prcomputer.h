#ifndef PRCOMPUTER_H
#define PRCOMPUTER_H
#include "prplayer.h"
class PrComputer : public PrPlayer
{
    Q_OBJECT
public:
    explicit PrComputer(Game*, QObject *parent = 0);
    
signals:
    
public slots:
    void animateWrong();
    void getMove();
};

#endif // PRCOMPUTER_H
