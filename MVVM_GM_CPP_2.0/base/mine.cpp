#include "mine.h"

bool Mine::CheckForCover(Mine &other) {
    if ((fabs(other.getx() - x) < other.getSizex() + sizex
        && fabs(other.gety() - y) < other.getSizey() + sizey)) {
        return false;
    }
    return true;
}

void Mine::mineInit() {
    bool valid = false;
    hold = false;
    while (!valid) {
        x = 110.0 + rand() % (WIDTH - 220);
        y = 110.0 + rand() % (HEIGHT - 220);
        flag = true;
        type = rand() % 7;
        switch (type) {
        case LITTLEGOLD:
            sizex = 32;
            sizey = 30;
            gold = 50;
            break;
        case MIDGOLD:
            sizex = 59;
            sizey = 55;
            gold = 100;
            break;
        case BIGGOLD:
            sizex = 155;
            sizey = 144;
            gold = 500;
            break;
        case LITTLESTONE:
            sizex = 67;
            sizey = 57;
            gold = 11;
            break;
        case BIGSTONE:
            sizex = 94;
            sizey = 83;
            gold = 20;
            break;
        case MONEY:
            sizex = 73;
            sizey = 83;
            gold = rand() % 500 + 100;
            break;
        case DIAMOND:
            sizex = 33;
            sizey = 27;
            gold = 600;
            break;
        }

        if (x - sizex < 0 || x + sizex > WIDTH
            || y - sizey < 1.0*MAPUPPERBOUND + DeadAngleRange || y + sizey > 1.0*HEIGHT) {
            continue;
        }
        valid = true;
    }
}
