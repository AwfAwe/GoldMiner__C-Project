#ifndef USEBOOMCOMMAND_H
#define USEBOOMCOMMAND_H
#include "../../common/etlbase.h"

class ViewModel;
class UseBoomCommand: public ICommandBase
{
public:
    UseBoomCommand(ViewModel *p)throw();
    virtual void SetParameter(const std::any &param);
    virtual void Exec();
private:
    ViewModel* viewmodel_ptr;
    int m_param;
};

#endif // USEBOOMCOMMAND_H
