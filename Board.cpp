 #include "Board.h"
#include <QPainter>
#include<QMouseEvent>
#include <math.h>
Board::Board(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("中国象棋");
    for(int i=0;i<32;++i)
    {
        if(i<16)//黑方，0-15为棋子的ID
        {
            stone[i].m_red=false;
            stone[i].StoneInit(i);
            stone[i].m_dead=false;
        }
        else//  红方，16-31，棋子ID
        {
            stone[i].m_red=true;
            stone[i].StoneInit(i);
            stone[i].m_dead=false;
        }
    }
    m_seleceID=-1;//初始化，等于-1表示棋子还未被选中
    RedReady=true;//红方先行
}
void Board::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //绘制棋盘
    int d=40;//棋子直径，用来衡量棋盘的大小
    m_r=d/2;//保存半径
    for(int i=1;i<=10;++i)//绘制10行
    {
        painter.drawLine(QPoint(d,d*i),QPoint(9*d,d*i));
    }

    for(int i=1;i<=9;++i)//绘制9条竖线
    {
        if(i==1||i==9)
            painter.drawLine(QPoint(d*i,d),QPoint(d*i,d*10));
        else
        {
            painter.drawLine(QPoint(d*i,d),QPoint(d*i,d*5));
             painter.drawLine(QPoint(d*i,6*d),QPoint(d*i,d*10));
        }
    }
    //绘制棋盘中间的九宫格
      painter.drawLine(QPoint(4*d,d),QPoint(d*6,d*3));
      painter.drawLine(QPoint(6*d,d),QPoint(d*4,d*3));

      painter.drawLine(QPoint(4*d,8*d),QPoint(d*6,d*10));
      painter.drawLine(QPoint(6*d,d*8),QPoint(d*4,d*10));

      //绘制棋盘的特殊形状
      //上方、左边 炮的位置
      painter.drawLine(QPoint(2*d-4,3*d-15),QPoint(d*2-4,d*3-4));
      painter.drawLine(QPoint(2*d-15,d*3-4),QPoint(d*2-4,d*3-4));

      painter.drawLine(QPoint(2*d+4,3*d-15),QPoint(d*2+4,d*3-4));
      painter.drawLine(QPoint(2*d+15,d*3-4),QPoint(d*2+4,d*3-4));

      painter.drawLine(QPoint(2*d-15,3*d+4),QPoint(d*2-4,d*3+4));
      painter.drawLine(QPoint(2*d-4,d*3+15),QPoint(d*2-4,d*3+4));

      painter.drawLine(QPoint(2*d+4,3*d+4),QPoint(d*2+15,d*3+4));
      painter.drawLine(QPoint(2*d+4,d*3+15),QPoint(2*d+4,3*d+4));

       //上方、右边 炮的位置
      painter.drawLine(QPoint(8*d-4,3*d-15),QPoint(d*8-4,d*3-4));
      painter.drawLine(QPoint(8*d-15,d*3-4),QPoint(d*8-4,d*3-4));

      painter.drawLine(QPoint(8*d+4,3*d-15),QPoint(d*8+4,d*3-4));
      painter.drawLine(QPoint(8*d+15,d*3-4),QPoint(d*8+4,d*3-4));

      painter.drawLine(QPoint(8*d-15,3*d+4),QPoint(d*8-4,d*3+4));
      painter.drawLine(QPoint(8*d-4,d*3+15),QPoint(d*8-4,d*3+4));

      painter.drawLine(QPoint(8*d+4,3*d+4),QPoint(d*8+15,d*3+4));
      painter.drawLine(QPoint(8*d+4,d*3+15),QPoint(8*d+4,3*d+4));


      //下方、左边 炮的位置
      painter.drawLine(QPoint(2*d-4,8*d-15),QPoint(d*2-4,d*8-4));
      painter.drawLine(QPoint(2*d-15,d*8-4),QPoint(d*2-4,d*8-4));

      painter.drawLine(QPoint(2*d+4,8*d-15),QPoint(d*2+4,d*8-4));
      painter.drawLine(QPoint(2*d+15,d*8-4),QPoint(d*2+4,d*8-4));

      painter.drawLine(QPoint(2*d-15,8*d+4),QPoint(d*2-4,d*8+4));
      painter.drawLine(QPoint(2*d-4,d*8+15),QPoint(d*2-4,d*8+4));

      painter.drawLine(QPoint(2*d+4,8*d+4),QPoint(d*2+15,d*8+4));
      painter.drawLine(QPoint(2*d+4,d*8+15),QPoint(2*d+4,8*d+4));


      //下方、右边 炮的位置
     painter.drawLine(QPoint(8*d-4,8*d-15),QPoint(d*8-4,d*8-4));
     painter.drawLine(QPoint(8*d-15,d*8-4),QPoint(d*8-4,d*8-4));

     painter.drawLine(QPoint(8*d+4,8*d-15),QPoint(d*8+4,d*8-4));
     painter.drawLine(QPoint(8*d+15,d*8-4),QPoint(d*8+4,d*8-4));

     painter.drawLine(QPoint(8*d-15,8*d+4),QPoint(d*8-4,d*8+4));
     painter.drawLine(QPoint(8*d-4,d*8+15),QPoint(d*8-4,d*8+4));

     painter.drawLine(QPoint(8*d+4,8*d+4),QPoint(d*8+15,d*8+4));
     painter.drawLine(QPoint(8*d+4,d*8+15),QPoint(8*d+4,8*d+4));

     //卒子位置，上方，左边角 1
     painter.drawLine(QPoint(1*d+4,4*d-15),QPoint(d*1+4,d*4-4));
     painter.drawLine(QPoint(1*d+15,d*4-4),QPoint(d*1+4,d*4-4));

     painter.drawLine(QPoint(1*d+4,4*d+4),QPoint(d*1+15,d*4+4));
     painter.drawLine(QPoint(1*d+4,d*4+15),QPoint(1*d+4,4*d+4));

     //卒子位置，上方， 3 位
     painter.drawLine(QPoint(3*d-4,4*d-15),QPoint(d*3-4,d*4-4));
     painter.drawLine(QPoint(3*d-15,d*4-4),QPoint(d*3-4,d*4-4));

     painter.drawLine(QPoint(3*d+4,4*d-15),QPoint(d*3+4,d*4-4));
     painter.drawLine(QPoint(3*d+15,d*4-4),QPoint(d*3+4,d*4-4));

     painter.drawLine(QPoint(3*d-15,4*d+4),QPoint(d*3-4,d*4+4));
     painter.drawLine(QPoint(3*d-4,d*4+15),QPoint(d*3-4,d*4+4));

     painter.drawLine(QPoint(3*d+4,4*d+4),QPoint(d*3+15,d*4+4));
     painter.drawLine(QPoint(3*d+4,d*4+15),QPoint(3*d+4,4*d+4));

     //卒子位置，上方， 5 位
     painter.drawLine(QPoint(5*d-4,4*d-15),QPoint(d*5-4,d*4-4));
     painter.drawLine(QPoint(5*d-15,d*4-4),QPoint(d*5-4,d*4-4));

     painter.drawLine(QPoint(5*d+4,4*d-15),QPoint(d*5+4,d*4-4));
     painter.drawLine(QPoint(5*d+15,d*4-4),QPoint(d*5+4,d*4-4));

     painter.drawLine(QPoint(5*d-15,4*d+4),QPoint(d*5-4,d*4+4));
     painter.drawLine(QPoint(5*d-4,d*4+15),QPoint(d*5-4,d*4+4));

     painter.drawLine(QPoint(5*d+4,4*d+4),QPoint(d*5+15,d*4+4));
     painter.drawLine(QPoint(5*d+4,d*4+15),QPoint(5*d+4,4*d+4));

     //卒子位置，上方， 7 位
     painter.drawLine(QPoint(7*d-4,4*d-15),QPoint(d*7-4,d*4-4));
     painter.drawLine(QPoint(7*d-15,d*4-4),QPoint(d*7-4,d*4-4));

     painter.drawLine(QPoint(7*d+4,4*d-15),QPoint(d*7+4,d*4-4));
     painter.drawLine(QPoint(7*d+15,d*4-4),QPoint(d*7+4,d*4-4));

     painter.drawLine(QPoint(7*d-15,4*d+4),QPoint(d*7-4,d*4+4));
     painter.drawLine(QPoint(7*d-4,d*4+15),QPoint(d*7-4,d*4+4));

     painter.drawLine(QPoint(7*d+4,4*d+4),QPoint(d*7+15,d*4+4));
     painter.drawLine(QPoint(7*d+4,d*4+15),QPoint(7*d+4,4*d+4));

     //卒子位置，上方， 9 位
     painter.drawLine(QPoint(9*d-4,4*d-15),QPoint(d*9-4,d*4-4));
     painter.drawLine(QPoint(9*d-15,d*4-4),QPoint(d*9-4,d*4-4));

     painter.drawLine(QPoint(9*d-15,4*d+4),QPoint(d*9-4,d*4+4));
     painter.drawLine(QPoint(9*d-4,d*4+15),QPoint(d*9-4,d*4+4));

    //卒子下方
     //卒子位置，下方，左边角 1
     painter.drawLine(QPoint(1*d+4,7*d-15),QPoint(d*1+4,d*7-4));
     painter.drawLine(QPoint(1*d+15,d*7-4),QPoint(d*1+4,d*7-4));

     painter.drawLine(QPoint(1*d+4,7*d+4),QPoint(d*1+15,d*7+4));
     painter.drawLine(QPoint(1*d+4,d*7+15),QPoint(1*d+4,7*d+4));

     //卒子位置，下方， 3 位
     painter.drawLine(QPoint(3*d-4,7*d-15),QPoint(d*3-4,d*7-4));
     painter.drawLine(QPoint(3*d-15,d*7-4),QPoint(d*3-4,d*7-4));

     painter.drawLine(QPoint(3*d+4,7*d-15),QPoint(d*3+4,d*7-4));
     painter.drawLine(QPoint(3*d+15,d*7-4),QPoint(d*3+4,d*7-4));

     painter.drawLine(QPoint(3*d-15,7*d+4),QPoint(d*3-4,d*7+4));
     painter.drawLine(QPoint(3*d-4,d*7+15),QPoint(d*3-4,d*7+4));

     painter.drawLine(QPoint(3*d+4,7*d+4),QPoint(d*3+15,d*7+4));
     painter.drawLine(QPoint(3*d+4,d*7+15),QPoint(3*d+4,7*d+4));

     //卒子位置，下方， 5 位
     painter.drawLine(QPoint(5*d-4,7*d-15),QPoint(d*5-4,d*7-4));
     painter.drawLine(QPoint(5*d-15,d*7-4),QPoint(d*5-4,d*7-4));

     painter.drawLine(QPoint(5*d+4,7*d-15),QPoint(d*5+4,d*7-4));
     painter.drawLine(QPoint(5*d+15,d*7-4),QPoint(d*5+4,d*7-4));

     painter.drawLine(QPoint(5*d-15,7*d+4),QPoint(d*5-4,d*7+4));
     painter.drawLine(QPoint(5*d-4,d*7+15),QPoint(d*5-4,d*7+4));

     painter.drawLine(QPoint(5*d+4,7*d+4),QPoint(d*5+15,d*7+4));
     painter.drawLine(QPoint(5*d+4,d*7+15),QPoint(5*d+4,7*d+4));

     //卒子位置，下方， 7 位
     painter.drawLine(QPoint(7*d-4,7*d-15),QPoint(d*7-4,d*7-4));
     painter.drawLine(QPoint(7*d-15,d*7-4),QPoint(d*7-4,d*7-4));

     painter.drawLine(QPoint(7*d+4,7*d-15),QPoint(d*7+4,d*7-4));
     painter.drawLine(QPoint(7*d+15,d*7-4),QPoint(d*7+4,d*7-4));

     painter.drawLine(QPoint(7*d-15,7*d+4),QPoint(d*7-4,d*7+4));
     painter.drawLine(QPoint(7*d-4,d*7+15),QPoint(d*7-4,d*7+4));

     painter.drawLine(QPoint(7*d+4,7*d+4),QPoint(d*7+15,d*7+4));
     painter.drawLine(QPoint(7*d+4,d*7+15),QPoint(7*d+4,7*d+4));

     //卒子位置，下方， 9 位
     painter.drawLine(QPoint(9*d-4,7*d-15),QPoint(d*9-4,d*7-4));
     painter.drawLine(QPoint(9*d-15,d*7-4),QPoint(d*9-4,d*7-4));

     painter.drawLine(QPoint(9*d-15,7*d+4),QPoint(d*9-4,d*7+4));
     painter.drawLine(QPoint(9*d-4,d*7+15),QPoint(d*9-4,d*7+4));

     //绘制棋子
     for(int j=0;j<32;++j)
        DrawStone(painter,j);

}
QPoint Board::center(int row, int col)
{
    QPoint ret;
    ret.rx()=(col+1)*m_r*2;//根据棋子所在行和列和半径计算出棋子的坐标
    ret.ry()=(row+1)*m_r*2;
    return ret;
}
void Board::DrawStone(QPainter &painter,int i)
{
       if(stone[i].m_dead)//如果棋子死了，就不用再画
           return;
       QPoint stoCenter=center(stone[i].m_row,stone[i].m_col);
       QRect rt=QRect(stoCenter.rx()-m_r,stoCenter.ry()-m_r,m_r*2,2*m_r);//创建一个矩形来摆放棋子的名称
       painter.setFont(QFont("system",24));
       painter.setBrush(QBrush(QColor("yellow")));
         if(stone[i].m_red)
         {
            if(i==m_seleceID)//改变选中的棋子的颜色
            {
                painter.setBrush(QColor(Qt::gray));
                painter.drawEllipse(stoCenter,m_r,m_r);//画圆
                painter.drawText(rt,stone[i].getType(),QTextOption(Qt::AlignCenter));
            }
             else
            {
                painter.setPen(QColor("red"));
                painter.drawEllipse(stoCenter,m_r,m_r);//画圆
                painter.drawText(rt,stone[i].getType(),QTextOption(Qt::AlignCenter));
            }
         }
         else
         {
             if(i==m_seleceID)
             {
                 painter.setBrush(QColor(Qt::gray));
                 painter.drawEllipse(stoCenter,m_r,m_r);//画圆
                 painter.drawText(rt,stone[i].getType(),QTextOption(Qt::AlignCenter));
             }
              else
             {
                 painter.setPen(QColor("black"));
                 painter.drawEllipse(stoCenter,m_r,m_r);//画圆
                 painter.drawText(rt,stone[i].getType(),QTextOption(Qt::AlignCenter));
             }
         }
}
//该函数的作用判断点击的坐标属于棋盘上的哪个位置，true表示得到点击的位置
bool Board::getRowCol(QPoint pt, int &row, int &col)
{
    //需要判断该坐标属于哪一个行哪一列，使用最笨的方法遍历棋盘所有的点，距离小于m_r半径说明该点属于所在行
    for(int i=0;i<10;++i)
    {
        for(int j=0;j<9;++j)
        {
            //根据行列获得棋子中心坐标
            QPoint s=center(i,j);
            int dx=pt.rx()-s.rx();
            int dy=pt.ry()-s.ry();
            int dist=dx*dx+dy*dy;
            if(dist<m_r*m_r)    //距离小于半径，说明该点有棋子，返回true
            {
                row=i;
                col=j;
                return true;
            }
        }
    }
    return false;
}
void Board::mouseReleaseEvent(QMouseEvent *ev)
{
    QPoint pt=ev->pos();//获得点击的坐标
    click(pt);
 //    //要判断该点是否有棋子，需要把坐标转换为行和列，并遍历棋子
//    int row,col;//保存选中的棋子的行列
//    int id;
//    int clickID=-1;//保存被吃掉棋子的ＩＤ
//    if(m_seleceID==-1)
//    {
//        if(getRowCol(pt,row,col))//定义一个函数进行处理
//        {
//            //选中了该棋子，找出该棋子ID，并改变其颜色用来表示被选中
//            for(id=0;id<32;++id)
//                if(stone[id].m_row==row&&stone[id].m_col==col&&stone[id].m_dead==false)
//                    break;
//            if(id<32)
//            {
//                if(RedReady==stone[id].m_red)//选中的棋子颜色和轮到其走的一致则可以选中
//                {
//                  m_seleceID=id;
//                  update();
//                }
//                else
//                    return;
//            }
//        }
//        else
//            return;
//    }
//    else //这里是走棋的实现，但是我们走棋前需要判定一下规则，就是能不能走
//    {
//           if(getRowCol(pt,row,col))//定义一个函数进行处理,获得第二次点击的点
//            {
//                for(id=0;id<32;++id)
//                    if(stone[id].m_row==row&&stone[id].m_col==col&&stone[id].m_dead==false)
//                        break;
//                if(id<32)
//                    clickID=id;//保存第二次点击的棋子位置的ID，没有棋子则为-1
//                if(canMove(m_seleceID,row,col,clickID))//判断是否可走
//                {
//                    if(clickID!=-1)
//                    {
//                        stone[clickID].m_dead=true;//如果该点有棋子，则吃掉
//                    }
//                    stone[m_seleceID].m_row=row;//移动到该点
//                    stone[m_seleceID].m_col=col;
//                    m_seleceID=-1;//置标志
//                    update();
//                    RedReady=!RedReady;//每次走完取反
//                }

//            }
//            else
//                return;//没有找到点

//    }

}
void Board::click(QPoint pt)
{
//    //要判断该点是否有棋子，需要把坐标转换为行和列，并遍历棋子
//    int row,col;//保存选中的棋子的行列
//    int id;
//    int clickID=-1;//保存被吃掉棋子的ＩＤ
//    if(m_seleceID==-1)
//    {
//        if(getRowCol(pt,row,col))//定义一个函数进行处理,true表示有棋子
//        {
//            //选中了该棋子，找出该棋子ID，并改变其颜色用来表示被选中
//            id=getStoneID(row,col);
//            if(id<32)
//            {
//                if(RedReady==stone[id].m_red)//选中的棋子颜色和轮到其走的一致则可以选中
//                {
//                  m_seleceID=id;
//                  update();
//                }
//                else
//                    return;
//            }
//        }
//    }
    //点击进来，先判断有没有点中棋子，没点中则直接返回
    int row,col;
    bool clickID=getRowCol(pt,row,col);//获取点击的坐标是否有棋子，有则返回true，row，col是引用传参，
    if(!clickID) return;

    int selectID=getStoneID(row,col);//获取点击选中的棋子ID
    click(selectID,row,col);//重载调用该click函数
}
void Board::click(int selectID, int row, int col)
{
    if(m_seleceID==-1)//第一次点击，选中第一个棋子
    {
       TrySelectStone(selectID);
    }
    else//第二次点击，尝试移动棋子
    {
       TryMoveStone(selectID,row,col);
    }
}
void Board::TryMoveStone(int killid, int row, int col)
{
   if(killid!=-1&&samecolor(m_seleceID,killid))//如果第二次点中了棋子并且棋子颜色是相同的则再次选中，不移动
   {
       TrySelectStone(killid);
       return;
   }
   //待续
   int rt=canMove(m_seleceID,row,col,killid);//判断是否该路线可以移动
   if(rt)
   {
       MoveStone(m_seleceID,row,col,killid);
       m_seleceID=-1;
       update();
   }

}
void Board::MoveStone(int seleceID, int row, int col, int killid)
{
    saveStep(seleceID,killid,row,col,m_steps);//存储步
    killStone(killid);//吃掉棋子
    MoveStone(seleceID,row,col);//真正移动棋子
}
void Board::MoveStone(int seleceID, int row, int col)
{
    stone[seleceID].m_row=row;//移动到该点
    stone[seleceID].m_col=col;
    update();
    RedReady=!RedReady;//每次走完取反
}
void Board::saveStep(int selectid, int killid, int row, int col,QVector<Step*>&_steps)
{
    //存储一步棋，要保存原来的位置以及要移到位置
    Step* step=new Step();
    step->fromID=selectid;
    step->fromRow=stone[selectid].m_row;
    step->fromCol=stone[selectid].m_col;
    step->toID=killid;
    step->toRow=row;
    step->toCol=col;

    _steps.append(step);//添加到动态数组的尾部
}
void Board::reliveStone(int id)
{
    if(id==-1) return;

    stone[id].m_dead=false;
}
void Board::killStone(int killid)
{
    if(killid==-1) return;//如果第二次没有选中棋子则不需吃子，直接移动
    stone[killid].m_dead=true;//吃掉
}
void Board::TrySelectStone(int id)
{
    if(id==-1) return;//第一次点击，如果是-1说明没有点中棋子

    if(!canselect(id)) return;//判断是否可以选择

    //可以选择
    m_seleceID=id;//把ID保存下来
    update();

}
bool Board::samecolor(int selectid, int killid)
{
    if(selectid==-1|| killid==-1) return false;
    return stone[selectid].m_red==stone[killid].m_red;
}
bool Board::canselect(int id)
{
     return RedReady==stone[id].m_red;//如果轮流走棋次序一致，返回true
}
int Board::getStoneID(int row, int col)
{
    int id;
    for(id=0;id<32;++id)
    {
        if(stone[id].m_row==row&&stone[id].m_col==col&&stone[id].m_dead==false)
        {
            return id;//该点击的点有棋子返回该棋子ID号
        }
    }
    return -1;//该点击的点没有棋子则返回-1
}
bool Board::canMove(int moveID, int row, int col, int killID)
{
    /*1、需要判断的是不能吃掉同一方，如果连续两次选中的是同一方，说明先前选错，需要换选择
   */
    if(stone[moveID].m_red==stone[killID].m_red)
    {
        m_seleceID=killID;
        update();
        return false;
    }
  /*
    2、判断棋子类型，根据棋子类型定义走棋规则，判断是否可以走

    */
    switch (stone[moveID].m_type) {
    case Stone::JIANG:
        return canMoveJiang(moveID,row,col,killID);
        break;
    case Stone::MA:
        return canMoveMa(moveID,row,col,killID);
        break;
    case Stone::PAO:
        return canMovePao(moveID,row,col,killID);
        break;
    case Stone::SHI:
          return canMoveShi(moveID,row,col,killID);//
        break;
    case Stone::SHUAI:
        return canMoveJiang(moveID,row,col,killID);//帅和将一样，调同样的函数
        break;
    case Stone::BING:
         return canMoveBingZu(moveID,row,col,killID);
        break;
    case Stone::ZU:
        return canMoveBingZu(moveID,row,col,killID);
        break;
    case Stone::RXIANG:
        return canMoveXiang(moveID,row,col,killID);
        break;
    case Stone::BXIANG:
        return canMoveXiang(moveID,row,col,killID);
        break;
    case Stone::JU:
        return canMoveJu(moveID,row,col,killID);
        break;
    default:
        break;
    }
    return true;
}
bool Board::canMoveBingZu(int moveID, int row, int col, int )
{
    //兵、卒的走棋规则，也是只能走直线，而且只能走一格，只能前进，没过河之前只能前进，不能左右和后退，
    //过河之后可以左右，不可后退
    //1，不是直线，错误走法
    if(stone[moveID].m_row!=row&&stone[moveID].m_col!=col)
        return false;
    //2,只能前进
    if(stone[moveID].m_red)//兵
    {
        //首先判断过没过河，兵不在，5,6行说明过了河
        if(stone[moveID].m_row!=5&&stone[moveID].m_row!=6)//过了河
        {
            //其次是不能后退,且只能移动一个位置
             if(stone[moveID].m_row-row!=1&&abs(stone[moveID].m_col-col)!=1)
                 return false;

        }
        else//没过河
        {
            //其次是不能后退,且只能移动一个位置,不能左右移动
             if(stone[moveID].m_row-row!=1||stone[moveID].m_col-col!=0)
                 return false;
        }
    }
    else//卒
    {
        //首先判断过没过河，卒不在，3,4行说明过了呵
        if(stone[moveID].m_row!=3&&stone[moveID].m_row!=4)//过了河
        {
            //其次是不能后退,且只能移动一个位置
             if(stone[moveID].m_row-row!=-1&&abs(stone[moveID].m_col-col)!=1)
                 return false;

        }
        else//没过河
        {
            //其次是不能后退,且只能移动一个位置,不能左右移动
             if(stone[moveID].m_row-row!=-1||stone[moveID].m_col-col!=0)
                 return false;
        }
    }

    return true;

}
bool Board::canMoveJu(int moveID, int row, int col, int )
{
    /*车的走法规则，也是只能走直线*/
    //1，不是直线，错误走法
    if(stone[moveID].m_row!=row&&stone[moveID].m_col!=col)
        return false;
    //不管目标位置有没有棋子，中间都不能有棋子，否则不能移动
    if(stone[moveID].m_row==row)//车横行，判断横行路线是否有棋子
    {
        int d=stone[moveID].m_col-col;//原来位置到目标位置间的距离
        int count=0;//保存中间有几个棋子
        if(d<0)
        {
         for(int i=stone[moveID].m_col+1;i<col;++i)
         {
             for(int j=0;j<32;++j)
                 if(stone[j].m_col==i&&stone[j].m_row==row&&stone[j].m_dead==false)
                     count++;
         }
         if(count==0)//没有棋子，可以移动，并吃掉
             return true;
         else//中间有棋子或者不止一个棋子不能移动
             return false;
        }
        else
        {
            for(int i=col+1;i<stone[moveID].m_col;++i)
            {
                for(int j=0;j<32;++j)
                    if(stone[j].m_col==i&&stone[j].m_row==row&&stone[j].m_dead==false)
                        count++;
            }
            if(count==0)//没有棋子，可以移动，并吃掉
                return true;
            else//中间有棋子或者不止一个棋子不能移动
                return false;
        }

    }
    else if(stone[moveID].m_col==col)//车列行
    {
        int d=stone[moveID].m_row-row;//原来位置到目标位置间的距离
        int count=0;//保存中间有几个棋子
        if(d<0)
        {
             for(int i=stone[moveID].m_row+1;i<row;++i)
             {
                 for(int j=0;j<32;++j)
                     if(stone[j].m_row==i&&stone[j].m_col==col&&stone[j].m_dead==false)
                         count++;
             }
             if(count==0)//没有棋子，可以移动，并吃掉
                 return true;
             else//中间有棋子或者不止一个棋子不能移动
                 return false;
        }
        else
        {
                for(int i=row+1;i<stone[moveID].m_row;++i)
                {
                    for(int j=0;j<32;++j)
                        if(stone[j].m_row==i&&stone[j].m_col==col&&stone[j].m_dead==false)
                            count++;
                }
                if(count==0)//没有棋子，可以移动，并吃掉
                    return true;
                else//中间有棋子或者不止一个棋子不能移动
                    return false;
        }
    }

}
bool Board::canMovePao(int moveID, int row, int col, int )
{
 /*
炮的走棋规则，只能直线走
*/
    //1，不是直线，错误走法
    if(stone[moveID].m_row!=row&&stone[moveID].m_col!=col)
        return false;

    //2、炮的移动，目标位置如果没有棋子，则移动路线不能有棋子；目标位置有棋子，则移动路线只能有一个棋子
    int id;
    for(id=0;id<32;++id)
    {
        if(stone[id].m_row==row&&stone[id].m_col==col&&stone[id].m_dead==false)
            break;
    }
    if(id<32)//目标位置有棋子
    {
        if(stone[moveID].m_row==row)//炮横行，判断横行路线只有一个棋子
        {
            int d=stone[moveID].m_col-col;//原来位置到目标位置间的距离
            int count=0;//保存中间有几个棋子
            if(d<0)
            {
             for(int i=stone[moveID].m_col+1;i<col;++i)
             {
                 for(int j=0;j<32;++j)
                     if(stone[j].m_col==i&&stone[j].m_row==row&&stone[j].m_dead==false)
                         count++;
             }
             if(count==1)//有一个棋子，可以移动，并吃掉
                 return true;
             else//中间没有棋子或者不止一个棋子不能移动
                 return false;
            }
            else
            {
                for(int i=col+1;i<stone[moveID].m_col;++i)
                {
                    for(int j=0;j<32;++j)
                        if(stone[j].m_col==i&&stone[j].m_row==row&&stone[j].m_dead==false)
                            count++;
                }
                if(count==1)//有一个棋子，可以移动，并吃掉
                    return true;
                else//中间没有棋子或者不止一个棋子不能移动
                    return false;
            }

        }
        else if(stone[moveID].m_col==col)//炮列行
        {
            int d=stone[moveID].m_row-row;//原来位置到目标位置间的距离
            int count=0;//保存中间有几个棋子
            if(d<0)
            {
                 for(int i=stone[moveID].m_row+1;i<row;++i)
                 {
                     for(int j=0;j<32;++j)
                         if(stone[j].m_row==i&&stone[j].m_col==col&&stone[j].m_dead==false)
                             count++;
                 }
                 if(count==1)//有一个棋子，可以移动，并吃掉
                     return true;
                 else//中间没有棋子或者不止一个棋子不能移动
                     return false;
            }
            else
            {
                    for(int i=row+1;i<stone[moveID].m_row;++i)
                    {
                        for(int j=0;j<32;++j)
                            if(stone[j].m_row==i&&stone[j].m_col==col&&stone[j].m_dead==false)
                                count++;
                    }
                    if(count==1)//有一个棋子，可以移动，并吃掉
                        return true;
                    else//中间没有棋子或者不止一个棋子不能移动
                        return false;
            }
        }
    }
    else//目标位置没有棋子,则移动路线不能有棋子
    {
          if(stone[moveID].m_row==row)//炮横行，
          {
              int d=stone[moveID].m_col-col;//原来位置到目标位置间的距离
              int count=0;//保存中间有几个棋子
              if(d<0)
              {
               for(int i=stone[moveID].m_col+1;i<col;++i)
               {
                   for(int j=0;j<32;++j)
                       if(stone[j].m_col==i&&stone[j].m_row==row&&stone[j].m_dead==false)
                           count++;
               }
               if(count>0)//有棋子，不可以移动，
                   return false;
               else//中间没有棋子能移动
                   return true;
              }
              else
              {
                  for(int i=col+1;i<stone[moveID].m_col;++i)
                  {
                      for(int j=0;j<32;++j)
                          if(stone[j].m_col==i&&stone[j].m_row==row&&stone[j].m_dead==false)
                              count++;
                  }
                  if(count>0)//有棋子，不可以移动，
                      return false;
                  else//中间没有棋子能移动
                      return true;
              }
          }
          else if(stone[moveID].m_col==col)//炮列行
          {
              int d=stone[moveID].m_row-row;//原来位置到目标位置间的距离
              int count=0;//保存中间有几个棋子
              if(d<0)
              {
                   for(int i=stone[moveID].m_row+1;i<row;++i)
                   {
                       for(int j=0;j<32;++j)
                           if(stone[j].m_row==i&&stone[j].m_col==col&&stone[j].m_dead==false)
                               count++;
                   }
                   if(count>0)//有棋子，不可以移动，
                       return false;
                   else//中间没有棋子能移动
                       return true;
              }
              else
              {
                      for(int i=row+1;i<stone[moveID].m_row;++i)
                      {
                          for(int j=0;j<32;++j)
                              if(stone[j].m_row==i&&stone[j].m_col==col&&stone[j].m_dead==false)
                                  count++;
                      }
                      if(count>0)//有棋子，不可以移动，
                          return false;
                      else//中间没有棋子能移动
                          return true;
              }
          }
    }
}
bool Board::canMoveJiang(int moveID, int row, int col, int)
{
    /*
     将或者帅的移动，规则：
     1、要移动的位置必须在九宫格内，否则无效
     2、每次只能走一格，而且只能直线行走
     3、当将和帅面对面时可以直接吃掉（这个后面再实现）
     */

    //1、判断是否在九宫格内
    if(stone[moveID].m_type==Stone::JIANG)
    {
        if(row>2||(col<3)||col>5)
            return false;
        //  2、每次只能走一格，而且只能直线行走
        int dx=stone[moveID].m_row-row;
        int dy=stone[moveID].m_col-col;//dx，dy绝对值必定是1个等于1一个等于0才是合法走法，不能对角线走
        int d=abs(dx)+abs(dy);
        if(d==1)
            return true;
        else
            return false;

    }
    if(stone[moveID].m_type==Stone::SHUAI)//同理
    {
        if(row<7||(col<3)||col>5)
            return false;
        //  2、每次只能走一格，而且只能直线行走
        int dx=stone[moveID].m_row-row;
        int dy=stone[moveID].m_col-col;//dx，dy绝对值必定是1个等于1一个等于0才是合法走法，不能对角线走
        int d=abs(dx)+abs(dy);
        if(d==1)
            return true;
        else
            return false;
    }

    return true;
}
 bool Board::canMoveShi(int moveID,int row,int col,int )
 {
     /*
      士的移动，规则：
      1、要移动的位置必须在九宫格内，否则无效
      2、每次只能走一格，而且只能对角线行走
      */

     //1、判断是否在九宫格内，先判断是不是红方
     if(stone[moveID].m_type==Stone::SHI)
     {
         if(stone[moveID].m_red)//是红方
         {
             if(row<7||(col<3)||col>5)
                 return false;
         }
         else//黑方
         {
             if(row>2||(col<3)||col>5)
                 return false;
         }
         //  2、每次只能走一格，而且只能对角线行走
         int dx=stone[moveID].m_row-row;
         int dy=stone[moveID].m_col-col;//dx，dy绝对值必定是都等于1才是合法走法，不能直线走
         int d=abs(dx)*10+abs(dy);//两个数其中一个乘以10再相加，如果是对角线则是：10*1+1=11；其他情况都得不到11
         if(d==11)
             return true;
         else
             return false;

     }
     return true;
 }
 bool Board::isPreventXiang(int moveID, int row, int col)//被阻挡返回true
 {
     //1，要想阻止“象”移动，只要“田”的中点有棋子就可以，所以首先找出该点
     int drow;
     int dcol;
     //a、找出该点的行和列
     if(stone[moveID].m_row>row)
         drow=row+1;
     else
         drow=stone[moveID].m_row+1;
     if(stone[moveID].m_col>col)
         dcol=col+1;
     else
         dcol=stone[moveID].m_col+1;
    //b、判断该行、列是否有棋子
     int id;
     for(id=0;id<32;++id)
     {
        if(stone[id].m_row==drow&&stone[id].m_col==dcol&&stone[id].m_dead==false)
         break;
     }
     if(id<32)//有棋子
         return true;
      else
         return false;

 }
 bool Board::canMoveXiang(int moveID,int row,int col,int )
 {
     /*
      象的移动，规则，只能在走“田字”的对角线，
      1、象走的列：0，2，4，6,8，行：红相：5，7，9；黑象：0,2,4

      3、当象走的位置正确，还要判断象有没有被卡死，如果被卡死则不能走，写一个函数isPreventXiang()
       */


     if(!(col==0||col==2||col==4||col==6||col==8))//不管红或黑都一样
         return false;
     if(stone[moveID].m_red)//红方“相”
     {
         if(!(row==5||row==7||row==9))
             return false;
         int dx=stone[moveID].m_row-row;
         int dy=stone[moveID].m_col-col;//dx，dy绝对值必定是都等于1才是合法走法，不能直线走
         int d=abs(dx)*10+abs(dy);//两个数其中一个乘以10再相加，如果是对角线则是：10*2+2=22；其他情况都得不到22
         if(d==22)
         {
             if(isPreventXiang(moveID,row,col))//移动位置正确，判断是否被阻挡
                 return false;
             else
                 return true;
         }
         else
             return false;
     }
     else// 黑方“象”
     {
         if(!(row==0||row==2||row==4))
             return false;
         int dx=stone[moveID].m_row-row;
         int dy=stone[moveID].m_col-col;//dx，dy绝对值必定是都等于1才是合法走法，不能直线走
         int d=abs(dx)*10+abs(dy);//两个数其中一个乘以10再相加，如果是对角线则是：10*2+2=22；其他情况都得不到22
         if(d==22)
         {
             if(isPreventXiang(moveID,row,col))//移动位置正确，判断是否被阻挡
                 return false;
             else
                 return true;
         }
         else
             return false;

     }
     return true;
 }
 bool Board::isPreventMa(int moveID, int row, int col)//返回true说明被阻挡
 {
     /*马的走法比较灵活，一共有上、下、左、右四个方向可走，每个方向有两种走法，
      所以首先需要判断走的是哪个方向的哪种走法，再去判断是否被阻挡。
    1，方向上左，上右，下左，下右，走法沿y方向走，沿x方向走
    */
     if(stone[moveID].m_row-row>0)//在上边
     {
         if(stone[moveID].m_col-col>0)//上左
         {
            if(stone[moveID].m_row-row==2&&stone[moveID].m_col-col==1) //沿y方向
            {
                //判断该棋子的上面一个位置是否有其它棋子阻挡
                int yrow=stone[moveID].m_row-1;
                int ycol=stone[moveID].m_col;
                //判断改行、列是否有棋子
                int id;
                for(id=0;id<32;++id)
                {
                   if(stone[id].m_row==yrow&&stone[id].m_col==ycol&&stone[id].m_dead==false)
                    break;
                }
                if(id<32)//有棋子
                    return true;
                 else
                    return false;
            }
            else if(stone[moveID].m_row-row==1&&stone[moveID].m_col-col==2)//沿x方向
            {

                //判断该棋子的上面一个位置是否有其它棋子阻挡
                int xrow=stone[moveID].m_row;
                int xcol=stone[moveID].m_col-1;
                //判断改行、列是否有棋子
                int id;
                for(id=0;id<32;++id)
                {
                   if(stone[id].m_row==xrow&&stone[id].m_col==xcol&&stone[id].m_dead==false)
                    break;
                }
                if(id<32)//有棋子
                    return true;
                 else
                    return false;
            }
         }
         else//上右
         {
             if(stone[moveID].m_row-row==2&&stone[moveID].m_col-col==-1) //沿y方向
             {
                 //判断该棋子的上面一个位置是否有其它棋子阻挡
                 int yrow=stone[moveID].m_row-1;
                 int ycol=stone[moveID].m_col;
                 //判断改行、列是否有棋子
                 int id;
                 for(id=0;id<32;++id)
                 {
                    if(stone[id].m_row==yrow&&stone[id].m_col==ycol&&stone[id].m_dead==false)
                     break;
                 }
                 if(id<32)//有棋子
                     return true;
                  else
                     return false;
             }
             else if(stone[moveID].m_row-row==1&&stone[moveID].m_col-col==-2)//沿x方向
             {

                 //判断该棋子的上面一个位置是否有其它棋子阻挡
                 int xrow=stone[moveID].m_row;
                 int xcol=stone[moveID].m_col+1;
                 //判断改行、列是否有棋子
                 int id;
                 for(id=0;id<32;++id)
                 {
                    if(stone[id].m_row==xrow&&stone[id].m_col==xcol&&stone[id].m_dead==false)
                     break;
                 }
                 if(id<32)//有棋子
                     return true;
                  else
                     return false;
             }

         }
     }
     else//在下边
     {
         if(stone[moveID].m_col-col>0)//下左
         {
            if(stone[moveID].m_row-row==-2&&stone[moveID].m_col-col==1) //沿y方向
            {
                //判断该棋子的上面一个位置是否有其它棋子阻挡
                int yrow=stone[moveID].m_row+1;
                int ycol=stone[moveID].m_col;
                //判断改行、列是否有棋子
                int id;
                for(id=0;id<32;++id)
                {
                   if(stone[id].m_row==yrow&&stone[id].m_col==ycol&&stone[id].m_dead==false)
                    break;
                }
                if(id<32)//有棋子
                    return true;
                 else
                    return false;
            }
            else if(stone[moveID].m_row-row==-1&&stone[moveID].m_col-col==2)//沿x方向
            {

                //判断该棋子的上面一个位置是否有其它棋子阻挡
                int xrow=stone[moveID].m_row;
                int xcol=stone[moveID].m_col-1;
                //判断改行、列是否有棋子
                int id;
                for(id=0;id<32;++id)
                {
                   if(stone[id].m_row==xrow&&stone[id].m_col==xcol&&stone[id].m_dead==false)
                    break;
                }
                if(id<32)//有棋子
                    return true;
                 else
                    return false;
            }
         }
         else//下右
         {
             if(stone[moveID].m_row-row==-2&&stone[moveID].m_col-col==-1) //沿y方向
             {
                 //判断该棋子的上面一个位置是否有其它棋子阻挡
                 int yrow=stone[moveID].m_row+1;
                 int ycol=stone[moveID].m_col;
                 //判断改行、列是否有棋子
                 int id;
                 for(id=0;id<32;++id)
                 {
                    if(stone[id].m_row==yrow&&stone[id].m_col==ycol&&stone[id].m_dead==false)
                     break;
                 }
                 if(id<32)//有棋子
                     return true;
                  else
                     return false;
             }
             else if(stone[moveID].m_row-row==-1&&stone[moveID].m_col-col==-2)//沿x方向
             {

                 //判断该棋子的上面一个位置是否有其它棋子阻挡
                 int xrow=stone[moveID].m_row;
                 int xcol=stone[moveID].m_col+1;
                 //判断改行、列是否有棋子
                 int id;
                 for(id=0;id<32;++id)
                 {
                    if(stone[id].m_row==xrow&&stone[id].m_col==xcol&&stone[id].m_dead==false)
                     break;
                 }
                 if(id<32)//有棋子
                     return true;
                  else
                     return false;
             }
         }

     }


 }
bool Board::canMoveMa(int moveID, int row, int col, int )
{
    /*马走的是“日”字*/
    int dx=stone[moveID].m_row-row;
    int dy=stone[moveID].m_col-col;//dx，dy绝对值必定是都等于1才是合法走法，不能直线走
    int d1=abs(dx)+abs(dy)*10;//两个数其中一个乘以10再相加，
    int d2=abs(dx)*10+abs(dy);
    if(d1==12)
    {
        if(isPreventMa(moveID,row,col))//被阻挡
            return false;
        else
            return true;
    }
    else if(d2==12)
    {
        if(isPreventMa(moveID,row,col))//被阻挡
            return false;
        else
            return true;
    }
    else
        return false;
}
















