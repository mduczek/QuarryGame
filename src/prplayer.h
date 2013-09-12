#ifndef PRPLAYER_H
#define PRPLAYER_H

#include <QObject>
#include <QtGui>
#include "game.h"

class Game;
struct MoveData{
    int x1, y1, x2, y2;
};
enum EvaluateFlag{
    JustEval, EvalForGravity, EvalMove
};
enum PrState{
    WaitingForMove, Animating, Idle
};
class PrPlayer : public QObject
{
    Q_OBJECT
public:
    explicit PrPlayer(Game*, QObject *parent = 0);
    Game* gm;
    int score;
    //param exec : true -> modifyStones, false just evaluate and do nothing more
    bool evaluate(MoveData, EvaluateFlag flag = JustEval, QVector<QVector<bool> > &visited = emptyV);
    QVector<QPair<int, int> > stonesToCrush;
protected:
    void dfs(int x, int y, QVector<QVector<bool> > &visited, QVector<QPair<int, int> > &stones);
    //what should you do with a stone that matches
    void modifyStones(StStone*);
    //how do you want to eval stone
    void evaluateStones(QVector<QPair<int, int> > &stones);
    //if it is a correct board pos
    bool posOk(int);
    static QVector<QVector<bool> > emptyV;
    QVector<QPair<int, int> > stonesOne;
    QVector<QPair<int, int> > stonesTwo;
    void animateMove();
    virtual void animateWrong();
    //don't mess with either states!
    PrState state;
    EvaluateFlag evalFlag;
signals:
    void gotMove(MoveData);
    void movesEnded();
    void scoreChanged(int, PrPlayer*);
public slots:
    virtual void getMove(){return;}
    virtual void chosenStone(StStone*){return;}
protected slots:
    void endMove();
};



#endif // PRPLAYER_H
