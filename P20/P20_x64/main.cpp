
#include <QApplication>
#include "zp20.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ZP20 p20;
    p20.ZStart();

    return app.exec();
}
