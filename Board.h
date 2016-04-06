#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "Stone.h"
#include "Step.h"
class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);

    //定义32颗棋子
    Stone stone[32];
    int m_r;//定义棋子的半径
    int m_seleceID;//保存被选中棋子的ID
    bool RedReady;//轮流走棋标志

    QVector<Step*> m_steps;//定义一个动态数组来存储走的步数

   void DrawStone(QPainter &painter,int i);//绘制棋子函数
   QPoint center(int row,int col);//计算棋子的中心点，即坐标
   virtual void paintEvent(QPaintEvent *);

   void mouseReleaseEvent(QMouseEvent *);//用来处理走棋
   bool getRowCol(QPoint pt,int &row,int&col);//获取点击的点的行和列
   bool canMove(int moveID,int row,int col,int killID);//判断是否可以移动函数，参数为选中的ID，要移到目标地的row和col，以及目标ID
  //定义每种棋子走棋规则
   bool canMoveJiang(int moveID,int row,int col,int killID);
   bool canMoveShi(int moveID,int row,int col,int killID);
   bool canMoveJu(int moveID,int row,int col,int killID);
   bool canMoveMa(int moveID,int row,int col,int killID);
   bool canMovePao(int moveID,int row,int col,int killID);
   bool canMoveBingZu(int moveID,int row,int col,int killID);
   bool canMoveXiang(int moveID,int row,int col,int killID);

   bool isPreventXiang(int moveID,int row,int col);//判断“象”是否被阻挡
   bool isPreventMa(int moveID,int row,int col);//判断“马”是否被阻挡

   void click(QPoint pt);//鼠标点击棋盘
   virtual void click(int selectID,int row,int col);//重载，并定义为虚函数
   void TrySelectStone(int id);//尝试选择棋子
   void TryMoveStone(int killid,int row,int col);//尝试移动棋子
   bool canselect(int id);//判断是否可以选择棋子
   bool samecolor(int selectid,int killid);//判断两个棋子颜色是否相同
   int getStoneID(int row,int col);//传入行和列，返回棋子ID
   void MoveStone(int seleceID,int row,int col,int killid);//移动棋子
   void MoveStone(int seleceID,int row,int col);//移动棋子
   void killStone(int killid);//吃掉棋子
   void saveStep(int selectid,int killid,int row,int col,QVector<Step*>&_steps);//存储走的棋，用来实现悔棋的功能

   void reliveStone(int id);//复活棋子
signals:

public slots:
};

#endif // BOARD_H
