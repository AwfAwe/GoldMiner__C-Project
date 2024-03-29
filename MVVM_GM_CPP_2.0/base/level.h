#ifndef LEVEL_H
#define LEVEL_H
#include "player.h"
#include "map.h"
#include <QTimer>
#include <memory>

class Level{
private:
    Player* player[4];
    int player_num;
    Map map;
//    QTimer timer_frame, timer_clock;
//    int FrameTime, ClockTime;

public:
    Level(int pn = DEFAULT_PLAYER_NUM, int mn = DEFAULT_MINE_NUM);
    void HookRotate();
    void HookMove();
    void JudgeFetch();
    void HookDown(int idx);
    void NotifyMine(int idx, double x, double y, bool hold,bool fetch);
    void NotifyPlayer(int idx, int coin);
    void NotifyHook(int idx, double ex, double ey, double agl, int stt);

    int GetPlayerNum(){return player_num;}
    Player* GetPlayer(int idx){return player[idx];}
    Mine* GetMines(){return map.GetMines();}
    int GetMineNum(){return map.GetMineNum();}

    void Reset();
    ~Level(){
    }

};

#endif // LEVEL_H
