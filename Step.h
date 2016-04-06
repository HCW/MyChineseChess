#ifndef STEP_H
#define STEP_H

#include <QObject>
class Step:public QObject
{
public:
    Step();

    int fromID;//原来棋子的id
    int fromRow;
    int fromCol;
    int toID;//目标位置的id
    int toRow;
    int toCol;
};

#endif // STEP_H
