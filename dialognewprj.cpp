#include "dialognewprj.h"
#include "ui_dialognewprj.h"
#include "mainwindow.h"

extern QString globalnewprj;

dialognewprj::dialognewprj(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialognewprj)
{
    ui->setupUi(this);
}

dialognewprj::~dialognewprj()
{
    delete ui;
}

void dialognewprj::on_buttonBox_accepted()
{
    globalnewprj = ui->lineEdit->text();
}
