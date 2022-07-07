#ifndef APP_H
#define APP_H
#include "../model/model.h"
#include "../viewmodel/viewmodel.h"
#include "../windows/gameview.h"
class app
{
public:
    app();
    ~app();
    view* GetMainWindow();
    std::shared_ptr<ViewModel> GetViewModel();
    void run();
private:
    view _mainwindow;
    std::shared_ptr<model> model_ptr;
    std::shared_ptr<ViewModel> viewmodel_ptr;

};

#endif // APP_H
