#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>

namespace Ui {
class Config;
}

class Config : public QDialog
{
    Q_OBJECT

public:
    explicit Config(int w, int h, int m, QWidget *parent = nullptr);
    ~Config();

    int _weight;
    int _height;
    int _mines;

public slots:
    void virtual accept() override;


private:
    Ui::Config *ui;
};

#endif // CONFIG_H
