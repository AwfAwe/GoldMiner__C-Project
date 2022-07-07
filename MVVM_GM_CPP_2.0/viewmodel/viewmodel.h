#pragma once
#include "./command/frameruncommand.h"
#include "./command/playersetcommand.h"
#include "../model/model.h"
#include "../common/precomp.h"

class ViewModel
{
public:
    ViewModel();
    void SetModel(const std::shared_ptr<model>& model_);
    bool CallModelFrameRun();
    bool CallModelPlayerSet(int ply_idx);
    std::shared_ptr<POS>    GetPlayersPosX();
    std::shared_ptr<POS>    GetPlayersPosY();
    std::shared_ptr<COINS>  GetPlayersCoin();
    std::shared_ptr<POS>    GetHooksPosX();
    std::shared_ptr<POS>    GetHooksPosY();
    std::shared_ptr<POS>    GetHooksPosEndX();
    std::shared_ptr<POS>    GetHooksPosEndY();

    std::shared_ptr<ANGLES> GetHooksAngle();
    std::shared_ptr<STT>    GetHooksState();

    std::shared_ptr<POS>    GetMinesPosX();
    std::shared_ptr<POS>    GetMinesPosY();
    std::shared_ptr<TYPES>  GetMinesType();
    std::shared_ptr<EXISTS> GetMinesExist();

    std::shared_ptr<ICommandBase> GetFrameRun();
    std::shared_ptr<ICommandBase> GetPlayerSet();
private:
    std::shared_ptr<model> m_model;
    std::shared_ptr<FrameRunCommand> m_cmdRun;
    std::shared_ptr<PlayerSetCommand> m_cmdPlayerSet;
};

