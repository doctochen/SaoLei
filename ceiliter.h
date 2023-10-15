#ifndef CEILITER_H
#define CEILITER_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

//每个格点的状态
enum ceilStatus
{
    INITIAL, EXPLODE, BLOCK, QUESTION, FLAG,DIGIT
};

//方格的类
class CeilIter : public QGraphicsPixmapItem
{
public:
    CeilIter(int x, int y, enum ceilStatus status = INITIAL,
        QGraphicsPixmapItem* parents = Q_NULLPTR);

    ~CeilIter();
    void setStatus(enum ceilStatus status, int digit = -2);
    enum ceilStatus getStatus();

    static QPixmap* _init;
    static QPixmap* _explode;
    static QPixmap* _block;
    static QPixmap* _question;
    static QPixmap* _flag;
    static QPixmap* _digit[9];

    static int ref_num;  //引用计数，图片仅需被初始化一次

private:
    int cx, cy;
    enum ceilStatus status;
};

#endif // CEILITER_H
