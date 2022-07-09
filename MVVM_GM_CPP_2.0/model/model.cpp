#include "model.h"

model::model(){
//    model_map = std::make_shared<std::vector<Map*>>();
    level_id = std::make_shared<int>(0);
    player_num = std::make_shared<int>(DEFAULT_PLAYER_NUM);
    model_player = std::make_shared<std::vector<Player*>>();
    level_goal = std::make_shared<GOAL>(0);
    booms_num = std::make_shared<int>(0);

    for(int i=0; i<*player_num; ++i){
        players[i] = new Player(i, *player_num);
        model_player->push_back(players[i]);
    }
    map_ = new Map();
    map_->mapInit(DEFAULT_MINE_NUM);
//    booms_num
    std::cout<<"model construct address::"<<&((*model_player)[0]->GetRolex())<<std::endl;
}


std::shared_ptr<std::vector<double*>> model::GetHookPosx(){
    std::shared_ptr<std::vector<double*>> HookPosx = std::make_shared<std::vector<double*>>();
    for(int i=0; i<*player_num; i++){
        HookPosx->push_back(&(players[i]->getx()));
    }
    std::cout<<"model:: x address"<<&((*HookPosx)[0])<<std::endl;
    return HookPosx;
}

std::shared_ptr<std::vector<double*>> model::GetHookPosy(){
    std::shared_ptr<std::vector<double*>> HookPosy = std::make_shared<std::vector<double*>>();
    for(int i=0; i<*player_num; i++){
        HookPosy->push_back(&(players[i]->gety()));
    }
    return HookPosy;
}

std::shared_ptr<std::vector<double*>> model::GetHookPosEndx(){
    std::shared_ptr<std::vector<double*>> HookPosEndx = std::make_shared<std::vector<double*>>();
    for(int i=0; i<*player_num; i++){
        HookPosEndx->push_back(&(players[i]->getendx()));
    }
    return HookPosEndx;
}

std::shared_ptr<std::vector<double*>> model::GetHookPosEndy(){
    std::shared_ptr<std::vector<double*>> HookPosEndy = std::make_shared<std::vector<double*>>();
    for(int i=0; i<*player_num; i++){
        HookPosEndy->push_back(&(players[i]->getendy()));
    }
    return HookPosEndy;
}

std::shared_ptr<std::vector<double*>> model::GetHookAngle(){
    std::shared_ptr<std::vector<double*>> HookAngle = std::make_shared<std::vector<double*>>();
    for(int i=0; i<*player_num; i++){
        HookAngle->push_back(&(players[i]->getAngle()));
    }
    return HookAngle;
}

std::shared_ptr<std::vector<int*>> model::GetHookState(){
    std::shared_ptr<std::vector<int*>> HookState = std::make_shared<std::vector<int*>>();
    for(int i=0; i<*player_num; i++){
        HookState->push_back(&(players[i]->getState()));
    }
    return HookState;
}

std::shared_ptr<std::vector<double*>> model::GetMinePosx(){
    std::shared_ptr<std::vector<double*>> MinePosx = std::make_shared<std::vector<double*>>();
    Mine* GotMines = map_->GetMines();
    for(int i=0; i<map_->GetMineNum();++i){
        MinePosx->push_back(&(GotMines[i].getx()));
    }
    return MinePosx;
}

std::shared_ptr<std::vector<double*>> model::GetMinePosy(){
    std::shared_ptr<std::vector<double*>> MinePosy = std::make_shared<std::vector<double*>>();
    Mine* GotMines = map_->GetMines();
    for(int i=0; i<map_->GetMineNum();++i){
        MinePosy->push_back(&(GotMines[i].gety()));
    }
    return MinePosy;
}

std::shared_ptr<std::vector<bool*>> model::GetMineExist(){
    std::shared_ptr<std::vector<bool*>> MineExist = std::make_shared<std::vector<bool*>>();
    Mine* GotMines = map_->GetMines();
    for(int i=0; i<map_->GetMineNum();++i){
        MineExist->push_back(&(GotMines[i].getExist()));
    }
    return MineExist;
}

std::shared_ptr<std::vector<int*>> model::GetMineType(){
    std::shared_ptr<std::vector<int*>> MineType = std::make_shared<std::vector<int*>>();
    Mine* GotMines = map_->GetMines();
    for(int i=0; i<map_->GetMineNum();++i){
        MineType->push_back(&(GotMines[i].getType()));
    }
    return MineType;
}

std::shared_ptr<std::vector<double*>> model::GetMinerPosx(){

    std::shared_ptr<std::vector<double*>> MinerPosx = std::make_shared<std::vector<double*>>();
    for(int i=0; i<*player_num; ++i){
        MinerPosx->push_back(&((*model_player)[i]->GetRolex()));
    }
    return MinerPosx;
}

std::shared_ptr<std::vector<double*>> model::GetMinerPosy(){
    std::shared_ptr<std::vector<double*>> MinerPosy = std::make_shared<std::vector<double*>>();
    for(int i=0; i<*player_num; ++i){
        MinerPosy->push_back(&((*model_player)[i]->GetRoley()));
    }
    return MinerPosy;
}

std::shared_ptr<std::vector<int*>> model::GetPlayerMoney(){
    std::shared_ptr<std::vector<int*>> Playermoney = std::make_shared<std::vector<int*>>();
    for(int i=0; i<*player_num; ++i){
        Playermoney->push_back(&((*model_player)[i]->GetCoin()));
    }
    return Playermoney;
}

std::shared_ptr<GOAL> model::GetLevelGoal(){
    return level_goal;
}

bool model::framerun(){
     for(auto i = 0;i < DEFAULT_PLAYER_NUM;i++){
         (*model_player)[i]->hookRock();
         (*model_player)[i]->HookMove();

         (*model_player)[i]->JudgeGrap(map_->GetMines(), DEFAULT_MINE_NUM, false);
     }
    return true;
}

bool model::playerset(int idx){
    int StateGot = (*model_player)[idx]->getState();
    if(StateGot == M_NORMAL){
        (*model_player)[idx]->setState(M_LONG);
    }
    return true;
}

bool model::gamereset(int ply_nm){
    *player_num = ply_nm;
    for(int i=0; i<*player_num; ++i){
        int tmp_coin = (*model_player)[i]->GetCoin();
        *((*model_player)[i])=Player(i+1,ply_nm);
        (*model_player)[i]->Reset(false);
        (*model_player)[i]->SetCoin(tmp_coin);
    }
    map_->mapInit(DEFAULT_MINE_NUM);
    *level_id = *level_id + 1;
    *level_goal += int (map_->GetTotalValue() * (0.7+0.05*(*player_num)));
    return true;
}

std::shared_ptr<int>  model::GetBoomsNum(){
    return booms_num;
}

bool model::Afford(int Price){
    int totCoin = 0;
    int Coin[3] = {0};
    for(int i=0; i<*player_num; ++i){
        Coin[i] = players[i]->GetCoin();
        totCoin += Coin[i];
    }
    if(totCoin<Price){
        return false;
    }
    for(int i=0; i<*player_num; ++i){
        if(Coin[i]>=Price){
            players[i]->SetCoin(Coin[i]-Price);
            Price = 0;
        }else{
            Price -= Coin[i];
            players[i]->SetCoin(0);
        }
    }

    return true;
}

bool model::itemsbuy(int itemid){
    switch (itemid) {
    case 1: //大力水 100
        if(Afford(100*(*player_num))){
            for(int i=0; i<*player_num; ++i){
                (*model_player)[i]->Reset(true);
            }
            Fire_OnPropertyChanged("Changed");
        }else{
            return false;
        }
        break;

    case 2:
        if(Afford(50)){
            Fire_OnPropertyChanged("Changed");
        }else{
            return false;
        }

        break;
    case 3:
        if(Afford(100)){
            Fire_OnPropertyChanged("Changed");
        }else{
            return false;
        }
        break;
    case 4:
        if(Afford(200)){
            Fire_OnPropertyChanged("Changed");
        }else{
            return false;
        }

        break;
    case 5: //炸药 100
        if(Afford(100)){
            (*booms_num)++;
            Fire_OnPropertyChanged("Changed");
        }else{
            return false;
        }
        break;
    }
   return true;
}
bool model::usebooms(int idx){
    if(*booms_num > 0 && (*model_player)[idx]->JudgeGrap(map_->GetMines(),DEFAULT_MINE_NUM, true)){
        (*booms_num) --;
    }
    return true;
}



int model::GetLevelId(){
    return *level_id;
}

