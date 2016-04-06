#include <QApplication>
#include "SingleGame.h"
int main(int argc,char*argv[])
{
    QApplication app(argc,argv);

    SingleGame b;
    b.show();

    return app.exec();
}
