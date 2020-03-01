#include "zmainui.h"
#include <QApplication>
#include <QFile>
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

    MainUI ui;
    ui.showMaximized();

    return app.exec();
}
