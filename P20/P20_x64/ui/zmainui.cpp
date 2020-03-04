#include "zmainui.h"

ZMainUI::ZMainUI(QWidget *parent)
    : QWidget(parent)
{
    this->m_rssiUI=new ZRssiUI;
    this->m_tbAutoFocus=new QToolButton;
    this->m_tbAutoFocus->setText(tr("自动对焦"));

    this->m_tbDistance=new QToolButton;
    this->m_tbDistance->setText(tr("距离:-米"));

    this->m_tbPlus=new QToolButton;
    this->m_tbPlus->setText(tr("+"));

    this->m_tbMinus=new QToolButton;
    this->m_tbMinus->setText(tr("-"));

    this->m_hLayPlusMinus=new QHBoxLayout;
    this->m_hLayPlusMinus->addWidget(this->m_tbPlus);
    this->m_hLayPlusMinus->addWidget(this->m_tbMinus);

    this->m_tbRecord=new QToolButton;
    this->m_tbRecord->setText(tr("录像"));

    this->m_tbPlayback=new QToolButton;
    this->m_tbPlayback->setText(tr("回放"));

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
