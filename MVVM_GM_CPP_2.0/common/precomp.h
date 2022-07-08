#ifndef PRECOMP_H
#define PRECOMP_H

#include "vector"
#include <cmath>
#include <iostream>
#define WIDTH 1266
#define HEIGHT 766
#define ROLE_WIDTH 140
#define ROLE_HEIGHT 120
#define HOOK_BIAS 40
#define PI 3.1415926
#define MAX_ANGLE 80
#define MINE_NUM 10
#define IMAGE_MAX 21
#define DeadAngleRange 10
#define LEN 50
#define MAPUPPERBOUND 120
#define VIGOSPEED 0.5
#define DEFAULT_PLAYER_NUM 3
#define DEFAULT_MINE_NUM 15
#define DEFAULT_HOOK_SPEED 2.0
#define LEVELTIME 60

#define DIS(A) \
sqrt(pow(A.getx() - x, 2) + pow(A.gety() - y, 2))
//int role_flag = 0, start_flag = 0;
//int i_up = 1, i_down = 0;


typedef std::vector<double*> POS;
typedef std::vector<double&> POSx;
typedef std::vector<double*> ANGLES;
typedef std::vector<int*> COINS;
typedef std::vector<int*> STT;
typedef std::vector<int*> TYPES;
typedef std::vector<bool*> EXISTS;


enum Index
{
    i_goldsmall=0,
    i_goldmiddle=1,
    i_goldbig=2,
    i_stonesmall=3,
    i_stonebig=4,
    i_money=5,
    i_diamond=6,
    i_roleDown=7,
    i_roleUp=8,
    i_shopper=23
};
/*
钩子状态：摆动、伸长、缩短、停止
*/
enum ATTR {
    //物品类型
    LITTLEGOLD,
    MIDGOLD,
    BIGGOLD,
    LITTLESTONE,
    BIGSTONE,
    MONEY,
    DIAMOND,
    //钩子方向
    LEFT,
    RIGHT,
    //钩子状态
    M_NORMAL,
    M_LONG,
    M_SHORT
};

enum MINE {//图片数组下标
    littlegold = 1,
    midgold = 3,
    biggold = 5,
    littlestone = 7,
    bigstone = 9,
    money = 11,
    diamond = 13,
    role_down = 15,
    role_up = 17,
    over = 18,
    bk = IMAGE_MAX - 1,
};


#endif // PRECOMP_H
