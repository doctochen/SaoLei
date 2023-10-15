#ifndef FEILDDATA_H
#define FEILDDATA_H
#include <vector>
#include <ctime>

#define Feild (FeildData::getInstance())

using CellCol = std::vector<int>;
using CellMatrix = std::vector<CellCol>;

//棋盘数据全局应当唯一，故使用单例模式设计
class FeildData
{
public:
    ~FeildData();
    static FeildData* getInstance();

    inline int get_weight() {return _weight;};
    inline int get_height() {return _height;};
    inline int get_mines() {return _mines;};

    void initCell();
    void initVisited();
    void reset();
    const CellMatrix& getCell() {return cell;};

    void deployMines();  //放置雷，并初始化棋盘情况
    void customHWM(int weight, int height, int mines);


    CellMatrix cell;  //每个格点的信息
    CellMatrix visited; //每个格点是否没点击过
protected:
    int _weight;
    int _height;
    int _mines; //雷的数量


    void update(int x, int y);  //更新某个格点的数字

private:
    FeildData();
    static FeildData* data;
};

#endif // FEILDDATA_H
