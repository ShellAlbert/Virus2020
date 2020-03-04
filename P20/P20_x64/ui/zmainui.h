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
class ZMainUI : public QWidget
{
    Q_OBJECT

public:
    ZMainUI(QWidget *parent = 0);
    ~ZMainUI();

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
};

#endif // ZMAINUI_H
