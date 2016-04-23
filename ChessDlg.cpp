#include "ChessDlg.h"
#include <QVBoxLayout>
#include <QPixmap>
#include <QPalette>
#include <QGridLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QMessageBox>

ChessDlg::ChessDlg(QWidget *parent) : QWidget(parent)
{
    _SingleButton=new QPushButton("人机对战");
    _MultiButton=new QPushButton("多人对战");
    _NetButton=new QPushButton("网络对战");

    _singlegame=new SingleGame;
  //  _netgame=new NetGame();
    _mulitigame=new MulitiGame;

    InitForm();

    connect(_SingleButton,SIGNAL(clicked()),this,SLOT(slotSingleGame()));
    connect(_NetButton,SIGNAL(clicked()),this,SLOT(slotNetGame()));
    connect(_MultiButton,SIGNAL(clicked()),this,SLOT(slotMulitiGame()));
    connect(_singlegame,SIGNAL(sigHandleBackForm()),this,SLOT(slotShow()));
    connect(_NetButton,SIGNAL(sigHandleBackForm()),this,SLOT(slotShow()));
    connect(_mulitigame,SIGNAL(sigHandleBackForm()),this,SLOT(slotShow()));
}
void ChessDlg::InitForm()
{
    QLabel* label=new QLabel("中国象棋");
    QVBoxLayout*vlay=new QVBoxLayout(this);
//    lay->addWidget(_SingleButton);
//    lay->addWidget(_MultiButton);
//    lay->addWidget(_NetButton);

    QGridLayout*glay=new QGridLayout;
    glay->addWidget(_SingleButton,1,1);
    glay->addWidget(_MultiButton,2,1);
    glay->addWidget(_NetButton,3,1);
    glay->setColumnStretch(0,1);
    glay->setColumnStretch(2,1);
    glay->setRowStretch(0,1);
    glay->setRowStretch(4,1);
    glay->setSpacing(10);

    QHBoxLayout*hlay=new QHBoxLayout;
    hlay->addStretch(1);
    hlay->addWidget(label);
     hlay->addStretch(1);
    vlay->addStretch(1);
    vlay->addLayout(hlay);
    vlay->addLayout(glay);
     vlay->addStretch(1);
    QString qss0="QPushButton {\
            background-color: #1E90FF;\
            border-style: outset;\
            border-width: 2px;\
            border-radius: 8px;\
            border-color: white;\
            font: bold 14px;\
            min-width:12em;\
            color:white;\
            font-family:楷体;\
            padding: 5px;\
        }\
        QPushButton:hover{\
        background-color: rgb(0, 150, 0);\
                        }\
        QPushButton:pressed {\
            background-color:#0000FF;\
            border-style: inset;\
        }\
        QPushButton:!enabled{\
                          background-color: rgb(100, 100, 100);\
                          border-style: inset;\
                          }";

    QString qss1="QLabel{\
            font:bold 24px;\
            font-family:隶书;\
            padding: 2px;\
        }";

    _SingleButton->setStyleSheet(qss0);
    _MultiButton->setStyleSheet(qss0);
    _NetButton->setStyleSheet(qss0);
    label->setStyleSheet(qss1);
    //设置背景图片
    QPixmap pixmap=QPixmap(":/new/prefix1/res/ch3.jpg").scaled(this->size());//加载一张图片，大小与窗口匹配
    QPalette palette(this->palette());//定义一个调色板
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    this->setPalette(palette);

    this->setWindowIcon(QIcon(":/new/prefix1/res/logo.png"));


    this->resize(300,300);
    this->setWindowTitle("中国象棋");
    this->setWindowFlags(Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);
}
void ChessDlg::slotSingleGame()
{
    this->hide();
    _singlegame->show();
}
void ChessDlg::slotNetGame()
{
    QMessageBox::StandardButton ret;
    ret=QMessageBox::question(NULL,"提示","是否作为服务器启动？");

    bool bServer=false;//是否是服务器启动
    if(ret==QMessageBox::Yes)
    {
            bServer=true;
    }
    _netgame=new NetGame(bServer);
    this->hide();
    _netgame->show();
}
void ChessDlg::slotMulitiGame()
{
    this->hide();
    _mulitigame->show();
}
void ChessDlg::slotShow()
{
    this->show();
}

