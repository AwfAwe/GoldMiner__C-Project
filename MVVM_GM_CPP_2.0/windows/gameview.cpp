#include "gameview.h"
//#include "ui_view.h"
#include "../common/precomp.h"
#include <QDebug>
#include <iostream>

char filename[40][20];
int i_up = 1, i_down = 0;
view::view(QWidget *parent, int playernumber, int minenumber):
    QMainWindow(parent),
//    ui(new Ui::view),
    player_num(playernumber),mine_num(minenumber),
    m_updateSink(std::make_shared<updateSink>(this))
{

    loadImg();
//    ui->setupUi(this);
    for(int i=0;i<6;i++)
        buy[i]=0;
    money=0;
    level_id = 0;
    page_flag = 0;
    cur_second = 0;
    boom_flag[0]=boom_flag[1]=boom_flag[2]=false;
    frameTime = 10;
    clockTime = 1000;
    Timer_frame.setInterval(frameTime);
    Timer_clock.setInterval(clockTime);
    connect(&Timer_frame, &QTimer::timeout, this, &view::FrameOperation);
    connect(&Timer_clock, &QTimer::timeout, this, &view::ClockChange);
}

void view::SetTimer(){
    std::cout<<"SetTimer!!"<<std::endl;
    cur_second = 0;
    Timer_frame.start();
    Timer_clock.start();

}

std::shared_ptr<IPropertyNotification> view::get_updateSink(){
    return std::static_pointer_cast<IPropertyNotification>(m_updateSink);
}

void view::SetPlayersPosX(std::shared_ptr<POS> ply_PosX){
    role_x = ply_PosX;
}

void view::SetPlayersPosY(std::shared_ptr<POS> ply_PosY){
    role_y = ply_PosY;
}

void view::SetPlayersCoin(std::shared_ptr<COINS> ply_Coin){
    player_coin = ply_Coin;
}

void view::SetHooksPosX(std::shared_ptr<POS> hk_PosX){
    hook_x = hk_PosX;
//    std::cout<<"View::"<<&((*hook_x)[0])<<std::endl;
}

void view::SetHooksPosY(std::shared_ptr<POS> hk_PosY){
    hook_y = hk_PosY;
}

void view::SetHooksPosEndX(std::shared_ptr<POS> hk_PosEndX){
    hook_endx = hk_PosEndX;
}

void view::SetHooksPosEndY(std::shared_ptr<POS> hk_PosEndY){
    hook_endy = hk_PosEndY;
}

void view::SetHooksAngle(std::shared_ptr<ANGLES> hk_Angle){
    hook_angle = hk_Angle;
}

void view::SetHooksState(std::shared_ptr<STT> hk_Stt){
    hook_state = hk_Stt;
}

void view::SetMinesPosX(std::shared_ptr<POS> mn_PosX){
    mine_x = mn_PosX;
}

void view::SetMinesPosY(std::shared_ptr<POS> mn_PosY){
    mine_y = mn_PosY;
}

void view::SetMinesType(std::shared_ptr<TYPES> mn_Type){
    mine_type = mn_Type;
}

void view::SetMinesExist(std::shared_ptr<EXISTS> mn_exi){
    mine_flag = mn_exi;
}

void view::SetLevelGoal(std::shared_ptr<GOAL> goal_){
    level_goal = goal_;
}

void view::SetBoomsNum(std::shared_ptr<int> boom_){
    booms_num = boom_;
}

void view::setFrameRunCommand(const std::shared_ptr<ICommandBase> &cmd){
    m_cmdFrameRun = cmd;
}

void view::setPlayerSetCommand(const std::shared_ptr<ICommandBase> &cmd){
    m_cmdPlayerSet = cmd;
}

void view::setGameResetCommand(const std::shared_ptr<ICommandBase> &cmd){
    m_cmdGameReset = cmd;
}

void view::setItemsBuyCommand(const std::shared_ptr<ICommandBase> &cmd){
    m_cmdItemsBuy = cmd;
}

void view::setUseBoomCommand(const std::shared_ptr<ICommandBase> &cmd){
    m_cmdUseBoom = cmd;
}

void view::FrameOperation(){
    m_cmdFrameRun->Exec();
    update();
}

void view::PlayerSet(int idx){
    m_cmdPlayerSet->SetParameter(idx);
    m_cmdPlayerSet->Exec();
}

void view::GameReset(){
    m_cmdGameReset->SetParameter(player_num);
    m_cmdGameReset->Exec();

    level_id ++;
    total_goal += *level_goal;

}

void view::ClockChange(){
    cur_second++;
    std::cout<<"Now Time is "<<cur_second<<std::endl;
    update();
}

void view::ItemBuy(int item_id){
    m_cmdItemsBuy->SetParameter(item_id);
    m_cmdItemsBuy->Exec();
}

void view::BoomUse(int idx){
    if(*booms_num<=0)return;
    m_cmdUseBoom->SetParameter(idx);
    m_cmdUseBoom->Exec();
    boom_flag[idx] = true;
    boom_x[idx]=*((*hook_endx)[idx]);
    boom_y[idx]=*((*hook_endy)[idx]);
    boom_time[idx] = cur_second;

}
view::~view(){
//    delete ui;
}

void view::loadImg()
{
    for (int i = 0; i < 20; i++)
        sprintf(filename[i], "G:/images/%d", i);
    sprintf(filename[20], "G:/images/bk");
    for (int i = 21; i < 40; i++)
        sprintf(filename[i], "G:/images/%d", i);
}

QPixmap view::rotateImageWithTransform(const QPixmap &src, int angle)
{
    QMatrix matri;
    //迁移到中心
    matri.translate(src.width()/2.0,src.height()/2.0);
    //中心旋转
    matri.rotate(angle);
    //回退中心
    
    
    matri.translate(-src.width()/2.0,-src.height()/2.0);
    //执行坐标映射变化
    //旋转后图像大小变化了 需要提前进行裁剪 如果在旋转后裁剪
    //则需要计算使用三角函数计算
    //中心偏移
    int cubeWidth = qMin(src.width(),src.height());
    QRect cubeRect(0,0,cubeWidth,cubeWidth);
    cubeRect.moveCenter(src.rect().center());
//        qDebug()<<" cube "<<cubeRect
//               <<" src rect "<<src.rect();

    auto retImg = src.copy(cubeRect);
    retImg = retImg.transformed(matri,Qt::SmoothTransformation);
    return retImg;
}


void view::keyPressEvent(QKeyEvent *event)
{
    if(page_flag == 1){

        switch(event->key()){

        case Qt::Key_S:
            PlayerSet(0);break;

        case Qt::Key_W:
            BoomUse(0);break;

        case Qt::Key_K:
            if(player_num>=2)PlayerSet(1);
            break;

        case Qt::Key_I:
            if(player_num>=2)BoomUse(1);
            break;

        case Qt::Key_Down:
            if(player_num>=3)PlayerSet(2);
            break;

        case Qt::Key_Up:
            if(player_num>=3)BoomUse(2);
            break;
        }
    }else if(page_flag==3){ //商店界面
        switch (event->key())
        {
            case Qt::Key_1:

                ItemBuy(1);
                break;
            case Qt::Key_2:
//                GameReset();
                ItemBuy(2);
                break;
            case Qt::Key_3:
//                GameReset();
                ItemBuy(3);
                break;
            case Qt::Key_4:
//                GameReset();
                ItemBuy(4);
                break;
            case Qt::Key_5:
//                GameReset();
                ItemBuy(5);
                break;
            case Qt::Key_Return:
//                std::cout<<"Enter"<<std::endl;
//                for(int i=0;i<6;i++)
//                    buy[i]=0;
                page_flag = 1;
                SetTimer();
                break;
        }


    }else if(page_flag==0){
        bool touch = false;
        switch (event->key()){
           case Qt::Key_Q:
               player_num=1;
               touch = true;
               break;
           case Qt::Key_W:
               player_num=2;
               touch = true;
               break;
           case Qt::Key_E:
               player_num=3 ;
               touch = true;
               break;
        }
        if(touch){
            GameReset();
            page_flag = 1;
            SetTimer();
        }
    }
}


void view::paintEvent(QPaintEvent *event)
{

    if(page_flag==1&&LEVELTIME-cur_second<=0+DEBUGTIME){
        page_flag = 2;
        Timer_frame.stop();

    }
    if(page_flag == 1){ // 游戏界面

        QPainter painter(this);
        //绘制背景
        this->resize( QSize( WIDTH, HEIGHT ));
        QPixmap pix;
        pix.load(filename[20]);
        painter.drawPixmap(0,140,WIDTH,HEIGHT-140,pix);
        pix.load(filename[15]);
        painter.drawPixmap(0,0,WIDTH,140,pix);

        //绘制人物
        for(int i=0;i<player_num;i++)
        {
            if (*((*hook_state)[i]) == M_NORMAL)
            {
                pix.load(filename[i_roleDown]);
                painter.drawPixmap(*((*role_x)[i]),*((*role_y)[i]),pix.width(),pix.height(),pix);
            }
            else
            {
                if (i_down%20<10)
                {
                    pix.load(filename[i_roleDown]);
                    painter.drawPixmap(*((*role_x)[i]),*((*role_y)[i]),pix.width(),pix.height(),pix);
                    i_down++;
                }
                else
                {
                    pix.load(filename[i_roleUp]);
                    painter.drawPixmap(*((*role_x)[i]),*((*role_y)[i]),pix.width(),pix.height(),pix);
                    i_down++;
                }
            }
        }

        //输出钱
        money = 0;
        for(int i=0;i<player_num;i++)
            money += *((*player_coin)[i]);
        QFont font;
        painter.setPen(QColor(Qt::black));
        font.setPointSize(30);
        painter.setFont(font);
        QTransform transform;
        // 获取字体信息
        QFontInfo info = painter.fontInfo();
        info.family();
        info.italic();
        // 转换
        painter.setTransform(transform);
        painter.drawText(rect(), QStringLiteral("金钱："));
        QString s = QString::number(money);
        painter.drawText(150, 42, s);
        for(int i=0;i<player_num;i++)
        {
            s = QString::number(*((*player_coin)[i]));
            painter.drawText(*((*role_x)[i])+40,*((*role_y)[i])*16, s);
        }

        //输出炸药
        pix.load(filename[14]);
        for(int i=0;i<*booms_num;i++)
            painter.drawPixmap(*((*role_x)[0])-10-30*i,*((*role_y)[0])*12,pix);
        //输出关卡目标
        painter.drawText(0,100, QStringLiteral("目标："));
        QString count = QString::number(*level_goal);
        painter.drawText(150, 100, count);

        //输出时间
        painter.drawText(900,100, QStringLiteral("时间："));
        count = QString::number(LEVELTIME-cur_second);
        painter.drawText(1050, 100, count);

        //输出当前关卡id
        painter.drawText(900, 42, QStringLiteral("关卡："));
        count = QString::number(level_id);
        painter.drawText(1050, 42, count);

        //绘制钩子
        QPixmap pix2,pix3;
        QPen pen;
        painter.setPen(QPen(Qt::black,5));
        pix.load(filename[25]);
        pix2.load(filename[25]);
        pix3.load(filename[25]);
        for(int i=0;i<player_num;i++)
        {
            painter.drawLine(QPoint(*((*hook_x)[i]),*((*hook_y)[i])),QPoint(*((*hook_endx)[i]),*((*hook_endy)[i])));
            if(!i)
            {
                pix=rotateImageWithTransform(pix, -*((*hook_angle)[i]));
                painter.drawPixmap(*((*hook_endx)[i]) - 18, *((*hook_endy)[i]) - 24,pix);
            }
            if(i==1)
            {
                pix2=rotateImageWithTransform(pix2, -*((*hook_angle)[i]));
                painter.drawPixmap(*((*hook_endx)[i]) - 18, *((*hook_endy)[i]) - 24,pix2);
            }
            if(i==2)
            {
                pix3=rotateImageWithTransform(pix3, -*((*hook_angle)[i]));
                painter.drawPixmap(*((*hook_endx)[i]) - 18, *((*hook_endy)[i]) - 24,pix3);
            }

        }

        //画金子
        for (int i = 0; i < DEFAULT_MINE_NUM; i++) {
            if (*((*mine_flag)[i]) == true) {
                switch (*((*mine_type)[i]))
                {
                    case LITTLEGOLD:
                        pix.load(filename[i_goldsmall]);
                        painter.drawPixmap(*((*mine_x)[i]), *((*mine_y)[i]),pix);
                        break;
                    case MIDGOLD:
                        pix.load(filename[i_goldmiddle]);
                        painter.drawPixmap(*((*mine_x)[i]), *((*mine_y)[i]),pix);
                        break;
                    case BIGGOLD:
                        pix.load(filename[i_goldbig]);
                        painter.drawPixmap(*((*mine_x)[i]), *((*mine_y)[i]),pix);
                        break;
                    case LITTLESTONE:
                        pix.load(filename[i_stonesmall]);
                        painter.drawPixmap(*((*mine_x)[i]), *((*mine_y)[i]),pix);
                        break;
                    case BIGSTONE:
                        pix.load(filename[i_stonebig]);
                        painter.drawPixmap(*((*mine_x)[i]), *((*mine_y)[i]),pix);
                        break;
                    case MONEY:
                        pix.load(filename[i_money]);
                        painter.drawPixmap(*((*mine_x)[i]), *((*mine_y)[i]),pix);
                        break;
                    case DIAMOND:
                        pix.load(filename[i_diamond]);
                        painter.drawPixmap(*((*mine_x)[i]), *((*mine_y)[i]),pix);
                        break;
                }
            }
        }

        //画爆炸效果
        pix.load(filename[26]);
        for(int i = 0; i<player_num; ++i){
            if(boom_flag[i]){

                painter.drawPixmap(boom_x[i], boom_y[i], pix);
                if(cur_second - boom_time[i]>=1)
                    boom_flag[i] = 0;
            }
        }

    }else if(page_flag == 2){ // 每局游戏的结算界面
        QPainter painter(this);
        //绘制背景
        this->resize( QSize( 1266, 766 ));
        QPixmap pix;
        pix.load("G:/images/18");
        painter.drawPixmap(0,0,1266,766,pix);
        QFont font;
        painter.setPen(QColor(Qt::yellow));
        font.setPointSize(30);
        painter.setFont(font);
        QTransform transform;
        // 获取字体信息
        QFontInfo info = painter.fontInfo();
        info.family();
        info.italic();
        // 转换
        painter.setTransform(transform);
        if(money>=*level_goal)
            painter.drawText(1266/2-80,766/2-100, QStringLiteral("通关成功"));
        else
        {
             painter.drawText(1266/2-80,766/2-100, QStringLiteral("通关失败"));
             painter.drawText(1266/2-180,766/2, QStringLiteral("您的最后得分："));
             QString s = QString::number(money);
             painter.drawText(1266/2+150,766/2, s);
             return;
        }
        painter.drawText(1266/2-80,766/2, QStringLiteral("得分："));
        QString s = QString::number(money);
        painter.drawText(1266/2+50,766/2, s);
        if(LEVELTIME-cur_second<=-2+DEBUGTIME){
            page_flag=3;
            GameReset();
        }
        return;

    }else if(page_flag==3){ //商店界面
        QPainter painter(this);
                //绘制背景
        this->resize( QSize( 1266, 766 ));
        QPixmap pix;
        pix.load("G:/images/22");
        painter.drawPixmap(0,0,1266,766,pix);
        QFont font;

        painter.setPen(QColor(Qt::yellow));
        money = 0;
        for(int i=0;i<player_num;i++)
            money += *((*player_coin)[i]);
        font.setPointSize(30);
        painter.setFont(font);
        QTransform transform;
        // 获取字体信息
        QFontInfo info = painter.fontInfo();
        info.family();
        info.italic();
        // 转换
        painter.setTransform(transform);
        painter.drawText(80, 82, QStringLiteral("当前金钱："));
        QString s = QString::number(money);
        painter.drawText(300, 82, s);
//        for(int i=0;i<player_num;i++)
//        {
//            s = QString::number(*((*player_coin)[i]));
//            painter.drawText(*((*role_x)[i])+40,*((*role_y)[i])*16, s);
//        }

        painter.setPen(QColor(Qt::white));
        font.setPointSize(15);
        painter.setFont(font);
//        QTransform transform;
        // 获取字体信息
        info = painter.fontInfo();
        info.family();
        info.italic();
        // 转换
        painter.setTransform(transform);


        if(!buy[1])
        {
            pix.load("G:/images/10");
            painter.drawPixmap(100,766/2,pix);
            painter.drawText(50,766/2-100, QStringLiteral("大力药水："));
            painter.drawText(50,766/2-50, QStringLiteral("抓取速度增加"));
            painter.drawText(50,766/2+100, QStringLiteral("价格：100/个"));
            painter.drawText(50,766/2+150, QStringLiteral("按下“1”购买"));
        }
        if(!buy[2])
        {
            pix.load("G:/images/11");
            painter.drawPixmap(300,766/2,pix);
            painter.drawText(250,766/2-100, QStringLiteral("石头收藏书："));
            painter.drawText(250,766/2-50, QStringLiteral("石头变得更值钱"));
            painter.drawText(250,766/2+100, QStringLiteral("价格：50"));
            painter.drawText(250,766/2+150, QStringLiteral("按下“2”购买"));
        }
        if(!buy[3])
        {
            pix.load("G:/images/12");
            painter.drawPixmap(500,766/2,pix);
            painter.drawText(450,766/2-100, QStringLiteral("幸运草："));
            painter.drawText(450,766/2-50, QStringLiteral("更容易发现钻石"));
            painter.drawText(450,766/2+100, QStringLiteral("价格：100"));
            painter.drawText(450,766/2+150, QStringLiteral("按下“3”购买"));
        }
        if(!buy[4])
        {
            pix.load("G:/images/13");
            painter.drawPixmap(700,766/2,pix);
            painter.drawText(650,766/2-100, QStringLiteral("沙漏："));
            painter.drawText(650,766/2-50, QStringLiteral("下一局时间增加"));
            painter.drawText(650,766/2+100, QStringLiteral("价格：200"));
            painter.drawText(650,766/2+150, QStringLiteral("按下“4”购买"));
        }
        if(!buy[5])
        {
            pix.load("G:/images/14");
            painter.drawPixmap(900,766/2,pix);
            painter.drawText(850,766/2-100, QStringLiteral("炸药："));
            painter.drawText(850,766/2-50, QStringLiteral("炸毁已抓到的物品"));
            painter.drawText(850,766/2+100, QStringLiteral("价格：100/个"));
            painter.drawText(850,766/2+150, QStringLiteral("按下“5”购买"));
        }
        painter.drawText(350,766/2+300, QStringLiteral("按下“ENTER”继续游戏"));
        pix.load("G:/images/23");
        painter.drawPixmap(1000,766/2,pix);

    }else if(page_flag == 0){
        QPainter painter(this);
        //绘制背景
        this->resize( QSize( 1266, 766 ));
        QPixmap pix;
        pix.load("G:/images/16");
        painter.drawPixmap(0,0,1266,766,pix);
        QFont font;
        painter.setPen(QColor(Qt::blue));
        font.setPointSize(15);
        painter.setFont(font);
        QTransform transform;
        // 获取字体信息
        QFontInfo info = painter.fontInfo();
        info.family();
        info.italic();
        // 转换
        painter.setTransform(transform);
//        painter.drawText(120,200, QStringLiteral("按下“Q”开始单人模式 按下“W”开始双人模式 按下“E”开始三人模式"));
        painter.drawText(150,220, QStringLiteral("按下“Q”开始单人模式"));
        painter.drawText(150,260, QStringLiteral("按下“W”开始双人模式"));
        painter.drawText(150,300, QStringLiteral("按下“E”开始三人模式"));
        painter.setPen(QColor(Qt::white));
        painter.setFont(font);
        // 获取字体信息
        info = painter.fontInfo();
        info.family();
        info.italic();
        // 转换
        painter.setTransform(transform);
        painter.drawText(100,520, QStringLiteral("玩家1: S——放钩子 W——放炸药"));
        painter.drawText(100,620, QStringLiteral("玩家2: K——放钩子 I——放炸药"));
        painter.drawText(100,720, QStringLiteral("玩家3: 方向键下——放钩子 方向键上——放炸药"));
    }

}
