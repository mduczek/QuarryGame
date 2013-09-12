#include "prcomputer.h"

PrComputer::PrComputer(Game * gme, QObject *parent) :
    PrPlayer(gme,parent)
{
}
void PrComputer::getMove(){
    qDebug("AI");
    gm->setEnabled(false);
    int max=-1;
    MoveData best;
    int tempScore=0;
    PrPlayer tempP(this->gm);
    for(int j = 0; j<gm->boardSize;j++){
        MoveData t;
        t.y1 = j;
        for(int i=0; i<gm->boardSize; i++){
            t.x1 = i;
            t.x2 = t.x1;
            t.y2 = t.y1;
            //E
            t.x2++;
            tempScore = tempP.score;
            if(tempP.evaluate(t) && (tempP.score-tempScore)>max){
                best = t;
                max = tempP.score-tempScore;
            }
            t.x2 = t.x1;
            //S
            t.y2++;
            tempScore = tempP.score;
            if(tempP.evaluate(t) && (tempP.score-tempScore)>max){
                best = t;
                max = tempP.score-tempScore;
            }
            t.y2 = t.y1;
        }
    }
    if(max==-1){
        emit movesEnded();
    }else{
        this->evaluate(best,EvalMove);
    }
}
void PrComputer::animateWrong(){
    return;
}
