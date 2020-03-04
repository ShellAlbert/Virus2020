#include "zcommunicatethread.h"
#include <QDebug>
#include "zgblparam.h"
ZCommunicateThread::ZCommunicateThread()
{
}
ZCommunicateThread::~ZCommunicateThread()
{
}
void ZCommunicateThread::ZBindQueue1(QMutex *mux,///<
                QWaitCondition *condNotEmpty,QWaitCondition *condNotFull,///<
                QQueue<ZElement*> *queueUsed,QQueue<ZElement*> *queueFree)
{
    this->m_mux1=mux;
    this->m_condNotEmpty1=condNotEmpty;
    this->m_condNotFull1=condNotFull;
    this->m_queueUsed1=queueUsed;
    this->m_queueFree1=queueFree;
}
void ZCommunicateThread::ZBindQueue2(QMutex *mux,///<
                QWaitCondition *condNotEmpty,QWaitCondition *condNotFull,///<
                QQueue<ZElement*> *queueUsed,QQueue<ZElement*> *queueFree)
{
    this->m_mux2=mux;
    this->m_condNotEmpty2=condNotEmpty;
    this->m_condNotFull2=condNotFull;
    this->m_queueUsed2=queueUsed;
    this->m_queueFree2=queueFree;
}
void ZCommunicateThread::run()
{

}
