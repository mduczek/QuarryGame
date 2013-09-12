#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include "ststone.h"
#include "prplayer.h"
#include "stfragile.h"
#include "stgold.h"
#include "stmud.h"
#include "stmorph.h"
#include "stmulti.h"
#include "animator.h"
#include "paramcurveanimation.h"
class PrPlayer;

class Game : public QWidget
{
    Q_OBJECT
public:
    explicit Game(QWidget *parent = 0);
    Animator* anim;
    ParamCurveAnimation* animCurve;
    QVector<QVector<StStone* > > board;
    int colorNum;
    int boardSize;
    StTypes probabilites [100];
    PrPlayer* playerOne;
    PrPlayer* playerTwo;
    void fillBoard();
    bool playerOneTurn;
protected:
    StStone* makeStone();
signals:
    void newTurn();
public slots:
    void gravity();
    void start();
    void gravityFinished();
    void animateCrushStones();
    void clickedStone(StStone* me);
};

#endif // GAME_H
