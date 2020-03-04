#ifndef ZTIMEOUTSCANTHREAD_H
#define ZTIMEOUTSCANTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QQueue>
#include "zgblparam.h"
class ZTimeoutScanThread : public QThread
{
    Q_OBJECT
public:
    ZTimeoutScanThread();
    void ZBindQueue(QMutex *mux,///<
                    QWaitCondition *condNotEmpty,QWaitCondition *condNotFull,///<
                    QQueue<ZElement*> *queueUsed,QQueue<ZElement*> *queueFree);
protected:
    void run();
private:
    //Communicate Thread to Timeout Thread.
    //WaitAckFIFO.
    QMutex *m_mux;
    QWaitCondition *m_condNotEmpty;
    QWaitCondition *m_condNotFull;
    QQueue<ZElement*> *m_queueUsed;
    QQueue<ZElement*> *m_queueFree;
};

#endif // ZTIMEOUTSCANTHREAD_H
