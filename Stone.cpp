#include "Stone.h"
// 棋子类
Stone::Stone()
{

}
void Stone::StoneInit(int ID)
{
    this->m_ID=ID;//设置棋子的ID
    struct pos{
        int row;
        int col;
        Stone::TYPE type;
    };
    struct pos m_Bpos[]={
    {0,0,JU},
    {0,1,MA},
    {0,2,BXIANG},
    {0,3,SHI},
    {0,4,JIANG},
    {0,5,SHI},
    {0,6,BXIANG},
    {0,7,MA},
    {0,8,JU},
    {2,1,PAO},
    {2,7,PAO},
    {3,0,ZU},
    {3,2,ZU},
    {3,4,ZU},
    {3,6,ZU},
    {3,8,ZU}
    };
    struct pos m_Bpos2[]={
    {9,0,JU},
    {9,1,MA},
    {9,2,BXIANG},
    {9,3,SHI},
    {9,4,JIANG},
    {9,5,SHI},
    {9,6,BXIANG},
    {9,7,MA},
    {9,8,JU},
    {7,1,PAO},
    {7,7,PAO},
    {6,0,ZU},
    {6,2,ZU},
    {6,4,ZU},
    {6,6,ZU},
    {6,8,ZU}
    };
    struct pos m_Rpos[]={
    {9,0,JU},
    {9,1,MA},
    {9,2,RXIANG},
    {9,3,SHI},
    {9,4,SHUAI},
    {9,5,SHI},
    {9,6,RXIANG},
    {9,7,MA},
    {9,8,JU},
    {7,1,PAO},
    {7,7,PAO},
    {6,0,BING},
    {6,2,BING},
    {6,4,BING},
    {6,6,BING},
    {6,8,BING}
    };
    struct pos m_Rpos2[]={
    {0,0,JU},
    {0,1,MA},
    {0,2,RXIANG},
    {0,3,SHI},
    {0,4,SHUAI},
    {0,5,SHI},
    {0,6,RXIANG},
    {0,7,MA},
    {0,8,JU},
    {2,1,PAO},
    {2,7,PAO},
    {3,0,BING},
    {3,2,BING},
    {3,4,BING},
    {3,6,BING},
    {3,8,BING}
    };
    if(this->m_red)//红方
    {
        if(ID>=16)
        {
            ID=ID-16;
            this->m_row=m_Rpos[ID].row;
            this->m_col=m_Rpos[ID].col;
            this->m_type=m_Rpos[ID].type;
        }
        else
        {
            this->m_row=m_Rpos2[ID].row;
            this->m_col=m_Rpos2[ID].col;
            this->m_type=m_Rpos2[ID].type;
        }
    }
    else//黑方
    {
        if(ID<16)
        {

            this->m_row=m_Bpos[ID].row;
            this->m_col=m_Bpos[ID].col;
            this->m_type=m_Bpos[ID].type;
        }
        else
        {
             ID=ID-16;
            this->m_row=m_Bpos2[ID].row;
            this->m_col=m_Bpos2[ID].col;
            this->m_type=m_Bpos2[ID].type;
        }
    }
}
QString Stone::getType()
{
    switch(this->m_type)
    {
        case JU:
            return "车";
        case MA:
            return "马";
        case RXIANG:
            return "相";
        case BXIANG:
            return "象";
        case SHI:
            return "士";
        case SHUAI:
            return "帅";
        case PAO:
            return "炮";
        case BING:
            return "兵";
        case ZU:
            return "卒";
        case JIANG:
            return "将";
        default:
            return 0;
    }
}

