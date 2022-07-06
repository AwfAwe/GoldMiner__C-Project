#ifndef ROLE_H
#define ROLE_H
#include "..\common.h"

class Role {

private:
    double x;
    double y;
    double width;
    double height;
public:
    Role(int id, int totid);
    int GetRolex(){return x;}
    int GetRoley(){return y;}
};


#endif // ROLE_H
