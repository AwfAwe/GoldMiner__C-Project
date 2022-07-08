#ifndef MAP_H
#define MAP_H
#include "mine.h"

class Map{
private:
    Mine *mine;
    int mine_num;
    int total_value;
public:
    Map();
    void mapInit(int mn);
    int& GetMineNum(){return mine_num;}
    Mine *&GetMines(){return mine;}

    int GetTotalValue(){return total_value;};
    ~Map() {
//        delete[] mine;
    }
};
#endif // MAP_H
