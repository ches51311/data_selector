#include "dialogopenprj.h"
#include "ui_dialogopenprj.h"
#include "mainwindow.h"

extern QStringList globalprjs;
extern QString globalprj;


dialogOpenPrj::dialogOpenPrj(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogOpenPrj)
{
    ui->setupUi(this);

    for (int i =0; i<globalprjs.count(); i++){
        ui->listWidget->addItem(globalprjs.at(i));
    }
}

dialogOpenPrj::~dialogOpenPrj()
{
    delete ui;
}

void dialogOpenPrj::on_buttonBox_accepted()
{
    globalprj = ui->listWidget->currentItem()->text();
}

void dialogOpenPrj::on_buttonBox_rejected()
{
    globalprj.clear();
}
