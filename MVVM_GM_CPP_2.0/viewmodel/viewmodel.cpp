#include "viewmodel.h"

ViewModel::ViewModel():
    m_cmdRun(std::make_shared<FrameRunCommand>(this)),
    m_cmdPlayerSet(std::make_shared<PlayerSetCommand>(this)),
    m_cmdGameReset(std::make_shared<GameResetCommand>(this)),
    m_cmdBuyItems(std::make_shared<BuyItemsCommand>(this)),
    m_cmdUseBoom(std::make_shared<UseBoomCommand>(this))
{}

void ViewModel::SetModel(const std::shared_ptr<model> &model_){
    m_model = model_;
//    m_mode->AddPropertyNotification(std::static_pointer_cast<IPropertyNotification>(m_sink));
//    todo : notification
}

bool ViewModel::CallModelFrameRun(){
    return m_model->framerun();
}

bool ViewModel::CallModelPlayerSet(int ply_idx){
    return m_model->playerset(ply_idx);
}

bool ViewModel::CallModelGameReset(int gamernum){
    return m_model->gamereset(gamernum);
}

bool ViewModel::CallModelItemsBuy(int item_id){
    return m_model->itemsbuy(item_id);
}

bool ViewModel::CallModelUseBoom(int ply_idx){
    return m_model->usebooms(ply_idx);
}


std::shared_ptr<ICommandBase> ViewModel::GetFrameRun(){
    return std::static_pointer_cast<ICommandBase>(m_cmdRun);
}

std::shared_ptr<ICommandBase> ViewModel::GetPlayerSet(){
    return std::static_pointer_cast<ICommandBase>(m_cmdPlayerSet);
}

std::shared_ptr<ICommandBase> ViewModel::GetGameReset(){
    return std::static_pointer_cast<ICommandBase>(m_cmdGameReset);
}

std::shared_ptr<ICommandBase> ViewModel::GetItemsBuy(){
    return std::static_pointer_cast<ICommandBase>(m_cmdBuyItems);
}

std::shared_ptr<ICommandBase> ViewModel::GetUseBoom(){
    return std::static_pointer_cast<ICommandBase>(m_cmdUseBoom);
}

std::shared_ptr<POS> ViewModel::GetPlayersPosX(){
    return m_model->GetMinerPosx();
}

std::shared_ptr<POS> ViewModel::GetPlayersPosY(){
    return m_model->GetMinerPosy();
}

std::shared_ptr<COINS> ViewModel::GetPlayersCoin(){
    return m_model->GetPlayerMoney();
}

std::shared_ptr<POS> ViewModel::GetHooksPosX(){
    return m_model->GetHookPosx();
}

std::shared_ptr<POS> ViewModel::GetHooksPosY(){
    return m_model->GetHookPosy();
}

std::shared_ptr<POS> ViewModel::GetHooksPosEndX(){
    return m_model->GetHookPosEndx();
}

std::shared_ptr<POS> ViewModel::GetHooksPosEndY(){
    return m_model->GetHookPosEndy();
}

std::shared_ptr<ANGLES> ViewModel::GetHooksAngle(){
    return m_model->GetHookAngle();
}

std::shared_ptr<STT>    ViewModel::GetHooksState(){
    return m_model->GetHookState();
}

std::shared_ptr<POS> ViewModel::GetMinesPosX(){
    return m_model->GetMinePosx();
}

std::shared_ptr<POS> ViewModel::GetMinesPosY(){
    return m_model->GetMinePosy();
}

std::shared_ptr<TYPES> ViewModel::GetMinesType(){
    return m_model->GetMineType();
}

std::shared_ptr<EXISTS> ViewModel::GetMinesExist(){
    return m_model->GetMineExist();
}

std::shared_ptr<GOAL> ViewModel::GetLevelGoal(){
    return m_model->GetLevelGoal();
}

std::shared_ptr<int>  ViewModel::GetBoomsNum(){
    return m_model->GetBoomsNum();
}
