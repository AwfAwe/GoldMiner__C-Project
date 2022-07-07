#include "frameruncommand.h"
#include "viewmodel/viewmodel.h"
FrameRunCommand::FrameRunCommand(ViewModel* p) throw():viewmodel_ptr(p)
{}

void FrameRunCommand::SetParameter(const std::any &param){
    m_param = std::any_cast<int>(param);
}


void FrameRunCommand::Exec(){
    bool b;
    b = viewmodel_ptr->CallModelFrameRun();
}
