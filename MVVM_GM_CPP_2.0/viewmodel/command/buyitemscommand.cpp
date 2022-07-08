#include "buyitemscommand.h"
#include "viewmodel/viewmodel.h"
BuyItemsCommand::BuyItemsCommand(ViewModel *p)throw():viewmodel_ptr(p)
{}


void BuyItemsCommand::SetParameter(const std::any &param){
    m_param = std::any_cast<int>(param);
}

void BuyItemsCommand::Exec(){
    bool b;
    b = viewmodel_ptr->CallModelItemsBuy(m_param);
}
