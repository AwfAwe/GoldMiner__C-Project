#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QTimer>
#include <QKeyEvent>
#include <time.h>
#include "../common/etlbase.h"
#include "../common/precomp.h"
#include "./sinks/updatesink.h"
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

    void SetPlayersPosX(std::shared_ptr<POS>);
    void SetPlayersPosY(std::shared_ptr<POS>);
    void SetPlayersCoin(std::shared_ptr<COINS>);

    void SetHooksPosX(std::shared_ptr<POS>);
    void SetHooksPosY(std::shared_ptr<POS>);
    void SetHooksPosEndX(std::shared_ptr<POS>);
    void SetHooksPosEndY(std::shared_ptr<POS>);
    void SetHooksAngle(std::shared_ptr<ANGLES>);
    void SetHooksState(std::shared_ptr<STT>);

    void SetMinesPosX(std::shared_ptr<POS>);
    void SetMinesPosY(std::shared_ptr<POS>);
    void SetMinesType(std::shared_ptr<TYPES>);
    void SetMinesExist(std::shared_ptr<EXISTS>);


    void SetLevelGoal(std::shared_ptr<GOAL>);
    void SetBoomsNum(std::shared_ptr<int>);

    void setFrameRunCommand(const std::shared_ptr<ICommandBase>& cmd);
    void setPlayerSetCommand(const std::shared_ptr<ICommandBase>& cmd);
    void setGameResetCommand(const std::shared_ptr<ICommandBase>& cmd);
    void setItemsBuyCommand(const std::shared_ptr<ICommandBase>& cmd);
    void setUseBoomCommand(const std::shared_ptr<ICommandBase>& cmd);


    void FrameOperation();
    void PlayerSet(int idx);
    void GameReset();
    void ItemBuy(int item_id);
    void BoomUse(int idx);

    void ClockChange();
    void settime(double time){countdown=time;}
    void SetTimer();

    std::shared_ptr<IPropertyNotification> get_updateSink();

private:
    Ui::view *ui;
    int player_num;
    int mine_num;
    double countdown;
    std::shared_ptr<POS> role_x;
    std::shared_ptr<POS> role_y;
    std::shared_ptr<COINS> player_coin;

    std::shared_ptr<POS> hook_x;
    std::shared_ptr<POS> hook_y;
    std::shared_ptr<STT> hook_state;

    std::shared_ptr<POS> hook_endx;
    std::shared_ptr<POS> hook_endy;
    std::shared_ptr<ANGLES> hook_angle;

    std::shared_ptr<POS> mine_x;
    std::shared_ptr<POS> mine_y;
    std::shared_ptr<TYPES> mine_type;
    std::shared_ptr<EXISTS> mine_flag;

    std::shared_ptr<int> level_goal;
    std::shared_ptr<int> booms_num;

    std::shared_ptr<ICommandBase> m_cmdFrameRun;
    std::shared_ptr<ICommandBase> m_cmdPlayerSet;
    std::shared_ptr<ICommandBase> m_cmdGameReset;
    std::shared_ptr<ICommandBase> m_cmdItemsBuy;
    std::shared_ptr<ICommandBase> m_cmdUseBoom;

    std::shared_ptr<updateSink> m_updateSink;


    QTimer Timer_frame, Timer_clock;
    int frameTime, clockTime;
    int cur_second;
    int money;
    int level_id;
    int total_goal;
    int buy[6];

    double boom_x[3];
    double boom_y[3];
    int boom_time[3];
    int boom_flag[3];

    int page_flag;
    /*
      page_flag = 0 ::  Start_Page
      page_flag = 1 ::  Game_Page
      page_flag = 2 ::  result_page
      page_flag = 3 ::  shop_page
     */

};


#endif // GAMEVIEW_H
