#ifndef BUYITEMSCOMMAND_H
#define BUYITEMSCOMMAND_H
#include "../../common/etlbase.h"

class ViewModel;

class BuyItemsCommand: public ICommandBase
{
public:
    BuyItemsCommand(ViewModel* p) throw();

    virtual void SetParameter(const std::any& param);
    virtual void Exec();

private:
    ViewModel* viewmodel_ptr;
    int m_param;

};



#endif // BUYITEMSCOMMAND_H
