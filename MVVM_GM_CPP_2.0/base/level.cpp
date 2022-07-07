#include "level.h"
#include<time.h>
#include<stdlib.h>
#include<QDebug>
#include<QString>

Level::Level(int pn, int mn){
    player_num = pn;
    for(int i=1; i<=pn; ++i){
        player[i] = new Player(i, pn);
    }
    map.mapInit(mn);

}

void Level::HookDown(int idx){
    Player *ply;
    ply = GetPlayer(idx);
    ply->setState(M_LONG);
}

void Level::HookRotate(){
    int n = GetPlayerNum();
    Player *ply;
    for(int i=1; i<=n; ++i){
        ply = GetPlayer(i);
        ply -> hookRock();
//        NotifyHook(i-1, ply->getendx(), ply->getendy(), ply->getAngle(), ply->getState());

    }
}
void Level::HookMove(){
//    exit(0);
    int n = GetPlayerNum();
    Player *ply;
    for(int i=1; i<=n; ++i){
        ply = GetPlayer(i);
        ply->HookMove();
//        NotifyHook(i-1, ply->getendx(), ply->getendy(), ply->getAngle(), ply->getState());
    }
}

void Level::JudgeFetch(){
    int n = GetPlayerNum();
    Player *ply;
    for(int i=1; i<=n; ++i){
        ply = GetPlayer(i);
        ply->JudgeGrap(GetMines(), GetMineNum());
//        NotifyHook(i-1, ply->getendx(), ply->getendy(), ply->getAngle(), ply->getState());
    }
}
