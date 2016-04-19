#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "Stone.h"
#include "Step.h"
#include <QRgb>
#include <QPushButton>
#include <QSplitter>
#include <QGroupBox>
#include <QLabel>
#include <QTimer>
#include "CalScoreWidget.h"
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
   bool m_sides;//红方棋子在棋盘下边还是上边，如果等于true则在下边，false则在上边

   QVector<Step*> m_steps;//定义一个动态数组来存储走的步数

   void InitGame();//初始化所有参数4
   void setupBoardFacade();//设置棋盘外观
   void InitStoneSides();//初始化棋子
   void DrawBoard(QPainter &painter);//绘制棋盘
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
   bool isWin(int id);//判断是否胜利，胜利则结束游戏
   void restoreBoard();//还原棋盘到一开始的时候

   void UndoStep();//悔棋
   void UndoStep(Step*step);//悔棋
   //定一些按钮
   QPushButton* m_startbutton;//开始
   QPushButton* m_requestbutton;//求和
   QPushButton* m_surrenderbutton;//投降，认输
   QPushButton* m_undobutton;//悔棋

   QSplitter* m_splitterMain;//主分割器
   QGroupBox* m_BlackGroupBox;//黑方对局信息分组框
   QGroupBox* m_RedGroupBox;//红方对局信息分组框
   QGroupBox* m_TimeGroupBox;//对局时间信息分组框
   QLabel*    m_InfoLabel;//信息
   QLabel*   m_BlackNameLabel;//黑方对局名称信息
   QLabel*   m_BlackScoreLabel;//黑方对局积分信息
   QLabel*   m_RedNameLabel;//红方对局名称信息
   QLabel*   m_RedScoreLabel;//红方对局积分信息

   //对局时间设置
   QLabel* m_BlackTimeLabel;//时间
   QLabel* m_RedTimeLabel;

   QTimer*m_BlackTimer;//黑方定时器
   QTimer*m_RedTimer;//红方定时器
   int m_BlackTime;//黑方局时
   int m_RedTime;//红方局时

   void InitTimeSetup();//初始化时间设置

   //定义一个开始下棋标志，该标志不置1，不能下棋
   bool m_StartGameFlag;

   //定义一个对局结果窗体
   CalScoreWidget* _ResultWidget;

signals:
   void sigRedStart();
   void sigRedStop();
   void sigBlackStart();
   void sigBlackStop();
public slots:
   void slotUndoStep();//悔棋
   void slotBlackTime();//黑棋时间处理
   void slotRedTime();//红棋时间处理
   void slotBlackStart();//黑棋时间开始走
   void slotBlackStop();//黑方停止计时
   void slotRedStart();//红棋时间开始走
   void slotRedStop();//红棋停止计时

   void slotStartButtonClick();//开始按钮
   void slotRestore();//重新初始化
};

#endif // BOARD_H
