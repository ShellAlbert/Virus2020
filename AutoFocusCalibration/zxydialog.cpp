#include "zxydialog.h"
#include <QMessageBox>
ZXYDialog::ZXYDialog(const QPointF &pt,QWidget *parent):QDialog(parent)
{
    this->setMinimumSize(400,200);

    this->m_llTips[0]=new QLabel(tr("测距值"));
    this->m_llTips[1]=new QLabel(tr("编码器值"));

    this->m_llXY[0]=new QLabel(QString::number(pt.x()));
    this->m_llXY[1]=new QLabel(QString::number(pt.y()));

    this->m_tb[0]=new QToolButton;
    this->m_tb[0]->setText(tr("召唤"));
    QObject::connect(this->m_tb[0],SIGNAL(clicked()),this,SLOT(ZSlotCallData()));

    this->m_tb[1]=new QToolButton;
    this->m_tb[1]->setText(tr("关闭"));
    QObject::connect(this->m_tb[1],SIGNAL(clicked()),this,SLOT(accept()));

    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_llTips[0],0,0);
    this->m_gridLayout->addWidget(this->m_llTips[1],0,1);
    this->m_gridLayout->addWidget(this->m_llXY[0],1,0);
    this->m_gridLayout->addWidget(this->m_llXY[1],1,1);
    this->m_gridLayout->addWidget(this->m_tb[0],2,0);
    this->m_gridLayout->addWidget(this->m_tb[1],2,1);

    this->setLayout(this->m_gridLayout);
}
ZXYDialog::~ZXYDialog()
{
    delete this->m_llTips[0];
    delete this->m_llTips[1];

    delete this->m_llXY[0];
    delete this->m_llXY[1];

    delete this->m_tb[0];
    delete this->m_tb[1];

    delete this->m_gridLayout;
}
void ZXYDialog::ZSlotCallData()
{
    QMessageBox::information(this,tr("Tips"),tr("召唤数据代码暂未实现"));
}
