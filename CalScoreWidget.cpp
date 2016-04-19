#include "CalScoreWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QStyleOption>
#include <QFile>
#include <QDebug>
#include <QHeaderView>
CalScoreWidget::CalScoreWidget(QWidget *parent) : QWidget(parent)
{

    InitInfo("朽","赢",1800,"电脑","输",10000);
    InitForm();

    connect(_AgainGameButton,SIGNAL(clicked()),this,SLOT(slotAgainGame()));

}
void CalScoreWidget::InitInfo(QString rp, QString rsta, int rsc, QString bp, QString bsta, int bsc)
{
    char str[10];
    _RedPlayerName=rp;//红方玩家名称
   _RedStatus=rsta;//赢输状态
   sprintf(str,"%d",rsc);
   _RedScore=str;
  // _RedScore=rsc;//积分

    _BlackPlayerName=bp;//黑方玩家名称
    _BlackStatus=bsta;//赢输状态
     memset(str,0,10);
    sprintf(str,"%d",bsc);
   _BlackScore=str;//积分
}
void CalScoreWidget::InitForm()
{
    this->setWindowTitle("对局结果");
    _AgainGameButton=new QPushButton("再来一局");
    _BackMainFormButton=new QPushButton("返回主界面");

    QHBoxLayout* lay=new QHBoxLayout();
    lay->addStretch(1);
    lay->addWidget(_AgainGameButton);
    lay->addWidget(_BackMainFormButton);

    _tableView=new QTableView(this);
    _model=new QStandardItemModel;
    _model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("玩家")));
    _model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("状态")));
    _model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("得分")));
    _tableView->setModel(_model);

   // _tableView->resizeColumnsToContents();
    //_tableView->resizeRowsToContents();
//  QHeaderView::setStretchLastSection(true);

    _tableView->horizontalHeader()->setStretchLastSection(true);//使最后一列自适应
   _tableView->verticalHeader()->setStretchLastSection(true);//使最后一行自适应


    _model->setItem(0,0,new QStandardItem(_BlackPlayerName));
    _model->setItem(0,1,new QStandardItem(_BlackStatus));
    _model->setItem(0,2,new QStandardItem(_BlackScore));

    _model->setItem(1,0,new QStandardItem(_RedPlayerName));
    _model->setItem(1,1,new QStandardItem(_RedStatus));
    _model->setItem(1,2,new QStandardItem(_RedScore));

    //QStandardItem()
    QVBoxLayout*vlay=new QVBoxLayout(this);
    vlay->addWidget(_tableView);
    vlay->addLayout(lay);

    this->resize(300,150);
   // _tableView->resize(200,100);
    //-------------------------------

    QString qss0="QWidget{ \
               background:#C5C1AA;\
               }";

    QString qss1="QPushButton {\
            background-color:#B0E0E6;\
            border-style: outset;\
            border-width: 2px;\
            border-radius: 10px;\
            border-color: #8B7355;\
            font: bold 14px;\
            min-width:6em;\
            color:white;\
            font-family:华文新魏;\
            padding: 7px;\
        }\
        QPushButton:hover{\
        background-color: rgb(0, 150, 0);\
                        }\
        QPushButton:pressed {\
            background-color: #1E90FF;\
            border-style: inset;\
        }";

    QString qss2="QTableView , QTableWidget{\
            selection-background-color:#44c767;\
            background-color:#CDC8B1;\
            border:1px solid #E0DDDC;\
            gridline-color:lightgray;\
        }\
        QHeaderView::section{\
            background-color:#CDC8B1;\
            border:0px solid #E0DDDC;\
            border-bottom:1px solid #E0DDDC;\
            height:20px;\
        }";
     _tableView->setStyleSheet(qss2);
     this->setStyleSheet(qss0);
    _AgainGameButton->setStyleSheet(qss1);
    _BackMainFormButton->setStyleSheet(qss1);
//    QFile file(":/res/css.qss");
//    if(file.open(QFile::ReadOnly))
//    {
//         qDebug()<<"File open";
//        QTextStream filetext(&file);
//        QString stylesheet = filetext.readAll();
//        this->setStyleSheet(stylesheet);
//        file.close();
//    }
//    else
//    {
//         qDebug()<<"File not open";

//    }


}
void CalScoreWidget::paintEvent(QPaintEvent* e)
{
         QStyleOption opt;
         opt.init(this);
         QPainter p(this);
         style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

}

void CalScoreWidget::slotAgainGame()
{
    emit sigAgainGame();
}
