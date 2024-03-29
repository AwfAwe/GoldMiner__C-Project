#include "app.h"
#include "iostream"
app::app(){}
app::~app(){}

void app::run(){


    model_ptr = std::make_shared<model>();
    viewmodel_ptr = std::make_shared<ViewModel>();
    viewmodel_ptr->SetModel(model_ptr);

    _mainwindow.SetPlayersPosX(viewmodel_ptr->GetPlayersPosX());
    _mainwindow.SetPlayersPosY(viewmodel_ptr->GetPlayersPosY());
    _mainwindow.SetPlayersCoin(viewmodel_ptr->GetPlayersCoin());

    _mainwindow.SetHooksPosX(viewmodel_ptr->GetHooksPosX());
    _mainwindow.SetHooksPosY(viewmodel_ptr->GetHooksPosY());
    _mainwindow.SetHooksPosEndX(viewmodel_ptr->GetHooksPosEndX());
    _mainwindow.SetHooksPosEndY(viewmodel_ptr->GetHooksPosEndY());

    _mainwindow.SetHooksAngle(viewmodel_ptr->GetHooksAngle());
    _mainwindow.SetHooksState(viewmodel_ptr->GetHooksState());

    _mainwindow.SetMinesPosX(viewmodel_ptr->GetMinesPosX());
    _mainwindow.SetMinesPosY(viewmodel_ptr->GetMinesPosY());
    _mainwindow.SetMinesType(viewmodel_ptr->GetMinesType());
    _mainwindow.SetMinesExist(viewmodel_ptr->GetMinesExist());

    _mainwindow.SetLevelGoal(viewmodel_ptr->GetLevelGoal());
    _mainwindow.SetBoomsNum(viewmodel_ptr->GetBoomsNum());

    _mainwindow.setFrameRunCommand(viewmodel_ptr->GetFrameRun());
    _mainwindow.setPlayerSetCommand(viewmodel_ptr->GetPlayerSet());
    _mainwindow.setGameResetCommand(viewmodel_ptr->GetGameReset());
    _mainwindow.setItemsBuyCommand(viewmodel_ptr->GetItemsBuy());
    _mainwindow.setUseBoomCommand(viewmodel_ptr->GetUseBoom());

    //notifications
    viewmodel_ptr->AddPropertyNotification(_mainwindow.get_updateSink());

    _mainwindow.show();
}

view* app::GetMainWindow(){
    return &_mainwindow;
}

std::shared_ptr<ViewModel> app::GetViewModel(){
    return viewmodel_ptr;
}
