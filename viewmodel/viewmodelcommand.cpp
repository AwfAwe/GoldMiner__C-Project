#include "viewmodelcommand.h"

viewmodelcommand::viewmodelcommand(view* vw, int plynm, int mnnum): viewmodelctrl(plynm, mnnum){

}

void viewmodelcommand::GetAllMines(QVector<double>&mine_x, QVector<double>&mine_y, QVector<int>&mine_type, QVector<bool>&mine_flag){
    int n = GetMineNum();
    Mine* mines = GetMines();
    for(int i=0; i<n; ++i){
        mine_x.push_back(mines[i].getx());
        mine_y.push_back(mines[i].gety());
        mine_type.push_back(mines[i].getType());
        mine_flag.push_back(mines[i].getExist());
    }
}


void viewmodelcommand::GetAllPlayers(QVector<double>&role_x, QVector<double>&role_y, QVector<int>&role_coin,
                   QVector<double>&hook_x, QVector<double>&hook_y, QVector<int>&hook_state,
                   QVector<double>&hook_ex, QVector<double>&hook_ey, QVector<double>&hook_angle){

    int n = GetPlayerNum();
    for(int i = 1; i <= n; ++i){
        Player *ply = GetPlayer(i);
        role_x.push_back(ply->GetRolex());
        role_y.push_back(ply->GetRoley());
        role_coin.push_back(ply->GetCoin());

        hook_x.push_back(ply->getx());
        hook_y.push_back(ply->gety());
        hook_state.push_back(ply->getState());
        hook_ex.push_back(ply->getendx());
        hook_ey.push_back(ply->getendy());
        hook_angle.push_back(ply->getAngle());
    }

}
