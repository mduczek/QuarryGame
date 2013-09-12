#include "game.h"

Game::Game(QWidget *parent) :
    QWidget(parent)
{
    anim = new Animator(this);
    animCurve = new ParamCurveAnimation(this);
    anim->accelerationX =0;
    anim->accelerationY = 3;
    playerOneTurn = (bool) (qrand() % 2);
    connect(anim,SIGNAL(ended()),this,SLOT(gravityFinished()));
    connect(animCurve,SIGNAL(ended()),this,SLOT(gravity()));
    this->setAutoFillBackground(true);

}
void Game::start(){
    emit newTurn();
    if(playerOneTurn){
        playerOne->getMove();
    }else{
        playerTwo->getMove();
    }
}
void Game::gravityFinished(){
    PrPlayer* player;
    if(playerOneTurn){
        player = playerOne;
    }else{
        player = playerTwo;
    }
    QVector<QVector<bool > > visited (boardSize);
    for(int i=0; i<boardSize; i++)
        visited[i].fill(false,boardSize);
    bool foundTriple = false;
    for(int i =0; i<boardSize; i++)
        for(int j=0; j<boardSize; j++){
            MoveData mv;
            mv.x1 = i;
            mv.x2 = i;
            mv.y1 = j;
            mv.y2 = j;
            foundTriple = player->evaluate(mv,EvalForGravity,visited) || foundTriple;
        }
    if(foundTriple){
        animateCrushStones();
    }else{
        playerOneTurn = !playerOneTurn;
        start();
    }
}

void Game::gravity(){
    PrPlayer* player;
    if(playerOneTurn){
        player = playerOne;
    }else{
        player = playerTwo;
    }
    for(int i=0; i<player->stonesToCrush.size();i++){
        int x = player->stonesToCrush.at(i).first;
        int y = player->stonesToCrush.at(i).second;
        StStone* st  = board[x][y];
        board[x][y] = 0;
        if(st!=0)
            delete st;
    }
    player->stonesToCrush.resize(0);
    int maxDy = 0;
    //setup animation
    for(int i=0; i<boardSize; i++){
        int dy = 0;
        for(int j=boardSize-1; j>=0; j--){
            StStone* st = board[i][j];
            if(st == 0){
                dy++;
            }else{
                QPoint p = st->pos();
                p.setY(p.y()+dy*StStone::size);
                if(dy!=0){
                    board[i][j+dy] =  board[i][j];
                    board[i][j] = 0;
                    anim->add(board[i][j+dy],p);
                }
            }
        }
        if(dy>maxDy)
            maxDy = dy;
    }
    QVector<QPair<int,int> > stonesAdded;
    //create new stones and animate them
    for(int i=0; i<boardSize; i++){
        int z=0;
        while( z < boardSize && board[i][z]==0 ){
            z++;
        }
        for(int j=0; j<z; j++){
            StStone* st = makeStone();
            st->show();
            board[i][j] = st;
            stonesAdded.append(qMakePair(i,j));
            st->move(i*StStone::size, (-maxDy+j)*StStone::size);
            QPoint p;
            p.setX(i*StStone::size);
            p.setY(j*StStone::size);
            anim->add(board[i][j],p);
        }
    }
    //Anti-infinite-block-from-sky-falling
    if(boardSize>4){
        PrPlayer tempPlayer (this);
        for(int k=0; k<stonesAdded.size(); k++){
            MoveData mv;
            int i = stonesAdded.at(k).first;
            int j = stonesAdded.at(k).second;
            mv.x1 = i;
            mv.x2 = i;
            mv.y1 = j;
            mv.y2 = j;
            if(tempPlayer.evaluate(mv)){
                board[i][j]->changeColor();
            }
        }
    }
    if(boardSize<4){
        PrPlayer tempPlayer (this);
        for(int k=0; k<stonesAdded.size(); k++){
            MoveData mv;
            int i = stonesAdded.at(k).first;
            int j = stonesAdded.at(k).second;
            mv.x1 = i;
            mv.x2 = i;
            mv.y1 = j;
            mv.y2 = j;
            if(!tempPlayer.evaluate(mv)){
                board[i][j]->changeColor();
            }
        }
    }
    anim->animate();
}

void Game::animateCrushStones(){
    PrPlayer* player;
    if(playerOneTurn){
        player = playerOne;
    }else{
        player = playerTwo;
    }
    for(int i=0; i<player->stonesToCrush.size();i++){
        int x = player->stonesToCrush.at(i).first;
        int y = player->stonesToCrush.at(i).second;
        StStone* st  = board[x][y];
        animCurve->add(st);
    }
    //Fragile
    for(int i=0;i<boardSize;i++)
        for(int j=0; j<boardSize;j++)
            if(board[i][j]->toBeDeleted()){
                player->stonesToCrush.append(qMakePair(i,j));
                animCurve->add(board[i][j]);
            }
    animCurve->animate(Tremble,15);
}

void Game::fillBoard(){
    board.resize(boardSize);
    for(int i=0; i<boardSize; i++){
        board[i].resize(boardSize);
        for(int j=0; j<boardSize; j++){
            board[i][j] = makeStone();
            board[i][j]->move(i*StStone::size, j*StStone::size);
        }
    }
    //do so it will be good
    for(int i=0; i<boardSize; i++){
        for(int j=0; j<boardSize; j++){
            MoveData mv;
            mv.x1 = i;
            mv.x2 = i;
            mv.y1 = j;
            mv.y2 = j;
            PrPlayer tempPlayer (this);
            for(int z=0; z< StStone::colorNum && tempPlayer.evaluate(mv);z++){
                board[i][j]->setColor(StStone::colors[z]);
            }
        }
    }
}
StStone* Game::makeStone(){
    int prob = qrand() % 100;
    StTypes stoneType = probabilites[prob];
    StStone* st;
    switch(stoneType){
    case Fragile :
        st = new StFragile(this);
        connect(this,SIGNAL(newTurn()),st,SLOT(newTurn()));
        break;
    case Gold :
        st = new StGold(this);
        break;
    case Morph :
        st = new StMorph(this);
        connect(this,SIGNAL(newTurn()),st,SLOT(newTurn()));
        break;
    case Mud :
        st = new StMud(this);
        break;
    case Multi :
        st = new StMulti(this);
        break;
    default:
        st = new StStone(this);
        break;
    }
    connect(st,SIGNAL(clicked(StStone*)),this,SLOT(clickedStone(StStone*)));
    return st;
}
void Game::clickedStone(StStone *me){
    PrPlayer* player;
    if(playerOneTurn){
        player = playerOne;
    }else{
        player = playerTwo;
    }
    player->chosenStone(me);
}
