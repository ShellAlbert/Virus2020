#ifndef MAINUI_H
#define MAINUI_H

#include <QDialog>
#include <QTextEdit>
#include <QToolButton>
#include <QVBoxLayout>
#include <QtCharts>
#include <QScatterSeries>
#include <QLineSeries>
#include "zbuttondialog.h"
using namespace QtCharts;
class MainUI : public QWidget
{
    Q_OBJECT

public:
    MainUI(QWidget *parent = 0);
    ~MainUI();

    qint32 ZDoInit();
private slots:
    void ZSlotData();
    void ZSlotCalculate();
    void ZSlotDevice();
    void ZSlotAbout();
private slots:
    void ZSlotScatterSeriesClicked(const QPointF &pt);
protected:
    void paintEvent(QPaintEvent *e);
private:
    QChart *m_chart;
    QChartView *m_chartView;

    QLabel *m_llPointNum;
    QToolButton *m_btnData;
    QToolButton *m_btnCalc;
    QToolButton *m_btnDevice;
    QToolButton *m_btnAbout;
    QHBoxLayout *m_hLayBtns;

    QVBoxLayout *m_vLayoutMain;
private:
    //单次测距样本数据点，散点图
    QList<QPointF> m_listData;
    QScatterSeries *m_scatterSeries;

    //最小二乘法拟合后的数据点
    QList<QPointF> m_listData1;
    QLineSeries *m_lineSeries1;

    //分段拟合后的数据点,分段算法
    QList<QPointF> m_listData2;
    QLineSeries *m_lineSeries2;

    QValueAxis *m_axisX;
    QValueAxis *m_axisY;
private:

    ZButtonDialog *m_diaCalc;
    ZButtonDialog *m_diaDevice;
};

#endif // MAINUI_H
