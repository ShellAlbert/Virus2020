#include "zvideoui.h"
#include <QPainter>
ZVideoUI::ZVideoUI(QWidget *parent) : QWidget(parent)
{

}
QSize ZVideoUI::sizeHint() const
{
    return QSize(400,300);
}
void ZVideoUI::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.fillRect(this->rect(),Qt::black);
}
