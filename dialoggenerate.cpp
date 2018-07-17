#include "dialoggenerate.h"
#include "ui_dialoggenerate.h"
#include "mainwindow.h"
#include <QDebug>


extern int globaltestvalue;
extern int globaltrainvalue;
extern int globalvalvalue;
dialoggenerate::dialoggenerate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialoggenerate)
{
    ui->setupUi(this);

    ui->spinBoxTest->setSuffix("%");
    ui->spinBoxTrain->setSuffix("%");
    ui->spinBoxVal->setSuffix("%");

}

dialoggenerate::~dialoggenerate()
{
    delete ui;
}


void dialoggenerate::on_spinBoxTest_valueChanged(int arg1)
{
    globaltestvalue = arg1;
    ui->spinBoxTrain->setRange(0,100-globaltestvalue-globalvalvalue);
    ui->spinBoxVal->setRange(0,100-globaltrainvalue-globaltestvalue);
}

void dialoggenerate::on_spinBoxTrain_valueChanged(int arg1)
{
    globaltrainvalue = arg1;
    ui->spinBoxTest->setRange(0,100-globaltrainvalue-globalvalvalue);
    ui->spinBoxVal->setRange(0,100-globaltrainvalue-globaltestvalue);
}

void dialoggenerate::on_spinBoxVal_valueChanged(int arg1)
{
    globalvalvalue = arg1;
    ui->spinBoxTrain->setRange(0,100-globaltestvalue-globalvalvalue);
    ui->spinBoxTest->setRange(0,100-globaltrainvalue-globalvalvalue);
}

void dialoggenerate::on_buttonBox_accepted()
{
    globaltestvalue = ui->spinBoxTest->value();
    globaltrainvalue = ui->spinBoxTrain->value();
    globalvalvalue = ui->spinBoxVal->value();

}

void dialoggenerate::on_buttonBox_rejected()
{
    globaltestvalue = -1;
}

void dialoggenerate::on_dialoggenerate_finished(int result)
{
    globaltestvalue = -1;
}
