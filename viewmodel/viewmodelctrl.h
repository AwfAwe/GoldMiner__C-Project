#ifndef VIEWMODELCTRL_H
#define VIEWMODELCTRL_H
#include "..\model\level.h"

class viewmodelnotification;
//class Level;
class viewmodelctrl
{
public:
    viewmodelctrl();
    viewmodelctrl(int ply_nm, int mn_nm);
    void levelinit();
    int GetPlayerNum(){return level_->GetPlayerNum();}
    Player* GetPlayer(int idx){return level_->GetPlayer(idx);}
    Mine* GetMines(){return level_->GetMines();}
    int GetMineNum(){return level_->GetMineNum();}

    void FrameOperation();
    void FetchOperation(int idx);

private:
    Level *level_;
};

#endif // VIEWMODELCTRL_H
