#ifndef PRMONKEY_H
#define PRMONKEY_H
#include "prplayer.h"
class PrMonkey : public PrPlayer
{
    Q_OBJECT
public:
    explicit PrMonkey(Game*, QObject *parent = 0);
signals:
    
public slots:
    void animateWrong();
    void getMove();
};

#endif // PRMONKEY_H
