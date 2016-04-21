#ifndef NETGAME_H
#define NETGAME_H

#include "Board.h"
#include <QTcpServer>
#include <QTcpSocket>
class NetGame : public Board
{
    Q_OBJECT
public:
    NetGame(bool bServer);

    QTcpServer* _server;//定义一个服务器
    QTcpSocket* _socket;

  virtual void click(int selectID,int row,int col);//重写该函数
  virtual void slotStartButtonClick();//重写该函数
  public slots:
    void slotNewConnection();
    void slotRecv();
};

#endif // NETGAME_H
