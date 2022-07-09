#include "player.h"

Player::Player(int id, int totid, double spd) :Role(id, totid),Hook(id, totid, spd){
    coin_ = 0;
    id_ = id;
    name_ = "player" + std::to_string(id);


}

void Player::reset(){
//    *this = Player(1)

}


bool Player::JudgeGrap(Mine mine[], int mine_num, bool flag) {// 判断是否抓住物品
    bool boom = 0;
    for (int i = 0; i < mine_num; i++) {
        if (mine[i].getExist() && !mine[i].isheld() &&//物品存在，且钩子在金块内部，则视为抓住金块，记录金块下标。
            getendx() > mine[i].getx() && getendx() < (mine[i].getx() + mine[i].getSizex()) &&
            getendy() > mine[i].gety() && getendy() < (mine[i].gety() + mine[i].getSizey()) )
        {
            setIndex(i);
//            mine[getIndex()].setFlagfalse();
            mine[getIndex()].setHoldTrue();//一个人抓到物品不能再被其他玩家抓取
            break;
        }
    }
    if (getIndex() != -1) {//如果抓住金块，绳子缩短
        setState(M_SHORT);
        mine[getIndex()].setx(getendx() - mine[getIndex()].getSizex() * 0.5);
        mine[getIndex()].sety(getendy() - mine[getIndex()].getSizey() * 0.5);

        if(flag){
            mine[getIndex()].settype(DESTROY);
            mine[getIndex()].setFlagfalse();
            boom = 1;
        }


        if (GetCurrentLen()<=LEN) {//如果绳子收缩为原长
            if(mine[getIndex()].getExist())
                coin_ += mine[getIndex()].getGold();//人物金币增加
            setState(M_NORMAL);//绳子状态为原长
            mine[getIndex()].setFlagfalse();
            setIndex(-1);//钩子变为没抓金子
        }
        else
        {
            switch (mine[getIndex()].getType()) {
            case LITTLEGOLD:
                setMine_speed(-0.5);
                break;
            case MIDGOLD:
                setMine_speed(-2.0);
                break;
            case BIGGOLD:
                setMine_speed(-3.5);
                break;
            case LITTLESTONE:
                setMine_speed(-2.5);
                break;
            case BIGSTONE:
                setMine_speed(-3.5);
                break;
            case MONEY:
                setMine_speed(-2.0*(rand()%10+1)/20);
                break;
            case DIAMOND:
                setMine_speed(0);
                break;
            case DESTROY:
                setMine_speed(0);
                break;
            }
        }
    }
    return boom;
}
