#pragma once
#include "./command/frameruncommand.h"
#include "./command/playersetcommand.h"
#include "./command/gameresetcommand.h"
#include "./command/buyitemscommand.h"
#include "./command/useboomcommand.h"
#include "./sink/viewmodelsink.h"
#include "../model/model.h"
#include "../common/precomp.h"
#include "../common/etlbase.h"

class ViewModel: public Proxy_PropertyNotification<ViewModel>
{
public:
    ViewModel();
    void SetModel(const std::shared_ptr<model>& model_);
    bool CallModelFrameRun();
    bool CallModelPlayerSet(int ply_idx);
    bool CallModelGameReset(int gamer_num);
    bool CallModelItemsBuy(int item_id);
    bool CallModelUseBoom(int ply_idx);

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
    std::shared_ptr<GOAL>   GetLevelGoal();

    std::shared_ptr<int>    GetBoomsNum();

    std::shared_ptr<ICommandBase> GetFrameRun();
    std::shared_ptr<ICommandBase> GetPlayerSet();
    std::shared_ptr<ICommandBase> GetGameReset();
    std::shared_ptr<ICommandBase> GetItemsBuy();
    std::shared_ptr<ICommandBase> GetUseBoom();

private:
    std::shared_ptr<model> m_model;
    std::shared_ptr<FrameRunCommand> m_cmdRun;
    std::shared_ptr<PlayerSetCommand> m_cmdPlayerSet;
    std::shared_ptr<GameResetCommand> m_cmdGameReset;
    std::shared_ptr<BuyItemsCommand> m_cmdBuyItems;
    std::shared_ptr<UseBoomCommand> m_cmdUseBoom;

    std::shared_ptr<ViewModelSink> m_sink;
};

