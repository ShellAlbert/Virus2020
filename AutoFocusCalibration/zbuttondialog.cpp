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
    this->m_btnLoad->setText(tr("Load"));

    this->m_btnMdy=new QToolButton;
    this->m_btnMdy->setText(tr("Modify"));

    this->m_btnSave=new QToolButton;
    this->m_btnSave->setText(tr("Save"));

    this->m_btnCallOne=new QToolButton;
    this->m_btnCallOne->setText(tr("CallOne"));

    this->m_btnCallAll=new QToolButton;
    this->m_btnCallAll->setText(tr("CallAll"));

    this->ZAddButton(this->m_btnLoad,1);
    this->ZAddButton(this->m_btnMdy,2);
    this->ZAddButton(this->m_btnSave,3);
    this->ZAddButton(this->m_btnCallOne,3);
    this->ZAddButton(this->m_btnCallAll,3);
}
ZDataDialog::~ZDataDialog()
{
    delete this->m_btnLoad;
    delete this->m_btnMdy;
    delete this->m_btnSave;
    delete this->m_btnCallOne;
    delete this->m_btnCallAll;
}
