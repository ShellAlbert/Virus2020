#include "zdatamdydialog.h"
#include <QHeaderView>
ZDataMdyDialog::ZDataMdyDialog(const QList<QPointF> &listPt,QWidget *parent):QDialog(parent)
{
    this->m_btnAdd=new QToolButton;
    this->m_btnAdd->setText(tr("ADD"));
    QObject::connect(this->m_btnAdd,SIGNAL(clicked()),this,SLOT(ZSlotAdd()));

    this->m_btnDel=new QToolButton;
    this->m_btnDel->setText(tr("DEL"));
    QObject::connect(this->m_btnDel,SIGNAL(clicked()),this,SLOT(ZSlotDel()));

    this->m_btnCleanAll=new QToolButton;
    this->m_btnCleanAll->setText(tr("CLEAR"));
    QObject::connect(this->m_btnCleanAll,SIGNAL(clicked()),this,SLOT(ZSlotCleanAll()));

    this->m_btnOkay=new QToolButton;
    this->m_btnOkay->setText(tr("OK"));
    QObject::connect(this->m_btnOkay,SIGNAL(clicked()),this,SLOT(ZSlotOkay()));

    this->m_hLayoutBtns=new QHBoxLayout;
    this->m_hLayoutBtns->addWidget(this->m_btnAdd);
    this->m_hLayoutBtns->addWidget(this->m_btnDel);
    this->m_hLayoutBtns->addWidget(this->m_btnCleanAll);
    this->m_hLayoutBtns->addWidget(this->m_btnOkay);

    this->m_tableWidget=new QTableWidget;
    this->m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->m_tableWidget->setColumnCount(2);
    this->m_tableWidget->setRowCount(listPt.size());
    for(qint32 i=0;i<listPt.size();i++)
    {
        QTableWidgetItem *itemDistance=new QTableWidgetItem;
        itemDistance->setTextAlignment(Qt::AlignCenter);
        itemDistance->setText(QString::number(listPt.at(i).x()));

        QTableWidgetItem *itemEncoder=new QTableWidgetItem;
        itemEncoder->setTextAlignment(Qt::AlignCenter);
        itemEncoder->setText(QString::number(listPt.at(i).y()));

        this->m_tableWidget->setItem(i,0,itemDistance);
        this->m_tableWidget->setItem(i,1,itemEncoder);
    }
    QStringList sListHeader;
    sListHeader<<"Distance(m)"<<"Encoder(Pluse)";
    this->m_tableWidget->setHorizontalHeaderLabels(sListHeader);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_tableWidget);
    this->m_vLayout->addLayout(this->m_hLayoutBtns);
    this->setLayout(this->m_vLayout);
}
ZDataMdyDialog::~ZDataMdyDialog()
{
    delete this->m_btnAdd;
    delete this->m_btnDel;
    delete this->m_btnCleanAll;
    delete this->m_btnOkay;
    delete this->m_hLayoutBtns;

    this->m_tableWidget->clear();
    delete this->m_tableWidget;
    delete this->m_vLayout;
}

void ZDataMdyDialog::ZSlotAdd()
{
    this->m_tableWidget->setRowCount(this->m_tableWidget->rowCount()+1);

    QTableWidgetItem *itemDistance=new QTableWidgetItem;
    itemDistance->setTextAlignment(Qt::AlignCenter);

    QTableWidgetItem *itemEncoder=new QTableWidgetItem;
    itemEncoder->setTextAlignment(Qt::AlignCenter);

    this->m_tableWidget->setItem(this->m_tableWidget->rowCount(),0,itemDistance);
    this->m_tableWidget->setItem(this->m_tableWidget->rowCount(),1,itemEncoder);
}
void ZDataMdyDialog::ZSlotDel()
{
    qint32 i=this->m_tableWidget->currentRow();
    this->m_tableWidget->removeRow(i);
}
void ZDataMdyDialog::ZSlotCleanAll()
{
    this->m_tableWidget->clear();
    this->m_tableWidget->setRowCount(0);
}
void ZDataMdyDialog::ZSlotOkay()
{
    this->accept();
}
