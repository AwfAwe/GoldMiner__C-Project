#ifndef UPDATESINK_H
#define UPDATESINK_H
#include "../../common/etlbase.h"

class view;

class updateSink: public IPropertyNotification
{
public:
    updateSink(view* ptr);
    virtual void OnPropertyChanged(const std::string &str);
private:
    view *mainwindow_ptr;
};

#endif // UPDATESINK_H
