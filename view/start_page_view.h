#ifndef START_PAGE_VIEW_H
#define START_PAGE_VIEW_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QMouseEvent>
namespace Ui {
class start_page_view;
}

class start_page_view : public QMainWindow
{
    Q_OBJECT

public:
    explicit start_page_view(QWidget *parent = nullptr);
    ~start_page_view();
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::start_page_view *ui;
};

#endif // START_PAGE_VIEW_H
