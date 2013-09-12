#ifndef PRHUMAN_H
#define PRHUMAN_H

#include "prplayer.h"

class PrHuman : public PrPlayer
{
    Q_OBJECT
public:
    explicit PrHuman(Game*, QObject *parent = 0);
protected:
    StStone* first;
    StStone* second;
    QPoint firstPos;
    QPoint secondPos;
signals:
    
public slots:
    void chosenStone(StStone * st){
        qDebug() << st->color.path;
        if(first==0){
            first = st;
        }else if(st != first){
            second = st;
        }
        if(second !=0){
            for(int i=0;i<gm->boardSize;i++)
                for(int j =0; j<gm->boardSize; j++){
                    if(gm->board[i][j]==first)
                        firstPos = QPoint::QPoint(i,j);
                    if(gm->board[i][j]==second)
                        secondPos = QPoint::QPoint(i,j);
                }
            MoveData mv;
            mv.x1 = firstPos.x();
            mv.x2 = secondPos.x();
            mv.y1 = firstPos.y();
            mv.y2 = secondPos.y();
            if((abs(mv.x1-mv.x2)==1 && mv.y1==mv.y2)||(abs(mv.y1-mv.y2)==1 && mv.x1==mv.x2)){
                if(evaluate(mv,EvalMove))
                    gm->setEnabled(false);
            }
            first = 0;
            second = 0;
        }
    }
    void getMove(){
        gm->setEnabled(true);
        qDebug("my move");
    }
};

#endif // PRHUMAN_H
