#ifndef VIEWMODELCOMMAND_H
#define VIEWMODELCOMMAND_H
#include "common.h"
#include "viewmodelctrl.h"
#include "QVector"

class view;
class viewmodelcommand : public viewmodelctrl
{
public:
    viewmodelcommand(view* vm, int plynm=DEFAULT_PLAYER_NUM, int mnnum=DEFAULT_MINE_NUM);
    void GetAllMines(QVector<double>&, QVector<double>&, QVector<int>&, QVector<bool>&);

    void GetAllPlayers(QVector<double>&, QVector<double>&, QVector<int>&,
                       QVector<double>&, QVector<double>&, QVector<int>&,
                       QVector<double>&, QVector<double>&, QVector<double>&);

private:
    view* view_;

};

#endif // VIEWMODELCOMMAND_H
