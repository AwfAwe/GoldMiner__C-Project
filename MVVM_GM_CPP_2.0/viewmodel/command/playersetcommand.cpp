#include "playersetcommand.h"
#include "viewmodel/viewmodel.h"
PlayerSetCommand::PlayerSetCommand(ViewModel* p) throw():viewmodel_ptr(p)
{}

void PlayerSetCommand::SetParameter(const std::any &param){
    m_param = std::any_cast<int>(param);
}

void PlayerSetCommand::Exec(){
    bool b;
    b = viewmodel_ptr->CallModelPlayerSet(m_param);
}
