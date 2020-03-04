#include "zrssiui.h"

ZRssiUI::ZRssiUI(QWidget *parent) : QWidget(parent)
{
    this->m_vLayout=new QVBoxLayout;
    for(qint32 i=0;i<10;i++)
    {
        this->m_tb[i]=new QToolButton;
        this->m_vLayout->addWidget(this->m_tb[i]);
    }
    this->setLayout(this->m_vLayout);
}
ZRssiUI::~ZRssiUI()
{
    for(qint32 i=0;i<10;i++)
    {
        delete this->m_tb[i];
    }
    delete this->m_vLayout;
}
