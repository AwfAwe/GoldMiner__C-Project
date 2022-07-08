#ifndef GAMERESETCOMMAND_H
#define GAMERESETCOMMAND_H

#include "../../common/etlbase.h"

class ViewModel;

class GameResetCommand: public ICommandBase
{
public:
    GameResetCommand(ViewModel* p) throw();
    virtual void SetParameter(const std::any &param);
    virtual void Exec();

private:
    ViewModel* viewmodel_ptr;
    int m_param;
};

#endif // GAMERESETCOMMAND_H
