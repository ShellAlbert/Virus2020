#include "zp20.h"
#include "zgblparam.h"
ZP20::ZP20()
{
//    g_GblPara.mainUI=this->m_mainUI;
//    g_GblPara.commThread=this->m_commThread;
//    g_GblPara.timeoutThread=this->m_timeoutThread;

}
ZP20::~ZP20()
{
    delete this->m_mainUI;
    delete this->m_commThread;
    delete this->m_timeoutThread;
}
bool ZP20::ZStart()
{
    //TxFIFO.
    for(qint32 i=0;i<5;i++)
    {
        ZElement *ele=new ZElement;
        this->m_queueUi2CoFree.enqueue(ele);
    }

    //WaitAckFIFO.
    for(qint32 i=0;i<5;i++)
    {
        ZElement *ele=new ZElement;
        this->m_queueCo2TiCoFree.enqueue(ele);
    }


    this->m_mainUI=new ZMainUI;
    this->m_mainUI->ZBindQueue(&m_muxUi2Co,&m_condUi2CoNotEmpty,&m_condUi2CoNotFull,&m_queueUi2CoUsed,&m_queueUi2CoFree);

    this->m_commThread=new ZCommunicateThread;
    this->m_commThread->ZBindQueue1(&m_muxUi2Co,&m_condUi2CoNotEmpty,&m_condUi2CoNotFull,&m_queueUi2CoUsed,&m_queueUi2CoFree);
    this->m_commThread->ZBindQueue2(&m_muxCo2Ti,&m_condCo2TiNotEmpty,&m_condCo2TiNotFull,&m_queueCo2TiCoUsed,&m_queueCo2TiCoFree);

    this->m_timeoutThread=new ZTimeoutScanThread;
    this->m_timeoutThread->ZBindQueue(&m_muxCo2Ti,&m_condCo2TiNotEmpty,&m_condCo2TiNotFull,&m_queueCo2TiCoUsed,&m_queueCo2TiCoFree);

    this->m_commThread->start();
    this->m_timeoutThread->start();
    this->m_mainUI->show();

    return true;
}
