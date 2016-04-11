#include "SingleGame.h"
#include <QTimer>
void SingleGame::click(int selectID, int row, int col)
{
    //人机对弈，电脑执黑
    if(!this->RedReady)
        return;

    Board::click(selectID,row,col);//如果人走，调用父类函数
    emit sigRedStop();//红方走完，发射红方时间停止信号
    emit sigBlackStart();//发射黑方时间开始信号
    if(!this->RedReady)
    {
        /* 启动0.1秒定时器，在0.1秒后电脑再思考 */
       // QTimer::singleShot(100, this, SLOT(computerMove()));
        QTimer::singleShot(5000,this,SLOT(computerMove()));

    }
}
void SingleGame::computerMove()
{
    Step* step=getbestMove();
    MoveStone(step->fromID,step->toRow,step->toCol,step->toID);
    delete step;
    update();
    emit sigRedStart();//同理
    emit sigBlackStop();
}

void SingleGame::getAllPossibleMove(QVector<Step *> &steps)
{
    int min=0;
    int max=16;
    if(this->RedReady)//红棋
    {
        min=16;
        max=32;
    }
    for(int i=min;i<max;++i)//遍历所有黑棋，0-1为黑棋ID
    {
        if(stone[i].m_dead) continue;//如果棋子死了，跳过
        for(int row=0;row<=9;++row)
        {
            for(int col=0;col<=8;++col)
            {
                int killid=this->getStoneID(row,col);
                if(samecolor(killid,i)) continue;//如果是相同颜色，跳过

                if(canMove(i,row,col,killid))
                {
                    saveStep(i,killid,row,col,steps);//把可能走的步存起来
                }
            }
        }
    }
}
Step* SingleGame::getbestMove()
{
    /*
        1,看看有哪些步骤可以走
        2，试着走一下
        3，评估走的结果
        4，取最好的结果的作为参考
    */
    //2016.4.6实现两步人工智能，使用最小最大值算法

    // 1,看看有哪些步骤可以走
    QVector<Step*> steps;
    getAllPossibleMove(steps);

    //2，试着走一下
    int maxScore=-100000;//保存最大的局面分
    Step* ret=NULL;
    while(steps.count())
    {
        Step* step=steps.back();
        steps.removeLast();
        fakeMove(step);//电脑试着走一下，不是真的走
        int score=getMinScore(_level-1, maxScore);//走一步，计算此时的局面分
        unfakeMove(step);//恢复到原来

        if(score>maxScore)//在最小值里面找出最好的局面分
        {
            maxScore=score;
            if(ret) delete ret;
            ret=step;
        }
        else
        {
            delete step;
        }
    }
    return ret;
    //4，取最好的结果的作为参考

}
int SingleGame::getMinScore(int level, int curMaxScore)
{
    if(level == 0) return calcScore();

    // 1.看看有那些步骤可以走
    QVector<Step*> steps;
    getAllPossibleMove(steps);   // 是红旗的possiblemove

    int minScore = 100000;
    while(steps.count())
    {
        Step* step = steps.back();
        steps.removeLast();

        fakeMove(step);
        int score = getMaxScore(level-1, minScore);
        unfakeMove(step);
        delete step;

        if(score <= curMaxScore)
        {
            while(steps.count())
            {
                Step* step = steps.back();
                steps.removeLast();
                delete step;
            }
            return score;
        }

        if(score < minScore)
        {
            minScore = score;
        }

    }
    return minScore;
}
int SingleGame::getMaxScore(int level, int curMinScore)
{
    if(level == 0) return calcScore();

    // 1.看看有那些步骤可以走
    QVector<Step*> steps;
    getAllPossibleMove(steps);   // 是红旗的possiblemove

    int maxScore = -100000;
    while(steps.count())
    {
        Step* step = steps.back();
        steps.removeLast();

        fakeMove(step);
        int score = getMinScore(level-1, maxScore);
        unfakeMove(step);
        delete step;

        if(score >= curMinScore)
        {
            while(steps.count())
            {
                Step* step = steps.back();
                steps.removeLast();
                delete step;
            }
            return score;
        }
        if(score > maxScore)
        {
            maxScore = score;
        }

    }
    return maxScore;
}
void SingleGame::fakeMove(Step *step)
{
    killStone(step->toID);
    MoveStone(step->fromID,step->toRow,step->toCol);//移动棋子
}
void SingleGame::unfakeMove(Step *step)
{
    //复活原来的杀死的棋子
    reliveStone(step->toID);
    MoveStone(step->fromID,step->fromRow,step->fromCol);//移动回原来的位置
}
//评价局面分
int SingleGame::calcScore()
{
    int redTotalScore=0;
    int blackTotalScore=0;
   //为每种棋子设定一个分数，根据计算分值
   // enum TYPE{JIANG,MA,PAO,SHI,RXIANG,BXIANG,BING,ZU,JU,SHUAI};
    static int chessScore[]={1500,50,50,10,10,10,10,10,100,1500};

    //局面分，黑棋分的总数-红棋分的总数
    for(int i=16;i<32;++i)
    {
        if(stone[i].m_dead) continue;
        redTotalScore+=chessScore[stone[i].m_type];//红棋总分
    }
    for(int i=0;i<16;++i)
    {
        if(stone[i].m_dead) continue;
        blackTotalScore+=chessScore[stone[i].m_type];//黑棋总分
    }

    return blackTotalScore-redTotalScore;
}
