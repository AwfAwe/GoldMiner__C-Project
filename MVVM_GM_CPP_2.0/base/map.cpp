#include "map.h"

Map::Map() {}
void Map::mapInit(int mn){
    mine_num = mn;
    mine = new Mine[mine_num];
    for (int i = 0; i < mine_num; i++) {
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
    }

}
