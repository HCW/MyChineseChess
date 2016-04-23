#ifndef CHESSDLG_H
#define CHESSDLG_H

#include <QWidget>
#include <QPushButton>
#include "Board.h"
#include "SingleGame.h"
#include "NetGame.h"
#include "MulitiGame.h"

class ChessDlg : public QWidget
{
    Q_OBJECT
public:
    explicit ChessDlg(QWidget *parent = 0);

    QPushButton* _SingleButton;
    QPushButton* _NetButton;
    QPushButton* _MultiButton;

    //定义
    SingleGame* _singlegame;//人机
    NetGame*    _netgame;//网络对战
    MulitiGame* _mulitigame;//自己和自己下
    void InitForm();//初始化界面
signals:

public slots:
    void slotSingleGame();
    void slotNetGame();
    void slotMulitiGame();
    void slotShow();
};

#endif // CHESSDLG_H
