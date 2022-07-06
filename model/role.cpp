#include "role.h"

Role::Role(int id, int totid) {

    this->width = 140;
    this->height = 120;
    switch(totid){

    case 1:
        this->x = WIDTH/2-width/2;
        break;
    case 2:
        if(id&1)
            this->x = WIDTH/2-width/2-WIDTH/6;
        else
            this->x = WIDTH/2-width/2+WIDTH/6;
        break;
    case 3:
        if(id==1)
            this->x = WIDTH/2-width/2-WIDTH/6;
        else if(id==2)
            this->x = WIDTH/2-width/2;
        else
            this->x = WIDTH/2-width/2+WIDTH/6;
    }
    this->y = 10;
}
