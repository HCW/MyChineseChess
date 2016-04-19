#include <QApplication>
#include "SingleGame.h"
#include "CalScoreWidget.h"
int main(int argc,char*argv[])
{
    QApplication app(argc,argv);

    SingleGame b;
    b.show();

//    CalScoreWidget w;
//    w.show();
    return app.exec();
}
