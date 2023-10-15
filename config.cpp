#include "config.h"
#include "ui_config.h"
#include <QIntValidator>
#include <QDebug>
#include <QDialogButtonBox>

Config::Config(int w, int h, int m, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Config)
{
    ui->setupUi(this);

    _weight = w;
    _height = h;
    _mines = m;

    QIntValidator* weightVal = new QIntValidator(1, 30, this);
    QIntValidator* heightVal = new QIntValidator(1, 19, this);
    QIntValidator* minesVal = new QIntValidator(1, 570, this);

    ui->lineEdit->setValidator(weightVal);
    ui->lineEdit_2->setValidator(heightVal);
    ui->lineEdit_3->setValidator(minesVal);

    ui->lineEdit->setText(QString::number(_weight));
    ui->lineEdit_2->setText(QString::number(_height));
    ui->lineEdit_3->setText(QString::number(_mines));
    qDebug()<<"debug ui..";
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
}

Config::~Config()
{
    delete ui;
}

void Config::accept()
{
    _weight = ui->lineEdit->text().toInt();
    _height = ui->lineEdit_2->text().toInt();
    _mines = ui->lineEdit_3->text().toInt();

    QDialog::accept();
}
