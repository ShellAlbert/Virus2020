#include "maindialog.h"
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QPointF>
#include <zxydialog.h>
#include <QTcpSocket>
#include <QHostAddress>
MainDialog::MainDialog(QWidget *parent)
    : QDialog(parent)
{
    this->setMinimumSize(400,200);
    if(this->ZDoInit()<0)
    {
        qApp->exit(-1);
    }
}

MainDialog::~MainDialog()
{
    delete this->m_chart;
    delete this->m_chartView;

    delete this->m_btnData;
    delete this->m_btnCalc;
    delete this->m_btnDevice;
    delete this->m_vlayBtns;

    delete this->m_hLayoutMain;

    delete this->m_scatterSeries;
    delete this->m_lineSeries2;
    delete this->m_axisX;
    delete this->m_axisY;
    delete this->m_axisY2;
}
qint32 MainDialog::ZDoInit()
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
    this->m_scatterSeries->setPen(QPen(Qt::yellow,2,Qt::SolidLine));
    this->m_scatterSeries->setPointLabelsVisible(true);
    QObject::connect(this->m_scatterSeries,SIGNAL(clicked(QPointF)),this,SLOT(ZSlotScatterSeriesClicked(QPointF)));

    this->m_lineSeries2=new QLineSeries;
    this->m_lineSeries2->setPen(QPen(Qt::red,2,Qt::SolidLine));

    this->m_chart->addSeries(this->m_scatterSeries);
    this->m_chart->addSeries(this->m_lineSeries2);

    this->m_axisX=new QValueAxis;
    this->m_axisX->setRange(0,10);
    this->m_axisX->setTitleText(tr("距离/(米)"));

    this->m_axisY=new QValueAxis;
    this->m_axisY->setRange(0,100);
    this->m_axisY->setTitleText(tr("实测编码器数值/(个)"));

    this->m_axisY2=new QValueAxis;
    this->m_axisY2->setRange(0,100);
    this->m_axisY2->setTitleText(tr("拟合编码器数值/(个)"));

    this->m_chart->addAxis(this->m_axisX,Qt::AlignBottom);
    this->m_chart->addAxis(this->m_axisY,Qt::AlignLeft);
    this->m_chart->addAxis(this->m_axisY2,Qt::AlignRight);


    this->m_scatterSeries->attachAxis(this->m_axisX);
    this->m_scatterSeries->attachAxis(this->m_axisY);

    this->m_lineSeries2->attachAxis(this->m_axisX);
    this->m_lineSeries2->attachAxis(this->m_axisY2);

    this->m_btnData=new QToolButton;
    this->m_btnData->setText(tr("数据"));
    QObject::connect(this->m_btnData,SIGNAL(clicked()),this,SLOT(ZSlotData()));

    this->m_btnCalc=new QToolButton;
    this->m_btnCalc->setText(tr("计算"));
    QObject::connect(this->m_btnCalc,SIGNAL(clicked()),this,SLOT(ZSlotCalculate()));

    this->m_btnDevice=new QToolButton;
    this->m_btnDevice->setText(tr("设备"));
    QObject::connect(this->m_btnDevice,SIGNAL(clicked()),this,SLOT(ZSlotDevice()));

    this->m_vlayBtns=new QVBoxLayout;
    this->m_vlayBtns->addWidget(this->m_btnData);
    this->m_vlayBtns->addWidget(this->m_btnCalc);
    this->m_vlayBtns->addWidget(this->m_btnDevice);
    this->m_vlayBtns->setContentsMargins(10,20,10,20);

    this->m_hLayoutMain=new QHBoxLayout;
    this->m_hLayoutMain->addWidget(this->m_chartView);
    this->m_hLayoutMain->addLayout(this->m_vlayBtns);
    this->m_hLayoutMain->setContentsMargins(0,0,0,0);
    this->m_hLayoutMain->setSpacing(0);

    this->setLayout(this->m_hLayoutMain);

    return 0;
}
void MainDialog::ZSlotData()
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
                this->m_axisY2->setRange(0,y_axis_max+y_axis_max/3);
                this->m_scatterSeries->replace(this->m_listData);
                //QMessageBox::information(this,tr("Tips"),"Load Okay");
            }

        }
            break;
        case 2:
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
void MainDialog::ZSlotCalculate()
{
    if(this->m_listData.size()<=0)
    {
        return;
    }
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
void MainDialog::ZSlotDevice()
{
    QTcpSocket *tcpClient=new QTcpSocket;
    tcpClient->connectToHost(QHostAddress("192.168.10.102"), 6665);
    if(tcpClient->waitForConnected(3000))
    {
        tcpClient->write("hello",5);
        tcpClient->waitForBytesWritten(3000);
        qDebug()<<"connect okay.";
    }else{
        qDebug()<<"connect failed.";
    }
    tcpClient->close();
    delete tcpClient;
}
void MainDialog::ZSlotScatterSeriesClicked(const QPointF &pt)
{
    ZXYDialog xy(pt);
    xy.exec();
}
