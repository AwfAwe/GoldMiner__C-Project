#include "map.h"

Map::Map() {
    mine = nullptr;

}
void Map::mapInit(int mn){
    mine_num = mn;
    total_value = 0;
    if(mine == nullptr){
        mine = new Mine[mine_num];
    }
    for (int i = 0; i < mine_num; ++i) {
        bool valid = false;
        while (!valid) {
            valid = true;
            mine[i].mineInit();
            for (int j = 0; j < i; ++j) {
                if (!mine[i].CheckForCover(mine[j])) {
                    valid = false;
                    break;
                }
            }

        }
        total_value += mine[i].getGold();
    }

}
