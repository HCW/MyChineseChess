#ifndef STONE_H
#define STONE_H

#include <QString>
//棋子类
//
class Stone
{
public:
    Stone();
 //定义棋子的ID、位置、类型（炮、马...），颜色
    int m_ID;

    //类型定义一个枚举
    enum TYPE{
        JIANG,MA,PAO,SHI,RXIANG,BXIANG,BING,ZU,JU,SHUAI
    };

    TYPE m_type;
    bool m_red;//是否是红色
    //位置,行，列
    int m_row;
    int m_col;
    bool m_dead;//棋子的死亡状态

    void StoneInit(int ID);
    QString getType();

};

#endif // STONE_H
