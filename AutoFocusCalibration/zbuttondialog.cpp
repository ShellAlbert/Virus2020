#include "zbuttondialog.h"

ZButtonDialog::ZButtonDialog(QWidget *parent):QDialog(parent)
{
    this->setMinimumSize(400,200);
    this->m_hLayout=new QHBoxLayout;
    this->setLayout(this->m_hLayout);
}
ZButtonDialog::~ZButtonDialog()
{
    this->m_map.clear();
    delete this->m_hLayout;
}
void ZButtonDialog::ZAddButton(QToolButton *btn,qint32 bindNum)
{
    if(this->m_map.contains(btn))
    {
        //already exists.
        return;
    }
    this->m_map.insert(btn,bindNum);
    this->m_hLayout->addWidget(btn);
    QObject::connect(btn,SIGNAL(clicked()),this,SLOT(ZSlotBtnClicked()));
}
qint32 ZButtonDialog::ZGetClickedBindNum()
{
    return this->m_clickedBindNum;
}
void ZButtonDialog::ZSlotBtnClicked()
{
    QToolButton* btn=qobject_cast<QToolButton*>(this->sender());
    if(this->m_map.contains(btn))
    {
        this->m_clickedBindNum=this->m_map.value(btn);
    }else{
        this->m_clickedBindNum=0;
    }
    this->accept();
}
ZDataDialog::ZDataDialog(QWidget *parent):ZButtonDialog(parent)
{
    this->m_btnLoad=new QToolButton;
    this->m_btnLoad->setText(tr("载入"));

    this->m_btnMdy=new QToolButton;
    this->m_btnMdy->setText(tr("修改"));

    this->m_btnSave=new QToolButton;
    this->m_btnSave->setText(tr("存档"));

    this->ZAddButton(this->m_btnLoad,1);
    this->ZAddButton(this->m_btnMdy,2);
    this->ZAddButton(this->m_btnSave,3);
}
ZDataDialog::~ZDataDialog()
{
    delete this->m_btnLoad;
    delete this->m_btnMdy;
    delete this->m_btnSave;
}
