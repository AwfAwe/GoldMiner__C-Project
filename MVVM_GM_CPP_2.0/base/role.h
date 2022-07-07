#ifndef ROLE_H
#define ROLE_H
#include "../common/precomp.h"

class Role{

private:
    double x;
    double y;
    double width;
    double height;
public:
    Role(int id, int totid);
    double& GetRolex(){return x;}
    double& GetRoley(){return y;}
};


#endif // ROLE_H
