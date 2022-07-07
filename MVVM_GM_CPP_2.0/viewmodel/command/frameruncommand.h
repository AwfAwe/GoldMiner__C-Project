#pragma once

#include "../../common/etlbase.h"

class ViewModel;

class FrameRunCommand: public ICommandBase
{
public:
    FrameRunCommand(ViewModel* p) throw();
    virtual void SetParameter(const std::any &param);
    virtual void Exec();
private:
    ViewModel* viewmodel_ptr;
    int m_param;
};

