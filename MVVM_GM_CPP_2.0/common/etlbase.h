#pragma once
/********************************************/
#include <memory>
#include <any>
#include <vector>
#include <map>
#include <stack>
#include <array>
#define NDEBUG



typedef unsigned char    uchar;
typedef unsigned short   ushort;
typedef unsigned int     uint;
typedef unsigned __int64 uint64;
typedef __int64          int64;

class ICommandBase{
public:

    virtual void SetParameter(const std::any& param) = 0;
    virtual void Exec() = 0;
};

template <class T>
class NotificationImpl{
public:
    void Clear() throw()
    {
        noty_array.clear();
    }
    void AddNotification(const std::shared_ptr<T>& p)
    {
        noty_array.push_back(p);
    }
    void RemoveNotification(const std::shared_ptr<T>& p) throw()
    {
        auto iter(noty_array.begin());
        for( ; iter != noty_array.end(); ++iter){
            if((*iter).get() == p.get()){
                noty_array.erase(iter);
                return;
            }
        }
    }
protected:
    std::vector<std::shared_ptr<T>> noty_array;
};

class IPropertyNotification{
public:
    virtual void OnPropertyChanged(const std::string& str) = 0;

};

class ICommandNotification
{
public:
    virtual void OnCommandComplete(const std::string& str, bool bOK) = 0;

};

template <class T>
class Proxy_PropertyNotification : public NotificationImpl<IPropertyNotification>
{
public:
    void AddPropertyNotification(const std::shared_ptr<IPropertyNotification>& p){
        AddNotification(p);
    }
    void RemovePropertyNotificaiton(const std::shared_ptr<IPropertyNotification>& p) throw()
    {
        RemoveNotification(p);
    }
    void Fire_OnPropertyChanged(const std::string& str){
        auto iter(noty_array.begin());
        for( ; iter != noty_array.end(); ++iter){
            (*iter)->OnPropertyChanged(str);
        }
    }
};


















