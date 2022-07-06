#include "end_view.h"
#include "ui_end_view.h"

end_view::end_view(int mon,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::end_view)
{
    money=mon;
    ui->setupUi(this);
}

end_view::~end_view()
{
    delete ui;
}

void end_view::paintEvent(QPaintEvent *event)
{
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
    if(money>=0)
        painter.drawText(1266/2-80,766/2-100, QStringLiteral("通关成功"));
    else
        painter.drawText(1266/2-80,766/2-100, QStringLiteral("通关失败"));
    painter.drawText(1266/2-80,766/2, QStringLiteral("得分："));
    QString s = QString::number(money);
    painter.drawText(1266/2+50,766/2, s);
    shop_view *widget2 = new shop_view(money);
    this->hide();
    widget2->show();
}

void end_view::keyPressEvent(QKeyEvent *event)
{

}
