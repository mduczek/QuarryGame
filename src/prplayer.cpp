#include "prplayer.h"
#include <QtCore/QPropertyAnimation>
#include <QtCore/QParallelAnimationGroup>
#include <QtCore/QSequentialAnimationGroup>

PrPlayer::PrPlayer(Game * gme, QObject *parent) :
    QObject(parent)
{
    gm = gme;
    score =0;
}

bool PrPlayer::evaluate(MoveData mv, EvaluateFlag flag, QVector<QVector<bool> > &visited){
    bool board = false;
    if(mv.x1==mv.x2 && mv.y1 == mv.y2)
        board = true;
    if(visited == PrPlayer::emptyV){
        visited = QVector<QVector<bool> >::QVector<QVector<bool> >(gm->boardSize);;
        for(int i=0; i<gm->boardSize; i++)
            visited[i].resize(gm->boardSize);
    }
    if(!posOk(mv.x1) || !posOk(mv.x2) ||
       !posOk(mv.y1) || !posOk(mv.y2) ||
       (abs(mv.x1-mv.x2)>1 && !board) || (abs(mv.y1-mv.y2)>1 && !board))
        return false;
    if(gm->board[mv.x1][mv.y1]==0 || gm->board[mv.x2][mv.y2]==0)
        return false;
    if(flag !=EvalForGravity)
        stonesToCrush.resize(0);
    StStone* st1 = gm->board[mv.x1][mv.y1];
    StStone* st2 = gm->board[mv.x2][mv.y2];
    if(st1!=st2 && st1->color.path == st2->color.path)
        return false;
    gm->board[mv.x1][mv.y1] = st2;
    gm->board[mv.x2][mv.y2] = st1;
    stonesOne.resize(0);
    stonesTwo.resize(0);

    stonesOne.append(qMakePair(mv.x2,mv.y2));
    dfs(mv.x2,mv.y2,visited,stonesOne);
    if(!board){
        stonesTwo.append(qMakePair(mv.x1,mv.y1));
        dfs(mv.x1,mv.y1,visited,stonesTwo);
    }
    this->evalFlag = flag;
    if(stonesOne.size()>=3 || stonesTwo.size()>=3){
        if(!board && flag == EvalMove)
            animateMove();
        else if(flag == EvalForGravity){
            endMove();
        }else if(!board && flag == JustEval){
            endMove();
            gm->board[mv.x1][mv.y1] = st1;
            gm->board[mv.x2][mv.y2] = st2;
        }

        return true;
    }else{
        //reverse change
        if(!board && flag == EvalMove)
            animateWrong();
        gm->board[mv.x1][mv.y1] = st1;
        gm->board[mv.x2][mv.y2] = st2;
        return false;
    }
}

void PrPlayer::endMove(){
    if(stonesOne.size()>=3)
        evaluateStones(stonesOne);
    if(stonesTwo.size()>=3)
        evaluateStones(stonesTwo);
    if(evalFlag == EvalMove)
        gm->animateCrushStones();
}

void PrPlayer::dfs(int x, int y, QVector<QVector<bool> > &visited, QVector<QPair<int, int> > &stones){
    StStone * st = gm->board[x][y];
    if(st == 0)
        return;
    visited[x][y] = true;
    //N
    if(posOk(y-1) && visited[x][y-1] == false && st->matches(gm->board[x][y-1])){
        stones.append(qMakePair(x,y-1));
        dfs(x,y-1,visited,stones);
    }
    //S
    if(posOk(y+1) && visited[x][y+1] == false && st->matches(gm->board[x][y+1])){
        stones.append(qMakePair(x,y+1));
        dfs(x,y+1,visited,stones);
    }
    //E
    if(posOk(x+1) && visited[x+1][y] == false && st->matches(gm->board[x+1][y])){
        stones.append(qMakePair(x+1,y));
        dfs(x+1,y,visited,stones);
    }
    //W
    if(posOk(x-1) && visited[x-1][y] == false && st->matches(gm->board[x-1][y])){
        stones.append(qMakePair(x-1,y));
        dfs(x-1,y,visited,stones);
    }
}

void PrPlayer::evaluateStones(QVector<QPair<int, int> > &stones){
    int value = 0;
    int multiplyer = 1;
    if(stones.size()>=3){
        for(int i=0; i< stones.size(); i++){
            stonesToCrush.append(stones.at(i));
            StStone* st = gm->board[stones[i].first][stones[i].second];
            value += st->getValue();
            multiplyer *= st->multiplyer();
        }
    }
    score += multiplyer*value;
    emit scoreChanged((int) score, this);
}

bool PrPlayer::posOk(int x){
    return (x >= 0 && x<gm->boardSize);
}

QVector<QVector<bool> > PrPlayer::emptyV = QVector<QVector<bool> >::QVector<QVector<bool> >(0);

//Animations------------------------------------------------------------------------
void PrPlayer::animateMove( ){
    StStone* one = gm->board[stonesOne.first().first][stonesOne.first().second];
    StStone* two = gm->board[stonesTwo.first().first][stonesTwo.first().second];
    QPropertyAnimation* anim1 = new QPropertyAnimation(one, "geometry");
    anim1->setDuration(1000);
    anim1->setStartValue(QRect(one->x(), one->y(), one->width(), one->height()));
    anim1->setEndValue(QRect(two->x(), two->y(), one->width(), one->height()));

    QPropertyAnimation* anim2 = new QPropertyAnimation(two, "geometry");
    anim2->setDuration(1000);
    anim2->setStartValue(QRect(two->x(), two->y(), two->width(), two->height()));
    anim2->setEndValue(QRect(one->x(), one->y(), two->width(), two->height()));

    QParallelAnimationGroup *group = new QParallelAnimationGroup();
    group->addAnimation(anim1);
    group->addAnimation(anim2);
    group->start(QAbstractAnimation::DeleteWhenStopped);
    connect(group,SIGNAL(finished()),this,SLOT(endMove()));
}
void PrPlayer::animateWrong(){
    StStone* one = gm->board[stonesOne.first().first][stonesOne.first().second];
    StStone* two = gm->board[stonesTwo.first().first][stonesTwo.first().second];
    int dx = one->x() - two->x();
    int dy = one->y() - two->y();
    QPropertyAnimation* anim1 = new QPropertyAnimation(one, "geometry");
    anim1->setDuration(500);
    anim1->setStartValue(QRect(one->x(), one->y(), one->width(), one->height()));
    anim1->setEndValue(QRect(one->x()-dx/3, one->y()-dy/3, one->width(), one->height()));

    QPropertyAnimation* anim2 = new QPropertyAnimation(one, "geometry");
    anim2->setDuration(500);
    anim2->setStartValue(QRect(one->x()-dx/3, one->y()-dy/3, one->width(), one->height()));
    anim2->setEndValue(QRect(one->x(), one->y(), one->width(), one->height()));

    QSequentialAnimationGroup* group1 = new QSequentialAnimationGroup();

    group1->addAnimation(anim1);
    group1->addAnimation(anim2);

    QPropertyAnimation* anim3 = new QPropertyAnimation(two, "geometry");
    anim3->setDuration(500);
    anim3->setStartValue(QRect(two->x(), two->y(), two->width(), two->height()));
    anim3->setEndValue(QRect(two->x()+dx/3, two->y()+dy/3, two->width(), two->height()));

    QPropertyAnimation* anim4 = new QPropertyAnimation(two, "geometry");
    anim4->setDuration(500);
    anim4->setStartValue(QRect(two->x()+dx/3, two->y()+dy/3, two->width(), two->height()));
    anim4->setEndValue(QRect(two->x(), two->y(), two->width(), two->height()));

    QSequentialAnimationGroup* group2 = new QSequentialAnimationGroup();

    group2->addAnimation(anim3);
    group2->addAnimation(anim4);

    QParallelAnimationGroup *group = new QParallelAnimationGroup();
    group->addAnimation(group1);
    group->addAnimation(group2);
    group->start(QAbstractAnimation::DeleteWhenStopped);
    connect(group,SIGNAL(finished()),this,SLOT(getMove()));
}
