#include <QApplication>
#include "SingleGame.h"
#include "CalScoreWidget.h"
#include "NetGame.h"
#include <QMessageBox>
#include "ChessDlg.h"
int main(int argc,char*argv[])
{
    QApplication app(argc,argv);

//    SingleGame b;
//    b.show();

//    QMessageBox::StandardButton ret;
//    ret=QMessageBox::question(NULL,"提示","是否作为服务器启动？");

//    bool bServer=false;//是否是服务器启动
//    if(ret==QMessageBox::Yes)
//    {
//        bServer=true;
//    }
//    NetGame b(bServer);
//    b.show();

    ChessDlg dlg;
    dlg.show();

//    CalScoreWidget w;
//    w.show();
    return app.exec();
}
