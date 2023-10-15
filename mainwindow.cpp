#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "feilddata.h"
#include "ceiliter.h"
#include <QDebug>
#include <iostream>
#include <QMessageBox>
#include <queue>
#include "config.h"

//剩余的雷数和剩余的初始数
int remain_mines = Feild->get_mines();
int remain_init = Feild->get_height() * Feild->get_weight();


double factor_Scale=0.9;//缩放因子(自定义),其实最后限制30*19了，这个缩放因子在14寸以上屏幕不会用到。
bool IsScale=false;//是否缩放(缩放了的话鼠标坐标也要缩放)


struct Point
{
    double px;
    double py;
};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    FeildData::getInstance();  //初始化全局数据

    _view = new QGraphicsView;
    this->setCentralWidget(_view); //把_view作为中心组件

    _scene = new MineScene;
    _view->setScene(_scene);


    this->setWindowTitle("扫雷");
    this->showMaximized();
}


void MainWindow::mousePressEvent(QMouseEvent* event)
{
    double mx = event->localPos().x();
    double my = event->localPos().y();

    //需减去上方空格的高度
    QGraphicsItem* item = _view->itemAt(mx, my - 35);
    _item = dynamic_cast<CeilIter*>(item);


//    for(int j = 0 ; j < Feild->get_weight(); j++)
//    {
//        for(int i = 0;i < Feild->get_height();i++)
//            std::cout<<Feild->getCell()[j][i];
//        puts("");
//    }
    if(item != nullptr)
    {
        static double cw = IsScale ?  item->boundingRect().width()*this->width()/_scene->width()*factor_Scale
                                   : item->boundingRect().width();
        static double ch = IsScale ?  item->boundingRect().height()*this->width()/_scene->width()*factor_Scale
                                   : item->boundingRect().height();

        switch (event->button()) {
        case Qt::LeftButton:
            if(INITIAL == _item->getStatus() || QUESTION == _item->getStatus())
            {
                std::cout<<Feild->cell[item->pos().x()/ cw][item->pos().y()/ch]<<std::endl;
                switch (Feild->cell[item->pos().x()/ cw][item->pos().y()/ch]) {
                case -1:
                    --remain_init;
                    _item->setStatus(EXPLODE);
                    QMessageBox::information(this,"end", "you failed...");
                    //std::cout<<"i ma debuging"<<std::endl;
                    on_actionnew_game_triggered();
                    //on_actionconfig_triggered();
                    break;
                case 0:
                    _item->setStatus(BLOCK);
                    --remain_init;JudegWin();
                    expendBlock(mx, my, item->pos().x()/cw, item->pos().y()/ch);
                    break;
                case 1:
                    _item->setStatus(DIGIT, 1);
                    --remain_init;JudegWin();
                    break;
                case 2:   
                    _item->setStatus(DIGIT, 2);
                    --remain_init;JudegWin();
                    break;
                case 3:
                    _item->setStatus(DIGIT, 3);
                    --remain_init;JudegWin();
                    break;
                case 4: 
                    _item->setStatus(DIGIT, 4);
                    --remain_init;JudegWin();
                    break;
                case 5:                    
                    _item->setStatus(DIGIT, 5);
                    --remain_init;JudegWin();
                    break;
                case 6:                   
                    _item->setStatus(DIGIT, 6);
                    --remain_init;JudegWin();
                    break;
                case 7:
                    _item->setStatus(DIGIT, 7);
                    --remain_init;JudegWin();
                    break;
                case 8:
                    _item->setStatus(DIGIT, 8);
                    --remain_init;JudegWin();
                    break;
                default:
                    break;
                }
            }
            else if(FLAG == _item->getStatus()) //左击旗帜，这里不做处理
            {
                ;
            }
            break;
        case Qt::RightButton:
            if(INITIAL == _item->getStatus())
            {
                _item->setStatus(FLAG);
                if(-1 == Feild->cell[item->pos().x()/ cw][item->pos().y()/ch])
                {
                    --remain_mines;
                    this->JudegWin();
                }
            }
            else if(QUESTION == _item->getStatus())
            {
                _item->setStatus(INITIAL);
            }
            else if(FLAG == _item->getStatus())
            {
                _item->setStatus(QUESTION);
                if(-1 == Feild->cell[item->pos().x()/ cw][item->pos().y()/ch])
                {
                    ++remain_mines;
                }
            }
            break;
        default:
            break;
        }
    }
}

void MainWindow::expendBlock(double px, double py, int x, int y)
{
    Feild->initVisited();
    QGraphicsItem* item = _view->itemAt(px, py-35);

    static double cw = IsScale ?  item->boundingRect().width()*this->width()/_scene->width()*factor_Scale
                               : item->boundingRect().width();
    static double ch = IsScale ?  item->boundingRect().height()*this->width()/_scene->width()*factor_Scale
                               : item->boundingRect().height();

    std::queue<std::pair<Point, int>> que;
    que.push({{px,py},x*Feild->get_height() + y });

    int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    Feild->visited[x][y] = 1;
    while(!que.empty())
    {
        auto fr = que.front();
        que.pop();

        px = fr.first.px;
        py = fr.first.py;
        x = fr.second / Feild->get_height();
        y = fr.second % Feild->get_height();


        for(int j = 0; j < 8; j++)
        {
            double npx = px + dx[j] * cw;
            double npy = py + dy[j] * ch;

            int nx = x + dx[j];
            int ny = y + dy[j];

            if(nx < 0 || ny >= Feild->get_height() || ny < 0 || nx >= Feild->get_weight()
                || Feild->visited[nx][ny] == 1)
                continue;

            item = _view->itemAt(npx, npy - 35);
            _item = dynamic_cast<CeilIter*>(item);

            if(FLAG == _item->getStatus())  //碰到棋子，直接返回
                continue;

            if(0 == Feild->getCell()[nx][ny])
            {
                que.push({{npx,npy}, nx * Feild->get_height() + ny});
                Feild->visited[nx][ny] = 1;
                _item->setStatus(BLOCK);
                --remain_init;JudegWin();
            }
            else
            {
                switch (Feild->cell[nx][ny]) {
                case 1:
                    if(_item->getStatus() != DIGIT)
                    {
                        _item->setStatus(DIGIT, 1);
                        remain_init--;JudegWin();
                    }
                    break;
                case 2:
                    if(_item->getStatus() != DIGIT)
                    {
                        _item->setStatus(DIGIT, 2);
                        remain_init--;JudegWin();
                    }
                    break;
                case 3:
                    if(_item->getStatus() != DIGIT)
                    {
                        _item->setStatus(DIGIT, 3);
                        remain_init--;JudegWin();
                    }
                    break;
                case 4:
                    if(_item->getStatus() != DIGIT)
                    {
                        _item->setStatus(DIGIT, 4);
                        remain_init--;JudegWin();
                    }
                    break;
                case 5:
                    if(_item->getStatus() != DIGIT)
                    {
                        _item->setStatus(DIGIT, 5);
                        remain_init--;JudegWin();
                    }
                    break;
                case 6:
                    if(_item->getStatus() != DIGIT)
                    {
                        _item->setStatus(DIGIT, 6);
                        remain_init--;JudegWin();
                    }
                    break;
                case 7:
                    if(_item->getStatus() != DIGIT)
                    {
                        _item->setStatus(DIGIT, 7);
                        remain_init--;JudegWin();
                    }
                    break;
                case 8:
                    if(_item->getStatus() != DIGIT)
                    {
                        _item->setStatus(DIGIT, 8);
                        remain_init--;JudegWin();
                    }
                    break;
                default:
                    break;
                }
            }


        }
    }
}

void MainWindow::deleteScene()
{
    //场景还原
    this->showMaximized();

    if(_scene->width()>this->width()){
        _view->scale(_scene->width()/this->width()/factor_Scale,_scene->width()/
                                                                         this->width()/factor_Scale);
        IsScale=false;
    }
    if(_scene != nullptr)
    {
        delete _scene;
        _scene = nullptr;
    }
}

void MainWindow::NewScene()
{
    _scene = new MineScene;
    _view->setScene(_scene);

    qDebug()<<"debug setScene..";
    this->showMaximized();
    if(_scene->width()>this->width()){
        IsScale=true;
        _view->scale(this->width()/_scene->width()*factor_Scale,
                     this->width()/_scene->width()*factor_Scale);//设置本次窗口大小
    }
    else{
        IsScale=false;
    }


    remain_init = Feild->get_height() * Feild->get_weight();
    remain_mines = Feild->get_mines();
}



MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::JudegWin()
{
    if(remain_init == Feild->get_mines())
    {
        QMessageBox::information(this,"Win","你赢了");
        on_actionnew_game_triggered();
        return true;
    }
    return false;
}


void MainWindow::on_actionnew_game_triggered()
{
    qDebug()<<"new game debuging....";
    deleteScene();
    Feild->customHWM(Feild->get_weight(), Feild->get_height(), Feild->get_mines());
    Feild->reset();
    NewScene();
    qDebug()<<"new game debuging end....";
}


void MainWindow::on_actionquit_triggered()
{
    close();
}


void MainWindow::on_actionabout_triggered()
{
    QMessageBox::about(this,"关于", "AHU CZY SAOLEI version 1.0");
}


void MainWindow::on_actionconfig_triggered()
{
    Config config(Feild->get_weight(), Feild->get_height(), Feild->get_mines());

    if(config.exec() == QDialog::Accepted)
    {
        if(config._mines <  config._height * config.width() * 0.5)
        {
            deleteScene();
            Feild->customHWM(config._weight, config._height, config._mines);
            Feild->reset();
            NewScene();
        }
    }else
    {
        QMessageBox::warning(this, "warning", "to many mines");
    }
}



