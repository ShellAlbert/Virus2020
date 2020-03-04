#include "zvideoui.h"

ZVideoUI::ZVideoUI(QWidget *parent) : QWidget(parent)
{

}
QSize ZVideoUI::sizeHint() const
{
    return QSize(400,300);
}
