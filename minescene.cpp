#include "minescene.h"
#include "feilddata.h"
#include <QDebug>

MineScene::MineScene(QObject *parent)
    : QGraphicsScene{parent}
{
    //addItem(new CeilIter(10,10)); //测试

    initItem();
}

MineScene::~MineScene()
{
    ClearItem();
}

void MineScene::initItem()
{
    int w = Feild->get_weight();
    int h = Feild->get_height();

    qDebug()<<w<<' '<<h;
    for(int j = 0; j < w; j++)
    {
        _matrix.push_back(CeilCol());
        for(int i = 0; i < h; i++)
        {
            _matrix[j].push_back(new CeilIter(j, i));
            static int cw = _matrix[0][0]->boundingRect().width();
            static int ch = _matrix[0][0]->boundingRect().height();

            _matrix[j][i]->setPos(j * cw, i * ch);
            addItem(_matrix[j][i]);
        }
    }
    qDebug()<<"debug matrix success";
}

void MineScene::ClearItem()
{
    int w = Feild->get_weight();
    int h = Feild->get_height();

    for(int j = 0; j < w; j++)
    {
        for(int i = 0; i < h; i++)
        {
            delete _matrix[j][i];
            _matrix[j][i] = nullptr;
        }
    }
    _matrix.clear();
}
