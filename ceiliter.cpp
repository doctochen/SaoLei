#include "ceiliter.h"
#include <QString>


QPixmap* CeilIter::_block = nullptr;
QPixmap* CeilIter::_digit[9] = {nullptr};
QPixmap* CeilIter::_explode = nullptr;
QPixmap* CeilIter::_flag = nullptr;
QPixmap* CeilIter::_init = nullptr;
QPixmap* CeilIter::_question = nullptr;

int CeilIter::ref_num = 0;


CeilIter::CeilIter(int x, int y, ceilStatus status, QGraphicsPixmapItem *parents)
    :QGraphicsPixmapItem(parents)
{
    this->status = status;
    cx = x;
    cy = y;

    //首次加载图片
    ref_num++;

    if(ref_num == 1)
    {
        _block = new QPixmap(":/images/images/blank.png");
        _explode = new QPixmap(":/images/images/explode.png");
        _flag = new QPixmap(":/images/images/flag.png");
        _init = new QPixmap(":/images/images/initial.png");
        _question = new QPixmap(":/images/images/question.png");

        //:/images/images/3.png
        QString head = ":/images/images/";
        QString trail = ".png";
        QString num;
        for(int j = 1; j <= 8; j++)
        {
            num.setNum(j);
            QString filename = head + num + trail;
            _digit[j] = new QPixmap(filename);
        }
    }

    setPixmap(*_init);
}

CeilIter::~CeilIter()
{
    //释放所有的cellItem后，释放图片
    if(--ref_num == 0)
    {
        delete _block;
        delete _question;
        delete _flag;
        delete _init;
        delete _explode;
        for(int j = 0; j < 9; j++)
        {
            delete _digit[j];
        }
    }
}

void CeilIter::setStatus(ceilStatus status, int digit)
{
    //setPixmap(*_explode);
    this->status = status;
    switch (status) {
    case INITIAL:
        setPixmap(*_init);
        break;
    case BLOCK:
        setPixmap(*_block);
        break;
    case FLAG:
        setPixmap(*_flag);
        break;
    case QUESTION:
        setPixmap(*_question);
        break;
    case EXPLODE:
        setPixmap(*_explode);
        break;
    case DIGIT:
        setPixmap(*_digit[digit]);
        break;
    default:
        break;
    }
}

enum ceilStatus CeilIter::getStatus()
{
    return status;
}
