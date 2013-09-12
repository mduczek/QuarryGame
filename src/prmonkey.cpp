#include "prmonkey.h"

PrMonkey::PrMonkey(Game * gme, QObject *parent) :
    PrPlayer(gme, parent)
{
}
void PrMonkey::getMove(){
    gm->setEnabled(false);
    bool notFound = true;
    int counter = 0;
    int limit = gm->boardSize*gm->boardSize*10;
    qDebug("SEARCHING");
    while(notFound && ++counter < limit){
        MoveData t;
        t.x1 = qrand() % gm->boardSize;
        bool eval = false;
        for(int i=0; i<gm->boardSize; i++){
            t.y1 = i;
            t.x2 = t.x1;
            t.y2 = t.y1;
            if(notFound){
                //N
                t.y2--;
                eval =  evaluate(t,EvalMove);
                if(eval)
                    notFound = false;
                else t.y2 = t.y1;
            }
            if(notFound){
                //E
                t.x2++;
                eval = evaluate(t,EvalMove);
                if(eval)
                    notFound = false;
                else t.x2 = t.x1;
            }
            if(notFound){
                //S
                t.y2++;
                eval = evaluate(t,EvalMove);
                if(eval)
                    notFound = false;
                else t.y2 = t.y1;
            }
            if(notFound){
                //W
                t.x2--;
                eval = evaluate(t,EvalMove);
                if(eval)
                    notFound = false;
                else t.x2 = t.x1;
            }
        }
    }
    if(counter >= limit){
        emit movesEnded();
        return;
    }
}
void PrMonkey::animateWrong(){
    return;
}
