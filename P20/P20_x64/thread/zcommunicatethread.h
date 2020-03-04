#ifndef ZCOMMUNICATETHREAD_H
#define ZCOMMUNICATETHREAD_H

#include <QThread>
#include "zgblparam.h"
#include <QMutex>
#include <QWaitCondition>
#include <QQueue>
class ZCommunicateThread : public QThread
{
    Q_OBJECT
public:
    ZCommunicateThread();
    ~ZCommunicateThread();

    void ZBindQueue1(QMutex *mux,///<
                    QWaitCondition *condNotEmpty,QWaitCondition *condNotFull,///<
                    QQueue<ZElement*> *queueUsed,QQueue<ZElement*> *queueFree);
    void ZBindQueue2(QMutex *mux,///<
                    QWaitCondition *condNotEmpty,QWaitCondition *condNotFull,///<
                    QQueue<ZElement*> *queueUsed,QQueue<ZElement*> *queueFree);
protected:
    void run();
private:
    //MainUI thread to Communicate Thread queue.
    //TxFIFO.
    QMutex *m_mux1;
    QWaitCondition *m_condNotEmpty1;
    QWaitCondition *m_condNotFull1;
    QQueue<ZElement*> *m_queueUsed1;
    QQueue<ZElement*> *m_queueFree1;

    //Communicate Thread to Timeout Thread.
    //WaitAckFIFO.
    QMutex *m_mux2;
    QWaitCondition *m_condNotEmpty2;
    QWaitCondition *m_condNotFull2;
    QQueue<ZElement*> *m_queueUsed2;
    QQueue<ZElement*> *m_queueFree2;
};

#endif // ZCOMMUNICATETHREAD_H
