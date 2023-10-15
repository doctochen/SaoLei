#include "feilddata.h"
#include <ctime>
#include <cstdlib>
FeildData* FeildData::data = nullptr;

FeildData::~FeildData()
{

}

FeildData *FeildData::getInstance()
{
    if(data == nullptr)
    {
        data = new FeildData;
    }
    return data;
}


void FeildData::initCell()
{
    for(int j = 0; j < _weight; j++)
        cell.push_back(CellCol(_height));

}

void FeildData::initVisited()
{
    for(int j = 0; j < _weight; j++)
        visited.push_back(CellCol(_height));

    for(int j = 0; j < _weight; j++)
        for(int i = 0; i < _height; i++)
            visited[j][i] = 0;
}

void FeildData::reset()
{
    cell.clear();
    initCell();
    deployMines();

    visited.clear();
    initVisited();
}


void FeildData::deployMines()
{
    for(int j = 0; j < _weight; j++)
        for(int i = 0; i < _height; i++)
            cell[j][i] = 0;

    int compase = _mines;
    while(compase)
    {
        int x = rand() % _weight;
        int y = rand() % _height;

        if(cell[x][y] != -1)
        {
            compase--;
            cell[x][y] = -1;

            int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
            int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
            for(int j = 0; j < 8; j++)
            {
                int a = x + dx[j], b = y + dy[j];
                update(a, b);
            }
        }
    }

}

void FeildData::customHWM(int weight, int height, int mines)
{
    _weight = weight;
    _height = height;
    _mines = mines;
}

void FeildData::update(int x, int y)
{
    if(x >= 0 && x < _weight && y >= 0 && y < _height)
    {
        if(cell[x][y] != -1)
            cell[x][y] ++;
    }
}

FeildData::FeildData() : _weight(20), _height(15), _mines(50)
{
    srand(time(nullptr));
    reset();
}
