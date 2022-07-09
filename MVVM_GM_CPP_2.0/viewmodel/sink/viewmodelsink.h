#ifndef VIEWMODELSINK_H
#define VIEWMODELSINK_H
#include "../../common/etlbase.h"

class ViewModel;


class ViewModelSink:public IPropertyNotification
{
public:
    ViewModelSink(ViewModel *p) throw();
    virtual void OnPropertyChanged(const std::string& str);
private:
    ViewModel* viewmodel_ptr;
};

#endif // VIEWMODELSINK_H
