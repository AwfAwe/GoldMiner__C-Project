#include "useboomcommand.h"
#include "viewmodel/viewmodel.h"


UseBoomCommand::UseBoomCommand(ViewModel *p)throw():viewmodel_ptr(p)
{}

void UseBoomCommand::SetParameter(const std::any &param){
    m_param = std::any_cast<int>(param);
}

void UseBoomCommand::Exec(){
    bool b;
    b = viewmodel_ptr->CallModelUseBoom(m_param);
}
