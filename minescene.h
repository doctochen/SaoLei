#ifndef MINESCENE_H
#define MINESCENE_H

#include <vector>
#include <QGraphicsScene>
#include "ceiliter.h"

using CeilCol = std::vector<CeilIter*>;
using CeilMatrix = std::vector<CeilCol>;


class MineScene : public QGraphicsScene
{
public:
    explicit MineScene(QObject *parent = nullptr);
    ~MineScene();

    void initItem();
    void ClearItem();

private:
    CeilMatrix _matrix;
};

#endif // MINESCENE_H
