#include "model.h"

model::model(){
//    model_map = std::make_shared<std::vector<Map*>>();
    level_id = std::make_shared<int>(1);
    player_num = std::make_shared<int>(DEFAULT_PLAYER_NUM);
    model_player = std::make_shared<std::vector<Player*>>();

    for(int i=0; i<*player_num; ++i){
        players[i] = new Player(i, *player_num);
        model_player->push_back(players[i]);
    }
    map_ = new Map();
    map_->mapInit(DEFAULT_MINE_NUM);

    std::cout<<"model construct address::"<<&((*model_player)[0]->GetRolex())<<std::endl;

//    model_mine = std::make_shared<std::vector<Mine>>();
//    model_role = std::make_shared<std::vector<Role>>();
//    model_hook = std::make_shared<std::vector<Hook>>();
//    model_map->push_back(Map());

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


bool model::framerun(){
     for(auto i = 0;i < DEFAULT_PLAYER_NUM;i++){
         (*model_player)[i]->hookRock();
         (*model_player)[i]->HookMove();

         (*model_player)[i]->JudgeGrap(map_->GetMines(), DEFAULT_MINE_NUM);
     }
    return true;
}

bool model::playerset(int idx){
    (*model_player)[idx-1]->setState(M_LONG);
    return true;
}

int model::GetLevelId(){
    return *level_id;
}

