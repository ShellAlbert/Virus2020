#include "ztimeoutscanthread.h"

ZTimeoutScanThread::ZTimeoutScanThread()
{

}
void ZTimeoutScanThread::ZBindQueue(QMutex *mux,///<
                QWaitCondition *condNotEmpty,QWaitCondition *condNotFull,///<
                QQueue<ZElement*> *queueUsed,QQueue<ZElement*> *queueFree)
{
    this->m_mux=mux;
    this->m_condNotEmpty=condNotEmpty;
    this->m_condNotFull=condNotFull;
    this->m_queueUsed=queueUsed;
    this->m_queueFree=queueFree;
}
void ZTimeoutScanThread::run()
{

}
