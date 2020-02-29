#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QToolButton>
#include <QVBoxLayout>
#include <QtCharts>
#include <QScatterSeries>
#include <QLineSeries>
#include "zbuttondialog.h"
using namespace QtCharts;
class MainDialog : public QDialog
{
    Q_OBJECT

public:
    MainDialog(QWidget *parent = 0);
    ~MainDialog();

    qint32 ZDoInit();
private slots:
    void ZSlotData();
    void ZSlotCalculate();
    void ZSlotDevice();
private slots:
    void ZSlotScatterSeriesClicked(const QPointF &pt);
private:
    QChart *m_chart;
    QChartView *m_chartView;

    QToolButton *m_btnData;
    QToolButton *m_btnCalc;
    QToolButton *m_btnDevice;
    QVBoxLayout *m_vlayBtns;

    QHBoxLayout *m_hLayoutMain;
private:
    //单次测距样本数据点
    QList<QPointF> m_listData;
    QScatterSeries *m_scatterSeries;

    //曲线拟合后的数据点
    QList<QPointF> m_listData2;
    QLineSeries *m_lineSeries2;

    QValueAxis *m_axisX;
    QValueAxis *m_axisY;
    QValueAxis *m_axisY2;


private:

    ZButtonDialog *m_diaCalc;
    ZButtonDialog *m_diaDevice;
};

#endif // MAINDIALOG_H
