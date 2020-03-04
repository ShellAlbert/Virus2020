#include "zmainui.h"
#include <QApplication>
#include <QThread>
#include <QDebug>
#include "zgblparam.h"
ZMainUI::ZMainUI(QWidget *parent):QWidget(parent)
{
    this->setWindowTitle(tr("BypassAPP"));

    this->m_rssiUI=new ZRssiUI;
    this->m_tbAutoFocus=new QToolButton;
    this->m_tbAutoFocus->setText(tr("自动对焦"));
    QObject::connect(this->m_tbAutoFocus,SIGNAL(clicked()),this,SLOT(ZSlotAutoFocus()));

    this->m_tbDistance=new QToolButton;
    this->m_tbDistance->setText(tr("距离:-米"));
    QObject::connect(this->m_tbDistance,SIGNAL(clicked()),this,SLOT(ZSlotDistance()));

    this->m_tbPlus=new QToolButton;
    this->m_tbPlus->setText(tr("+"));
    QObject::connect(this->m_tbPlus,SIGNAL(clicked()),this,SLOT(ZSlotPlus()));

    this->m_tbMinus=new QToolButton;
    this->m_tbMinus->setText(tr("-"));
    QObject::connect(this->m_tbMinus,SIGNAL(clicked()),this,SLOT(ZSlotMinus()));

    this->m_hLayPlusMinus=new QHBoxLayout;
    this->m_hLayPlusMinus->addWidget(this->m_tbPlus);
    this->m_hLayPlusMinus->addWidget(this->m_tbMinus);

    this->m_tbRecord=new QToolButton;
    this->m_tbRecord->setText(tr("录像"));
    QObject::connect(this->m_tbRecord,SIGNAL(clicked()),this,SLOT(ZSlotRecord()));

    this->m_tbPlayback=new QToolButton;
    this->m_tbPlayback->setText(tr("回放"));
    QObject::connect(this->m_tbPlayback,SIGNAL(clicked()),this,SLOT(ZSlotPlayback()));

    this->m_vLayLeft=new QVBoxLayout;
    this->m_vLayLeft->addWidget(this->m_rssiUI);
    this->m_vLayLeft->addWidget(this->m_tbAutoFocus);
    this->m_vLayLeft->addWidget(this->m_tbDistance);
    this->m_vLayLeft->addLayout(this->m_hLayPlusMinus);
    this->m_vLayLeft->addWidget(this->m_tbRecord);
    this->m_vLayLeft->addWidget(this->m_tbPlayback);

    this->m_videoUI=new ZVideoUI;
    this->m_batteryUI=new ZBatteryUI(this->m_videoUI);
    this->m_hLayMain=new QHBoxLayout;
    this->m_hLayMain->setContentsMargins(0,0,0,0);
    this->m_hLayMain->addLayout(this->m_vLayLeft);
    this->m_hLayMain->addWidget(this->m_videoUI);

    this->setLayout(this->m_hLayMain);
}

ZMainUI::~ZMainUI()
{
    delete this->m_rssiUI;
    delete this->m_tbAutoFocus;
    delete this->m_tbDistance;
    delete this->m_tbPlus;
    delete this->m_tbMinus;
    delete this->m_hLayPlusMinus;
    delete this->m_tbRecord;
    delete this->m_tbPlayback;
    delete this->m_vLayLeft;

    delete this->m_batteryUI;
    delete this->m_videoUI;

    delete this->m_hLayMain;
}
void ZMainUI::ZBindQueue(QMutex *mux,///<
                         QWaitCondition *condNotEmpty,QWaitCondition *condNotFull,///<
                         QQueue<ZElement*> *queueUsed,QQueue<ZElement*> *queueFree)
{
    this->m_mux=mux;
    this->m_condNotEmpty=condNotEmpty;
    this->m_condNotFull=condNotFull;
    this->m_queueUsed=queueUsed;
    this->m_queueFree=queueFree;
}
void ZMainUI::ZPutEle2FIFO(QByteArray baData)
{
    //get a free buffer from fifo.
    this->m_mux->lock();
    while(this->m_queueFree->isEmpty())
    {
        if(!this->m_condNotEmpty->wait(this->m_mux,1000))
        {
            this->m_mux->unlock();
            return;
        }
    }

    ZElement *ele=this->m_queueFree->dequeue();
    this->m_mux->unlock();

    //copy data into fifo element.
    memcpy(ele->baTxData->data(),baData.data(),baData.size());
    ele->nTxLen=baData.size();

    this->m_mux->lock();
    this->m_queueUsed->enqueue(ele);
    this->m_condNotFull->wakeAll();
    this->m_mux->unlock();
}
void ZMainUI::ZSlotAutoFocus()
{

}
void ZMainUI::ZSlotDistance()
{

}
void ZMainUI::ZSlotPlus()
{

}
void ZMainUI::ZSlotMinus()
{

}
void ZMainUI::ZSlotRecord()
{

}
void ZMainUI::ZSlotPlayback()
{

}
