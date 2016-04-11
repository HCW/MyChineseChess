#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include "Board.h"
#include <QObject>
class SingleGame:public Board
{
    Q_OBJECT
public:
    SingleGame()
    {
        _level=4;
    }
    virtual void click(int selectID,int row,int col);//继承Board，重写click函数

    Step* getbestMove();//电脑走棋
    void getAllPossibleMove(QVector<Step*>&steps);//获取所有可能走得步骤

    void fakeMove(Step*step);//试着走一下
    void unfakeMove(Step*step);//回到原来原来状态
    int calcScore();//返回计算的局面分
    int getMinScore(int level, int curMaxScore);//获取第二步局面分最小值
    int getMaxScore(int level, int curMinScore);//获取最大值

    int _level;//电脑计算等级
public slots:
    void computerMove();
};

#endif // SINGLEGAME_H
