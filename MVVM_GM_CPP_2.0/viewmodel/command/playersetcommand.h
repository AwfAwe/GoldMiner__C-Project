#ifndef PLAYERSETCOMMAND_H
#define PLAYERSETCOMMAND_H
#include "../../common/etlbase.h"
class ViewModel;

class PlayerSetCommand : public ICommandBase
{
public:
    PlayerSetCommand(ViewModel* p) throw();
    virtual void SetParameter(const std::any &param);
    virtual void Exec();
private:
    ViewModel* viewmodel_ptr;
    int m_param;

};

#endif // PLAYERSETCOMMAND_H
