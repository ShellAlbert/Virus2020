#ifndef ZP20_H
#define ZP20_H

#include "ui/zmainui.h"
#include "thread/zcommunicatethread.h"
#include "thread/ztimeoutscanthread.h"
#include "zgblparam.h"
#include <QMutex>
#include <QQueue>
#include <QWaitCondition>
#define FIFO_DEPTH 10
class ZP20:public QObject
{
    Q_OBJECT
public:
    ZP20();
    ~ZP20();

    bool ZStart();
private:
    ZMainUI *m_mainUI;
    ZCommunicateThread *m_commThread;
    ZTimeoutScanThread *m_timeoutThread;

    //MainUI thread to Communicate Thread queue.
    //TxFIFO.
    QMutex m_muxUi2Co;
    QWaitCondition m_condUi2CoNotEmpty;
    QWaitCondition m_condUi2CoNotFull;
    QQueue<ZElement*> m_queueUi2CoUsed;
    QQueue<ZElement*> m_queueUi2CoFree;

    //Communicate Thread to Timeout Thread.
    //WaitAckFIFO.
    QMutex m_muxCo2Ti;
    QWaitCondition m_condCo2TiNotEmpty;
    QWaitCondition m_condCo2TiNotFull;
    QQueue<ZElement*> m_queueCo2TiCoUsed;
    QQueue<ZElement*> m_queueCo2TiCoFree;
};

#endif // ZP20_H
