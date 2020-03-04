#ifndef ZMAINUI_H
#define ZMAINUI_H

#include <QWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "ui/zrssiui.h"
#include "ui/zvideoui.h"
#include "ui/zbatteryui.h"
#include "zgblparam.h"
#include <QMutex>
#include <QWaitCondition>
#include <QQueue>
class ZMainUI : public QWidget
{
    Q_OBJECT

public:
    ZMainUI(QWidget *parent = 0);
    ~ZMainUI();

    void ZBindQueue(QMutex *mux,///<
                    QWaitCondition *condNotEmpty,QWaitCondition *condNotFull,///<
                    QQueue<ZElement*> *queueUsed,QQueue<ZElement*> *queueFree);

private:
    void ZPutEle2FIFO(QByteArray baData);
private slots:
    void ZSlotAutoFocus();
    void ZSlotDistance();
    void ZSlotPlus();
    void ZSlotMinus();
    void ZSlotRecord();
    void ZSlotPlayback();

private:
    ZRssiUI *m_rssiUI;
    QToolButton *m_tbAutoFocus;
    QToolButton *m_tbDistance;
    QToolButton *m_tbPlus;
    QToolButton *m_tbMinus;
    QHBoxLayout *m_hLayPlusMinus;
    QToolButton *m_tbRecord;
    QToolButton *m_tbPlayback;
    QVBoxLayout *m_vLayLeft;

    ZVideoUI *m_videoUI;
    ZBatteryUI *m_batteryUI;
    QHBoxLayout *m_hLayMain;

private:
    //MainUI thread to Communicate Thread queue.
    //TxFIFO.
    QMutex *m_mux;
    QWaitCondition *m_condNotEmpty;
    QWaitCondition *m_condNotFull;
    QQueue<ZElement*> *m_queueUsed;
    QQueue<ZElement*> *m_queueFree;
};

#endif // ZMAINUI_H
