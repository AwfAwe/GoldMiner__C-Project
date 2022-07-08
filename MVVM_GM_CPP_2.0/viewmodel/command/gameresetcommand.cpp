#include "gameresetcommand.h"
#include "viewmodel/viewmodel.h"
GameResetCommand::GameResetCommand(ViewModel *p) throw():viewmodel_ptr(p)
{}

void GameResetCommand::SetParameter(const std::any &param){
    m_param = std::any_cast<int>(param);
}


void GameResetCommand::Exec(){
    bool b;
    b = viewmodel_ptr->CallModelGameReset(m_param);
}
