#include "viewmodelsink.h"
#include "../viewmodel.h"
ViewModelSink::ViewModelSink(ViewModel *p) throw():viewmodel_ptr(p)
{
}

void ViewModelSink::OnPropertyChanged(const std::string &str){
#ifndef NDEBUG
    qDebug() << "viewmodel sink get fire\nand send fire view_model->fireonPropertychange()\n";
#endif
    viewmodel_ptr->Fire_OnPropertyChanged(str);

}
