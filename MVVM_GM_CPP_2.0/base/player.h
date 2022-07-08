#ifndef PLAYER_H
#define PLAYER_H
#include "role.h"
#include "hook.h"
#include "mine.h"
#include <cstring>
#include <string>

class Player : public Role, public Hook{
private:
    int coin_;
    int id_;
    std::string name_;
    //Item* items;
public:
    Player(int id = 1, int totid = 1, double spd = DEFAULT_HOOK_SPEED);
    void reset();
    bool JudgeGrap(Mine [], int, bool);
    int& GetCoin(){return coin_;}
    void SetCoin(int tar_coin){coin_ = tar_coin;}
};
#endif // PLAYER_H
