#include "start_page_view.h"
#include "ui_start_page_view.h"
#include "view.h"
#include <QDebug>
//#include "form.h"
start_page_view::start_page_view(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::start_page_view)
{
    ui->setupUi(this);
}

start_page_view::~start_page_view()
{
    delete ui;
}

void start_page_view::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //绘制背景
    this->resize( QSize( 1266, 766 ));
    QPixmap pix;
    pix.load("G:/images/16");
    painter.drawPixmap(0,0,1266,766,pix);
    QFont font;
    painter.setPen(QColor(Qt::black));
    font.setPointSize(50);
    painter.setFont(font);
    QTransform transform;
    // 获取字体信息
    QFontInfo info = painter.fontInfo();
    info.family();
    info.italic();
    // 转换
    painter.setTransform(transform);
    painter.drawText(220,250, QStringLiteral("开始"));


}


void start_page_view::on_pushButton_clicked()
{
    qDebug()<<"chu"<<endl;
    view *widget2 = new view();
    this->hide();
    widget2->show();

}
