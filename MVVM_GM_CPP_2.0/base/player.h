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
    void JudgeGrap(Mine [], int);
    int& GetCoin(){return coin_;}
};
#endif // PLAYER_H
