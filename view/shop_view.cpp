#include "shop_view.h"
#include "ui_shop_view.h"
#include <QDebug>
shop_view::shop_view(int money,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::shop_view)
{
    MONEY=money;
    ui->setupUi(this);
}

shop_view::~shop_view()
{
    delete ui;
}

void shop_view::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //绘制背景
    this->resize( QSize( 1266, 766 ));
    QPixmap pix;
    pix.load("G:/images/22");
    painter.drawPixmap(0,0,1266,766,pix);
    pix.load("G:/images/10");
    painter.drawPixmap(100,766/2,pix);
    pix.load("G:/images/11");
    painter.drawPixmap(300,766/2,pix);
    pix.load("G:/images/12");
    painter.drawPixmap(500,766/2,pix);
    pix.load("G:/images/13");
    painter.drawPixmap(700,766/2,pix);
    pix.load("G:/images/14");
    painter.drawPixmap(900,766/2,pix);
    pix.load("G:/images/23");
    painter.drawPixmap(1000,766/2,pix);
    QFont font;
    painter.setPen(QColor(Qt::white));
    font.setPointSize(15);
    painter.setFont(font);
    QTransform transform;
    // 获取字体信息
    QFontInfo info = painter.fontInfo();
    info.family();
    info.italic();
    // 转换
    painter.setTransform(transform);
    painter.drawText(50,766/2-100, QStringLiteral("大力药水："));
    painter.drawText(50,766/2-50, QStringLiteral("抓取速度增加"));
    painter.drawText(50,766/2+150, QStringLiteral("按下“1”购买"));
    painter.drawText(250,766/2-100, QStringLiteral("石头收藏书："));
    painter.drawText(250,766/2-50, QStringLiteral("石头变得更值钱"));
    painter.drawText(250,766/2+150, QStringLiteral("按下“2”购买"));
    painter.drawText(450,766/2-100, QStringLiteral("幸运草："));
    painter.drawText(450,766/2-50, QStringLiteral("更容易发现钻石"));
    painter.drawText(450,766/2+150, QStringLiteral("按下“3”购买"));
    painter.drawText(650,766/2-100, QStringLiteral("沙漏："));
    painter.drawText(650,766/2-50, QStringLiteral("下一局时间增加"));
    painter.drawText(650,766/2+150, QStringLiteral("按下“4”购买"));
    painter.drawText(850,766/2-100, QStringLiteral("炸药："));
    painter.drawText(850,766/2-50, QStringLiteral("炸毁已抓到的物品"));
    painter.drawText(850,766/2+150, QStringLiteral("按下“5”购买"));
}

void shop_view::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_1:
            qDebug() <<"ESC";
            break;
        case Qt::Key_2:
            qDebug() <<"ESC";
            break;
        case Qt::Key_3:
            qDebug() <<"ESC";
            break;
        case Qt::Key_4:
            qDebug() <<"ESC";
            break;
        case Qt::Key_5:
            qDebug() <<"ESC";
            break;
        case Qt::Key_Enter:
            qDebug() <<"ESC";
            break;
    }
}
