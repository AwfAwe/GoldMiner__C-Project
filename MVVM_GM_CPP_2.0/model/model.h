#ifndef MODEL_H
#define MODEL_H
#include <memory>
#include "..\base\map.h"
#include "..\base\player.h"

class model{
private:

    std::shared_ptr<std::vector<Player*>> model_player;
    std::shared_ptr<std::vector<Map*>> model_map;
    std::shared_ptr<int> level_id;
    std::shared_ptr<int> player_num;
    Player *players[4];
    Map *map_;
public:
    model();
    void setminer(int idx,double x,double y);
    void sethook(int idx,double x,double y,double angle,int state);
    void setmine(int idx,double x,double y,bool hold,bool fetch);
    void setmoney(int idx,int money);
    bool framerun();
    bool playerset(int idx);
    std::shared_ptr<std::vector<double*>> GetMinerPosx();
    std::shared_ptr<std::vector<double*>> GetMinerPosy();
    std::shared_ptr<std::vector<double*>> GetHookPosx();
    std::shared_ptr<std::vector<double*>> GetHookPosy();
    std::shared_ptr<std::vector<double*>> GetHookPosEndx();
    std::shared_ptr<std::vector<double*>> GetHookPosEndy();
    std::shared_ptr<std::vector<double*>> GetHookAngle();
    std::shared_ptr<std::vector<int*>> GetHookState();
    std::shared_ptr<std::vector<double*>> GetMinePosx();
    std::shared_ptr<std::vector<double*>> GetMinePosy();
    std::shared_ptr<std::vector<bool*>> GetMineExist();
    std::shared_ptr<std::vector<int*>> GetMineType();
    std::shared_ptr<std::vector<int*>> GetPlayerMoney();
    int GetLevelId();
};

#endif // MODEL_H
