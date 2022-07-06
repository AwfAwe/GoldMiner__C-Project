#ifndef END_VIEW_H
#define END_VIEW_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <time.h>
#include "view/shop_view.h"
namespace Ui {
class end_view;
}

class end_view : public QMainWindow
{
    Q_OBJECT

public:
    explicit end_view(int mon,QWidget *parent = nullptr);
    ~end_view();
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::end_view *ui;
    int money;
};

#endif // END_VIEW_H
