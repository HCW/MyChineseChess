#ifndef CALSCOREWIDGET_H
#define CALSCOREWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>
class CalScoreWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CalScoreWidget(QWidget *parent = 0);

    void InitForm();//初始化界面
    void InitInfo(QString rp,QString rsta,int rsc,QString bp,QString bsta,int bsc );//初始化对局信息
    virtual void paintEvent(QPaintEvent* e);

    QString _RedPlayerName;//红方玩家名称
    QString _RedStatus;//赢输状态
    QString     _RedScore;//积分

    QString _BlackPlayerName;//黑方玩家名称
    QString _BlackStatus;//赢输状态
    QString     _BlackScore;//积分

    QPushButton* _AgainGameButton;//再来一局
    QPushButton* _BackMainFormButton;//返回主界面

    //定义数据模型视图
    QTableView* _tableView;
    QStandardItemModel*_model;
signals:
    void sigAgainGame();
    void sigBackForm();//返回主界面信号
public slots:
    void slotAgainGame();
    void slotBackForm();
};

#endif // CALSCOREWIDGET_H
