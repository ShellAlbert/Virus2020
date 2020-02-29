#include "maindialog.h"
#include <QApplication>
#include <QFile>
#include <QtNetwork/QNetworkInterface>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //generate example data file.
    //create it if it isnot exist.
    QFile fileExample("example.txt");
    if(!fileExample.exists())
    {
        if(fileExample.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            char *exampleData="31,10439\n76,12681\n152,16656\n240,30951\n300,32032\n400,64203\n";
            fileExample.write(exampleData,strlen(exampleData));
            fileExample.close();
        }
    }



    //load qss skin.
    QFile fileQss(":/skinfile/skin/default.qss");
    if(fileQss.open(QIODevice::ReadOnly))
    {
        QByteArray baQss=fileQss.readAll();
        app.setStyleSheet(baQss);
        fileQss.close();
    }

    MainDialog w;
    w.showMaximized();

    QList<QHostAddress> list =QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {
       if(address.protocol() ==QAbstractSocket::IPv4Protocol)
       {
           qDebug()<<address.toString();
       }
    }
    return app.exec();
}
