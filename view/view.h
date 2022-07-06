#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QTimer>
#include <QKeyEvent>
#include <time.h>
#include "common.h"
#include "view\end_view.h"
#include "view\shop_view.h"
#include ".\viewmodel\viewmodelcommand.h"

typedef viewmodelcommand *VMptr;

namespace Ui {
class view;
}

class view : public QMainWindow
{
    Q_OBJECT

public:

    explicit view(QWidget *parent = nullptr, int playernumber = DEFAULT_PLAYER_NUM, int minenumber = DEFAULT_MINE_NUM);
    ~view();
    void loadImg();
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    QPixmap rotateImageWithTransform(const QPixmap &src, int angle);
    void setcoin(QVector<int>coins){for(int i=0;i<player_num;i++)role_coin[i]=coins[i];}
    void setplayer(int player_number=1){player_num=player_number;}
    void sethookposition(QVector<double>endx,QVector<double>endy,QVector<int>state,QVector<double>len,QVector<double>angle,QVector<int>dir);
    void setmine(QVector<double>x,QVector<double>y,QVector<int>type,QVector<bool>flag);

    void viewmodelinit();//

    void GetAll(); // only for initialization
    void SetPlayerCoin(int idx, int res);
    void SetMine(int idx, double x, double y, bool flag);
    void SetHook(int idx, double ex, double ey, double agl, int stt);


    void FrameOperation();
    void ClockChange();

    void settime(double time){countdown=time;}

    void setplayer1();
    void setplayer2();
    void setplayer3();

private:
    Ui::view *ui;
    int player_num;
    int mine_num;
    double countdown;

    QVector<double>role_x;
    QVector<double>role_y;
    QVector<int>role_coin;

    QVector<double>hook_x;
    QVector<double>hook_y;
    QVector<int>hook_state;

    QVector<double>hook_endx;
    QVector<double>hook_endy;
    QVector<double>hook_angle;

    QVector<double>mine_x;
    QVector<double>mine_y;
    QVector<int>mine_type;
    QVector<bool>mine_flag;


    VMptr vm_;
    QTimer Timer_frame, Timer_clock;
    int frameTime, clockTime;
    int cur_second;
    int stop_flag;
    int money;
};

#endif // VIEW_H
