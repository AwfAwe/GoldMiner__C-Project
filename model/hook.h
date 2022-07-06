#ifndef HOOK_H
#define HOOK_H
#include "..\common.h"
class Hook {
private:
    double x;
    double y;
    double len; //钩子长度
    double speed; //钩子沉潜速度
    double mine_speed; //因为抓矿变慢的速度
    double vigo_speed;//药水加快的速度
    int state; //当前状态
    double endx;
    double endy;
    double angle; //钩子当前角度
    int dir;//钩子摆动方向
    double vx;//速度变化量
    double vy;
    int index;//抓住的物品下标
public:
    Hook(double x, double y, double speed);
    Hook(int id = 1, int totid = 1, double speed = DEFAULT_HOOK_SPEED);
    void hookRock();
    void HookMove();
    void Reset(bool);
    virtual double getx(){return x;}
    virtual double gety(){return y;}
    virtual double getendx(){return endx;}
    virtual double getendy(){return endy;}

    int getIndex(){return index;}
    void setIndex(int idx){index = idx;}

    int getState(){return state;}
    void setState(int stt){state = stt;}

    double getAngle(){return angle;}

    void setMine_speed(double mspd){mine_speed = mspd;}

    int GetCurrentLen();
};


#endif // HOOK_H
