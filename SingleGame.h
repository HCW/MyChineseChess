#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include "Board.h"
class SingleGame:public Board
{

    virtual void click(int selectID,int row,int col);//继承Board，重写click函数

    Step* getbestMove();//电脑走棋
    void getAllPossibleMove(QVector<Step*>&steps);//获取所有可能走得步骤

    void fakeMove(Step*step);//试着走一下
    void unfakeMove(Step*step);//回到原来原来状态
    int calcScore();//返回计算的局面分
    int getMinScore();//获取第二步局面分最小值
};

#endif // SINGLEGAME_H
