#ifndef SHOP_VIEW_H
#define SHOP_VIEW_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QKeyEvent>
namespace Ui {
class shop_view;
}

class shop_view : public QMainWindow
{
    Q_OBJECT

public:
    explicit shop_view(int money,QWidget *parent = nullptr);
    ~shop_view();
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::shop_view *ui;
    int MONEY;
};

#endif // SHOP_VIEW_H
