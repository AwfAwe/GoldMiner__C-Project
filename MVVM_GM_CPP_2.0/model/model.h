#ifndef MODEL_H
#define MODEL_H
#include <memory>
#include "..\base\map.h"
#include "..\base\player.h"
#include "./common/etlbase.h"

class model: public Proxy_PropertyNotification<model>{
private:

    std::shared_ptr<std::vector<Player*>> model_player;
    std::shared_ptr<std::vector<Map*>> model_map;
    std::shared_ptr<int> level_id;
    std::shared_ptr<int> player_num;
    Player *players[4];
    Map *map_;
    std::shared_ptr<GOAL> level_goal;
    std::shared_ptr<int>  booms_num;

public:
    model();
    void setminer(int idx,double x,double y);
    void sethook(int idx,double x,double y,double angle,int state);
    void setmine(int idx,double x,double y,bool hold,bool fetch);
    void setmoney(int idx,int money);

    bool framerun();

    bool playerset(int idx);
    bool gamereset(int ply_nm);
    bool itemsbuy(int itemid);
    bool usebooms(int idx);

    bool Afford(int Price);

    std::shared_ptr<POS> GetMinerPosx();
    std::shared_ptr<POS> GetMinerPosy();
    std::shared_ptr<POS> GetHookPosx();
    std::shared_ptr<POS> GetHookPosy();
    std::shared_ptr<POS> GetHookPosEndx();
    std::shared_ptr<POS> GetHookPosEndy();
    std::shared_ptr<ANGLES> GetHookAngle();
    std::shared_ptr<STT> GetHookState();
    std::shared_ptr<POS> GetMinePosx();
    std::shared_ptr<POS> GetMinePosy();
    std::shared_ptr<EXISTS> GetMineExist();
    std::shared_ptr<TYPES> GetMineType();
    std::shared_ptr<COINS> GetPlayerMoney();
    std::shared_ptr<GOAL> GetLevelGoal();
    std::shared_ptr<int>  GetBoomsNum();
    int GetLevelId();

};

#endif // MODEL_H
