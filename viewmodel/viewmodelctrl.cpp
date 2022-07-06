#include "viewmodelctrl.h"

viewmodelctrl::viewmodelctrl()
{

}

viewmodelctrl::viewmodelctrl(int plynm, int mnnm){
    level_ = new Level(plynm, mnnm);
}

void viewmodelctrl::FrameOperation(){
    level_->HookRotate();
    level_->HookMove();
    level_->JudgeFetch();
}

void viewmodelctrl::FetchOperation(int idx){
    level_->HookDown(idx);

}
