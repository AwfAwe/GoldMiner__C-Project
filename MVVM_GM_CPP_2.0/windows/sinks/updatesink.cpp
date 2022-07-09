#include "updatesink.h"
#include "../gameview.h"

updateSink::updateSink(view *p):mainwindow_ptr(p)
{}

void updateSink::OnPropertyChanged(const std::string &str){
//    if(str == "Changed"){
     mainwindow_ptr->update();

//    }
}
