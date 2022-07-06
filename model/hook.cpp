#include "hook.h"

Hook::Hook(double x, double y, double speed = 1.0) {

    this->x = x;
    this->y = y;
    this->len = LEN;
    this->angle = 0;
    this->dir = RIGHT;
    this->state = M_NORMAL;
    this->endx = x;
    this->endy = y + this->len;
    this->speed = speed;
    this->mine_speed = 0;
    this->vigo_speed = 0;
    this->vx = sin(PI / 180 * this->angle) * speed;
    this->vy = cos(PI / 180 * this->angle) * speed;
    this->index = -1;
}
Hook::Hook(int id, int totid, double speed) {

    switch(totid){

    case 1:
        this->x = WIDTH/2-ROLE_WIDTH/2;
        break;
    case 2:
        if(id&1)
            this->x = WIDTH/2-ROLE_WIDTH/2-WIDTH/6;
        else
            this->x = WIDTH/2-ROLE_WIDTH/2+WIDTH/6;
        break;
    case 3:
        if(id==1)
            this->x = WIDTH/2-ROLE_WIDTH/2-WIDTH/6;
        else if(id==2)
            this->x = WIDTH/2-ROLE_WIDTH/2;
        else
            this->x = WIDTH/2-ROLE_WIDTH/2+WIDTH/6;
        break;
    }

    this->x += HOOK_BIAS;
    this->y = 100;
    this->len = LEN;
    this->angle = 0;
    this->dir = RIGHT;
    this->state = M_NORMAL;
    this->endx = x;
    this->endy = y + this->len;
    this->speed = speed;
    this->mine_speed = 0;
    this->vigo_speed = 0;
    this->vx = sin(PI / 180 * this->angle) * speed;
    this->vy = cos(PI / 180 * this->angle) * speed;
    this->index = -1;
}

void Hook::hookRock()
{
    if (state == M_NORMAL)
    {
        if (dir == RIGHT)
            angle += 0.5;
        else if (dir == LEFT)
            angle -= 0.5;
        if (angle > MAX_ANGLE)
            dir = LEFT;
        else if (angle < -MAX_ANGLE)
            dir = RIGHT;
        endx = x + sin(PI / 180 * angle) * len;
        endy = y + cos(PI / 180 * angle) * len;
    }
//    printf("HOOKROCK:: %.2f\n", angle);


}

void Hook::HookMove() {//钩子位置变化

    if (state == M_LONG) {//出勾时，钩子位置一直变化
        endx += sin(PI / 180 * this->angle) * speed;
        endy += cos(PI / 180 * this->angle) * speed;
        if(endx<0||endx>WIDTH||endy>HEIGHT){
            state = M_SHORT;
        }
    }
    else if (state == M_SHORT) {//收勾时，钩子位置一直变化
        endx -= sin(PI / 180 * this->angle) * (speed + mine_speed + vigo_speed);
        endy -= cos(PI / 180 * this->angle) * (speed + mine_speed + vigo_speed);

        if (GetCurrentLen() <= LEN) {//钩子复原时，绳子回到正常状态
            state = M_NORMAL;
            mine_speed = 0;

        }
    }
}

int Hook::GetCurrentLen(){

    return (int)sqrt(pow(endx-x,2)+pow(endy-y,2));

}

void Hook::Reset(bool isVigo = false){
    this->len = LEN;
    this->angle = 0;
    this->dir = RIGHT;
    this->state = M_NORMAL;
    this->endx = x;
    this->endy = y + this->len;

    this->mine_speed = 0;
    this->vigo_speed = isVigo * VIGOSPEED;
    this->vx = sin(PI / 180 * this->angle) * speed;
    this->vy = cos(PI / 180 * this->angle) * speed;
    this->index = -1;

}
