#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "Stone.h"
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
signals:

public slots:
};

#endif // BOARD_H
