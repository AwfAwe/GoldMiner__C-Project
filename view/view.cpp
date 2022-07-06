#include "view.h"
#include "ui_view.h"
#include "common.h"
#include <QDebug>
using std::cout, std::endl;
char filename[40][20];
int i_up = 1, i_down = 0;
view::view(QWidget *parent, int playernumber, int minenumber):
    QMainWindow(parent),
    ui(new Ui::view),
  player_num(playernumber),
  mine_num(minenumber)
{

    loadImg();
    ui->setupUi(this);
    viewmodelinit();
    GetAll();
    stop_flag = false;
    frameTime = 10;
    clockTime = 1000;
    cur_second = 0;
    money=0;
    Timer_frame.setInterval(frameTime);
    Timer_clock.setInterval(clockTime);
    connect(&Timer_frame, &QTimer::timeout, this, &view::FrameOperation);
    connect(&Timer_clock, &QTimer::timeout, this, &view::ClockChange);
    Timer_frame.start();
    Timer_clock.start();
}
void view::FrameOperation(){
    vm_->FrameOperation();
    GetAll();
    update();
//    show();
}
void view::ClockChange(){
    cur_second ++;
}


void view::GetAll(){
    role_x.clear();
    role_y.clear();
    role_coin.clear();
    hook_x.clear();
    hook_y.clear();
    hook_state.clear();
    hook_endx.clear();
    hook_endy.clear();
    hook_angle.clear();
    mine_x.clear();
    mine_y.clear();
    mine_type.clear();
    mine_flag.clear();

    vm_->GetAllPlayers(role_x, role_y, role_coin, hook_x, hook_y, hook_state, hook_endx, hook_endy, hook_angle);
    vm_->GetAllMines(mine_x, mine_y, mine_type, mine_flag);
}

void view::SetPlayerCoin(int idx, int res){
    role_coin[idx]=res;
}

void view::SetMine(int idx, double x, double y, bool flag){
    mine_x[idx]=x;
    mine_y[idx]=y;
    mine_flag[idx]=flag;
}

void view::SetHook(int idx, double ex, double ey, double agl, int stt){
    hook_endx[idx]=ex;
    hook_endy[idx]=ey;
    hook_angle[idx]=agl;
    hook_state[idx]=stt;
    update();
}


void view::viewmodelinit(){
    vm_ = (VMptr)malloc(sizeof(viewmodelcommand));
    new(vm_) viewmodelcommand(this, player_num, mine_num);
}

view::~view(){
    delete ui;
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
        qDebug()<<" cube "<<cubeRect
               <<" src rect "<<src.rect();

        auto retImg = src.copy(cubeRect);
        retImg = retImg.transformed(matri,Qt::SmoothTransformation);
        return retImg;
}

void view::setplayer1(){
    vm_->FetchOperation(1);
}
void view::setplayer2(){
    vm_->FetchOperation(2);
}
void view::setplayer3(){
    vm_->FetchOperation(3);
}
void view::keyPressEvent(QKeyEvent *event)
{
    if(player_num==1)
    {
        switch (event->key())
        {
            case Qt::Key_Down:
                setplayer1();
                break;
        }
    }
    else if(player_num==2)
    {
        switch (event->key())
        {
            case Qt::Key_Down:
                setplayer1();
                break;
            case Qt::Key_S:
               setplayer2();
                break;
        }
    }
    else
    {
        switch (event->key())
        {
            case Qt::Key_Down:
                setplayer1();
                break;
            case Qt::Key_S:
               setplayer2();
                break;
            case Qt::Key_K:
               setplayer3();
                break;
        }
    }
}


void view::paintEvent(QPaintEvent *event)
{
    if(stop_flag)return;
    if(LEVELTIME-cur_second<=0)
        {
            stop_flag = true;
            Timer_frame.stop();
            Timer_clock.stop();
            end_view *widget2 = new end_view(money);
            this->hide();
            widget2->show();

        }
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
        if (hook_state[i] == M_NORMAL)
            {
                pix.load(filename[i_roleDown]);
                painter.drawPixmap(role_x[i],role_y[i],pix.width(),pix.height(),pix);
            }
            else
            {
                if (i_down%20<10)
                {
                    pix.load(filename[i_roleDown]);
                    painter.drawPixmap(role_x[i],role_y[i],pix.width(),pix.height(),pix);
                    i_down++;
                }
                else
                {
                    pix.load(filename[i_roleUp]);
                    painter.drawPixmap(role_x[i],role_y[i],pix.width(),pix.height(),pix);
                    i_down++;
                }
            }
    }

    //输出钱
    money = 0;
    for(int i=0;i<player_num;i++)
        money += role_coin[i];
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
        s = QString::number(role_coin[i]);
        painter.drawText(role_x[i]+40,role_y[i]*16, s);
    }

    //输出时间
    painter.drawText(0,100, QStringLiteral("时间："));
    QString count = QString::number(LEVELTIME-cur_second);
    painter.drawText(150, 100, count);
    //绘制钩子
    QPixmap pix2,pix3;
    QPen pen;
    painter.setPen(QPen(Qt::black,5));
    pix.load(filename[25]);
    pix2.load(filename[25]);
    pix3.load(filename[25]);
    for(int i=0;i<player_num;i++)
    {
        painter.drawLine(QPoint(hook_x[i],hook_y[i]),QPoint(hook_endx[i],hook_endy[i]));
        if(!i)
        {
            pix=rotateImageWithTransform(pix, -hook_angle[i]);
            painter.drawPixmap(hook_endx[i] - 18, hook_endy[i] - 24,pix);
        }
        if(i==1)
        {
            pix2=rotateImageWithTransform(pix2, -hook_angle[i]);
            painter.drawPixmap(hook_endx[i] - 18, hook_endy[i] - 24,pix2);
        }
        if(i==2)
        {
            pix3=rotateImageWithTransform(pix3, -hook_angle[i]);
            painter.drawPixmap(hook_endx[i] - 18, hook_endy[i] - 24,pix3);
        }

    }

    //画金子
    for (int i = 0; i < DEFAULT_MINE_NUM; i++) {
            if (mine_flag[i] == true) {
                switch (mine_type[i]) {
                case LITTLEGOLD:
                    pix.load(filename[i_goldsmall]);
                    painter.drawPixmap(mine_x[i], mine_y[i],pix);
                    break;
                case MIDGOLD:
                    pix.load(filename[i_goldmiddle]);
                    painter.drawPixmap(mine_x[i], mine_y[i],pix);
                    break;
                case BIGGOLD:
                    pix.load(filename[i_goldbig]);
                    painter.drawPixmap(mine_x[i], mine_y[i],pix);
                    break;
                case LITTLESTONE:
                    pix.load(filename[i_stonesmall]);
                    painter.drawPixmap(mine_x[i], mine_y[i],pix);
                    break;
                case BIGSTONE:
                    pix.load(filename[i_stonebig]);
                    painter.drawPixmap(mine_x[i], mine_y[i],pix);
                    break;
                case MONEY:
                    pix.load(filename[i_money]);
                    painter.drawPixmap(mine_x[i], mine_y[i],pix);
                    break;
                case DIAMOND:
                    pix.load(filename[i_diamond]);
                    painter.drawPixmap(mine_x[i], mine_y[i],pix);
                    break;
                }
            }
        }
}

void view::sethookposition(QVector<double>endx,QVector<double>endy,QVector<int>state,QVector<double>len,QVector<double>angle,QVector<int>dir)
 {
     hook_endx=endx;
     hook_endy=endy;
//     hook_state=state;
//     hook_len=len;
     hook_angle=angle;
//     hook_dir=dir;
 }

 void view::setmine(QVector<double>x,QVector<double>y,QVector<int>type,QVector<bool>flag)
 {
     mine_x=x;
     mine_y=y;
     mine_type=type;
     mine_flag=flag;
 }

