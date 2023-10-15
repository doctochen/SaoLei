#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include "minescene.h"
#include <QMouseEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool JudegWin();
    void expendBlock(double px, double py, int x, int y);

    void deleteScene();
    void NewScene();

protected:
    void mousePressEvent(QMouseEvent* event);

private slots:
    void on_actionnew_game_triggered();

    void on_actionquit_triggered();

    void on_actionabout_triggered();

    void on_actionconfig_triggered();

private:
    Ui::MainWindow *ui;

    QGraphicsView* _view;
    MineScene* _scene;
    CeilIter* _item;

};
#endif // MAINWINDOW_H
