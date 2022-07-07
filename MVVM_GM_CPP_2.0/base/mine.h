#ifndef MINE_H
#define MINE_H
#include "../common/precomp.h"
class Mine{
private:
    double x;
    double y;
    double sizex;
    double sizey;
    int type;
    bool flag;
    bool hold;
    int gold;
public:
    double& getx() {return x;}
    double& gety() {return y;}
    double& getSizex() {return sizex;}
    double& getSizey() {return sizey;}
    bool& getExist(){return flag;}
    bool& isheld(){return hold;}
    int& getGold(){return gold;}
    int& getType(){return type;}
    bool CheckForCover(Mine &other);

    void mineInit();

    void setx(double nx){x=nx;}
    void sety(double ny){y=ny;}
    void setFlagfalse(){flag = false;}
    void setHoldTrue(){hold = true;}
//    friend void Player::JudgeGrap(Mine mine[], int mine_num)
};
#endif // MINE_H
