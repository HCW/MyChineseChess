#include "NetGame.h"
#include <QDebug>
/*
通讯报文结构：

（1）判断执黑还是红：第一个字节固定是1，第二个字节是1表示接收方走红棋否则走黑棋

（2）点击信息：第一个字节固定是2，第二个字节是表示发送方的row，第三个字节是col，第四个字节是棋子id

 (3)开始游戏（有一方点击开始就开始）：第一个字节固定3，第二个字节为表示开始
 （4）对局时间更新：第一个字节固定为4，第二个字节表示哪一方，1表示红方时间走，0表示黑方时间走
*/
NetGame::NetGame(bool bServer)
{
    _server=NULL;
    _socket=NULL;

    if(bServer)
    {
        _server=new QTcpServer(this);
        _server->listen(QHostAddress::Any,9999);
        connect(_server,SIGNAL(newConnection()),this,SLOT(slotNewConnection()));
    }
    else
    {
        _socket=new QTcpSocket(this);
        _socket->connectToHost(QHostAddress("127.0.0.1"),9999);

        //客户端接收报文
        connect(_socket,SIGNAL(readyRead()),this,SLOT(slotRecv()));
    }

}
void NetGame::slotRecv()
{
    QByteArray buf=_socket->readAll();
    char cmd=buf[0];
    switch (cmd) {
    case 1:
        //判断第二个字节，决定执红还是黑
        if(buf[1]==0)
             InitStoneSides(false);
        else
        {
            InitStoneSides(true);
        }
        break;
    case 2:
    {
        int row=buf[1];
        int col=buf[2];
        int id=buf[3];
        Board::click(id,row,col);
    }
        break;
    case 3:
        if(buf[1]==1)
        {
            Board::slotStartButtonClick();
        }
        break;
    case 4:
        if(buf[1]==1)
        {
            emit sigBlackStop();
            emit sigRedStart();
        }
        else if(buf[1]==0)
        {
            emit sigRedStop();
            emit sigBlackStart();
        }
        break;
    }
}
void NetGame::slotNewConnection()
{
    if(_socket) return;//为空说明客户端未登陆

    _socket=_server->nextPendingConnection();//接受一个客户端连接返回一个通讯套接字
    connect(_socket,SIGNAL(readyRead()),this,SLOT(slotRecv()));//服务器同样需要处理报文
    //向客户端发送报文（1）

    char buf[2];
    buf[0]=1;
    buf[1]=0;//设定服务器为红方，客户端执黑
    _socket->write(buf,2);
    //InitGame(true);//默认服务器为红方

    qDebug()<<"connected";
}
void NetGame::click(int selectID, int row, int col)
{
    static int TempID=-23;
    if(m_seleceID == -1 && selectID !=-1 )
    {
        if(stone[selectID].m_red!=m_sides)
            return;
    }

    Board::click(selectID,row,col);//
    TempID=m_seleceID;//保存正在走棋的一方
    //发送给对方，报文（2）
    char buf[4];
    buf[0]=2;
    buf[1]=9-row;
    buf[2]=8-col;
    if(selectID==-1)
        buf[3]=selectID;
    else
        buf[3]=31-selectID;

    _socket->write(buf,4);//发送给客户端
   if(m_seleceID==-1)//走完一步棋,改变时间
   {
       if(stone[TempID].m_red)
       {
           emit sigRedStop();
           emit sigBlackStart();
           char buf[2];
           buf[0]=4;
           buf[1]=0;
           _socket->write(buf,2);
       }
       else//黑方时间
       {
           emit sigBlackStop();
           emit sigRedStart();
           char buf[2];
           buf[0]=4;
           buf[1]=1;
           _socket->write(buf,2);
       }
   }
}
void NetGame::slotStartButtonClick()
{
    Board::slotStartButtonClick();
    //发送报文(3)
    char buf[2];
    buf[0]=3;
    buf[1]=1;
    _socket->write(buf,2);
}
