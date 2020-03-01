#include "zmainui.h"
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QPointF>
#include <zxydialog.h>
#include <zdatamdydialog.h>
#include <QTcpSocket>
#include <QHostAddress>
#include <QtNetwork/QNetworkInterface>
#include <QToolTip>

//功能 : 最小二乘法直线拟合 y = k·x + b， 计算系数k 和 b
//参数 : x -- 辐照度的数组
//       y --  功率的数组
//       num 是数组包含的元素个数，x[]和y[]的元素个数必须相等
//       k,b 都是返回值
//输入的样本数据越多，结果越精确
void leastSquareLinearFit(float  *x, float *y, unsigned int DataNum,  float *k,  float *b)
{
    unsigned int i;
    float sum_x2 = 0;
    float sum_y = 0;
    float sum_x = 0;
    float sum_xy = 0;
    for (i = 0; i < DataNum; ++i)
    {
        sum_x2 += x[i] * x[i];
        sum_y += y[i];
        sum_x += x[i];
        sum_xy += x[i] * y[i];
    }
    *k = (DataNum * sum_xy - sum_x * sum_y) / (DataNum * sum_x2 - sum_x * sum_x);
    *b = (sum_x2 * sum_y - sum_x * sum_xy) / (DataNum * sum_x2 - sum_x * sum_x);
    return;
}
MainUI::MainUI(QWidget *parent)
    : QWidget(parent)
{
    this->setMinimumSize(600,400);
    this->setObjectName("MainUI");
    if(this->ZDoInit()<0)
    {
        qApp->exit(-1);
    }
}

MainUI::~MainUI()
{
    delete this->m_chart;
    delete this->m_chartView;

    delete this->m_llPointNum;
    delete this->m_btnData;
    delete this->m_btnCalc;
    delete this->m_btnDevice;
    delete this->m_btnAbout;
    delete this->m_hLayBtns;

    delete this->m_vLayoutMain;

    delete this->m_scatterSeries;
    delete this->m_lineSeries1;
    delete this->m_lineSeries2;

    delete this->m_axisX;
    delete this->m_axisY;
}
void MainUI::paintEvent(QPaintEvent*)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
qint32 MainUI::ZDoInit()
{
    this->m_chart=new QChart;
    this->m_chart->legend()->hide();
    this->m_chart->setTheme(QChart::ChartThemeBlueCerulean);
    this->m_chart->layout()->setContentsMargins(0, 0, 0, 0);
    this->m_chart->setMargins(QMargins(0, 0, 0, 0));
    this->m_chart->setBackgroundRoundness(0);

    this->m_chartView=new QChartView(this->m_chart);
    this->m_chartView->setRenderHint(QPainter::Antialiasing);

    this->m_scatterSeries=new QScatterSeries;
    this->m_scatterSeries->setPen(QPen(Qt::green,2,Qt::SolidLine));
    this->m_scatterSeries->setPointLabelsVisible(true);
    QObject::connect(this->m_scatterSeries,SIGNAL(clicked(QPointF)),this,SLOT(ZSlotScatterSeriesClicked(QPointF)));

    this->m_lineSeries1=new QLineSeries;
    this->m_lineSeries1->setPen(QPen(Qt::yellow,2,Qt::SolidLine));

    this->m_lineSeries2=new QLineSeries;
    this->m_lineSeries2->setPen(QPen(Qt::red,2,Qt::SolidLine));

    this->m_chart->addSeries(this->m_scatterSeries);
    this->m_chart->addSeries(this->m_lineSeries1);
    this->m_chart->addSeries(this->m_lineSeries2);

    this->m_axisX=new QValueAxis;
    this->m_axisX->setRange(0,10);
    this->m_axisX->setTitleText(tr("Distance/(m)"));

    this->m_axisY=new QValueAxis;
    this->m_axisY->setRange(0,100);
    this->m_axisY->setTitleText(tr("Encoder/(num)"));

    this->m_chart->addAxis(this->m_axisX,Qt::AlignBottom);
    this->m_chart->addAxis(this->m_axisY,Qt::AlignLeft);


    this->m_scatterSeries->attachAxis(this->m_axisX);
    this->m_scatterSeries->attachAxis(this->m_axisY);

    this->m_lineSeries1->attachAxis(this->m_axisX);
    this->m_lineSeries1->attachAxis(this->m_axisY);

    this->m_lineSeries2->attachAxis(this->m_axisX);
    this->m_lineSeries2->attachAxis(this->m_axisY);

    this->m_llPointNum=new QLabel;
    this->m_llPointNum->setText(tr("Points:0"));
    this->m_llPointNum->setObjectName("QLabel_PointNum");

    this->m_btnData=new QToolButton;
    this->m_btnData->setText(tr("Data"));
    QObject::connect(this->m_btnData,SIGNAL(clicked()),this,SLOT(ZSlotData()));

    this->m_btnCalc=new QToolButton;
    this->m_btnCalc->setText(tr("Calculate"));
    QObject::connect(this->m_btnCalc,SIGNAL(clicked()),this,SLOT(ZSlotCalculate()));

    this->m_btnDevice=new QToolButton;
    this->m_btnDevice->setText(tr("Device"));
    QObject::connect(this->m_btnDevice,SIGNAL(clicked()),this,SLOT(ZSlotDevice()));

    this->m_btnAbout=new QToolButton;
    this->m_btnAbout->setText(tr("Help"));
    QObject::connect(this->m_btnAbout,SIGNAL(clicked()),this,SLOT(ZSlotAbout()));

    this->m_hLayBtns=new QHBoxLayout;
    this->m_hLayBtns->addWidget(this->m_llPointNum);
    this->m_hLayBtns->addStretch();
    this->m_hLayBtns->addWidget(this->m_btnData);
    this->m_hLayBtns->addWidget(this->m_btnCalc);
    this->m_hLayBtns->addWidget(this->m_btnDevice);
    this->m_hLayBtns->addWidget(this->m_btnAbout);
    this->m_hLayBtns->addStretch();
    this->m_hLayBtns->setContentsMargins(2,0,2,0);
    this->m_hLayBtns->setSpacing(10);

    this->m_vLayoutMain=new QVBoxLayout;
    this->m_vLayoutMain->addLayout(this->m_hLayBtns);
    this->m_vLayoutMain->addWidget(this->m_chartView);
    this->m_vLayoutMain->setContentsMargins(0,0,0,0);
    this->m_vLayoutMain->setSpacing(0);

    this->setLayout(this->m_vLayoutMain);

    return 0;
}
void MainUI::ZSlotData()
{
    ZDataDialog  diaData(this);
    if(diaData.exec()==QDialog::Accepted)
    {
        qint32 bindNum=diaData.ZGetClickedBindNum();
        switch(bindNum)
        {
        case 1:
        {
            QFileDialog diaFile;
            QString fileName=diaFile.getOpenFileName(0,tr("Load data file"),".","Data (*.txt)");
            if(fileName.isEmpty())
            {
                return;
            }
            QFile fileTxt(fileName);
            if(fileTxt.open(QIODevice::ReadOnly|QIODevice::Text))
            {
                this->m_listData.clear();
                qint32 x_axis_max=0;
                qint32 y_axis_max=0;
                while(!fileTxt.atEnd())
                {
                    QByteArray baLine=fileTxt.readLine();
                    //qDebug()<<baLine;
                    QString xyString(baLine);
                    QStringList xyStrList=xyString.split(",");
                    if(xyStrList.size()==2)
                    {
                        qint32 x=xyStrList.at(0).toInt();
                        qint32 y=xyStrList.at(1).toInt();
                        this->m_listData.append(QPointF(x,y));

                        //find out the max x&y to reset the axis range.
                        if(x>x_axis_max)
                        {
                            x_axis_max=x;
                        }
                        if(y>y_axis_max)
                        {
                            y_axis_max=y;
                        }
                    }
                }
                fileTxt.close();
                //here add x/3 extra space plus to visible all data.
                this->m_axisX->setRange(0,x_axis_max+x_axis_max/3);
                this->m_axisY->setRange(0,y_axis_max+y_axis_max/3);
                this->m_scatterSeries->replace(this->m_listData);
                //update point number.
                this->m_llPointNum->setText(tr("Points:%1").arg(this->m_listData.size()));
                //QMessageBox::information(this,tr("Tips"),"Load Okay");
            }

        }
            break;
        case 2:
        {
            ZDataMdyDialog mdyDia(this->m_listData,this);
            if(mdyDia.exec()==QDialog::Accepted)
            {

            }
        }
            break;
        case 3:
        {
            QFileDialog diaFile;
            QString fileName=diaFile.getSaveFileName(0,tr("Save data to file"),".","Data (*.txt)");
            if(fileName.isEmpty())
            {
                return;
            }
            QFile fileTxt(fileName);
            if(fileTxt.open(QIODevice::WriteOnly|QIODevice::Text))
            {
                for(qint32 i=0;i<this->m_listData.size();i++)
                {
                    char buffer[256];
                    QPointF pt=this->m_listData.at(i);
                    sprintf(buffer,"%d,%d\n",pt.x(),pt.y());
                    fileTxt.write(buffer,strlen(buffer));
                }
                fileTxt.close();
                //QMessageBox::information(this,tr("Tips"),"Save Okay");
            }
        }
            break;
        default:
            break;
        }
    }


}
void MainUI::ZSlotCalculate()
{
    if(this->m_listData.size()<=0)
    {
        QToolTip::showText(this->geometry().center(),tr("No data points input!"));
        return;
    }
    //算法1:最小二乘法
    int sampleNum=this->m_listData.size();
    float *x=new float[sampleNum];
    float *y=new float[sampleNum];
    float k,b;
    for(qint32 i=0;i<this->m_listData.size();i++)
    {
        x[i]=this->m_listData.at(i).x();
        y[i]=this->m_listData.at(i).y();
    }
    leastSquareLinearFit(x,y,sizeof(x)/sizeof(x[0]),&k,&b);
    delete [] x;
    delete [] y;
    this->m_listData1.clear();
    qint32 xStart=this->m_listData.at(0).x();
    qint32 xEnd=this->m_listData.at(this->m_listData.size()-1).x();
    for(qint32 i=xStart;i<=xEnd;i++)
    {
        qint32 nDistance=i;
        qint32 nEncoder=i*k+b;
        this->m_listData1.append(QPointF(nDistance,nEncoder));
    }
    this->m_lineSeries1->replace(this->m_listData1);

    //算法2：分段拟合
    this->m_listData2.clear();
    for(qint32 i=0;i<this->m_listData.size()-1;i++)
    {
        QPointF pt=this->m_listData.at(i);
        QPointF ptNext=this->m_listData.at(i+1);
        qint32 diffDistance=ptNext.x()-pt.x();
        qint32 diffEncoder=ptNext.y()-pt.y();
        //qDebug()<<pt<<ptNext<<diffDistance<<diffEncoder;
        qint32 nStep=diffEncoder/diffDistance;
        //qDebug()<<pt<<ptNext;
        //qDebug()<<diffDistance<<diffEncoder<<nStep;

        //loop to generate other points.
        for(qint32 j=0;j<ptNext.x()-pt.x();j++)
        {
            //qDebug()<<"adding:"<<QPointF(pt.x()+j,pt.y()+j*nStep);
            this->m_listData2.append(QPointF(pt.x()+j,pt.y()+j*nStep));
        }
    }
    //donot miss the last one point.
    this->m_listData2.append(this->m_listData.at(this->m_listData.size()-1));
    this->m_lineSeries2->replace(this->m_listData2);
    //    QMessageBox::information(this,tr("Tips"),"Calculate");
    //    qDebug()<<this->m_listData2;
}
void MainUI::ZSlotDevice()
{
    QTcpSocket *tcpClient=new QTcpSocket;
    tcpClient->connectToHost(QHostAddress("192.168.10.102"), 6665);
    if(tcpClient->waitForConnected(3000))
    {
        tcpClient->write("ZTCalibration",13);
        tcpClient->waitForBytesWritten(3000);
    }else{
        QToolTip::showText(this->geometry().center(),tr("Failed to connect device!"));
    }
    tcpClient->close();
    delete tcpClient;
}
void MainUI::ZSlotAbout()
{
    QString tips;
    QList<QHostAddress> list =QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {
        if(address.isLoopback())
        {
            continue;
        }
       if(address.protocol()==QAbstractSocket::IPv4Protocol)
       {
           tips.append(QString("IP:")+address.toString()+QString("\n"));
       }
    }
    QToolTip::showText(this->geometry().center(),tips);
}
void MainUI::ZSlotScatterSeriesClicked(const QPointF &pt)
{
    ZXYDialog xy(pt);
    if(xy.exec()==QDialog::Accepted)
    {
        QPointF pt=xy.ZGetPoint();
        if(this->m_listData.contains(pt))
        {
            this->m_listData.removeOne(pt);
            this->m_scatterSeries->replace(this->m_listData);
            //update point number.
            this->m_llPointNum->setText(tr("Points:%1").arg(this->m_listData.size()));
        }
    }
}
