#ifndef ZGBLPARAM_H
#define ZGBLPARAM_H

#include <QWidget>
#include <QByteArray>
class ZMainUI;
class ZCommunicateThread;
class ZTimeoutScanThread;
class ZGblParam
{
public:
    ZGblParam();

    ZMainUI *mainUI;
    ZCommunicateThread *commThread;
    ZTimeoutScanThread *timeoutThread;
public:
    bool bExitFlag;
};
extern ZGblParam g_GblPara;

//element in FIFO.
#define TX_RX_MAX_SIZE   256
class ZElement
{
public:
    ZElement();
    ~ZElement();
public:
    QWidget *widget;
    qint32 nTimeoutMSec;
    QByteArray *baTxData;
    qint32 nTxLen;
    QByteArray *baRxData;
    qint32 nRxLen;
};
#endif // ZGBLPARAM_H
