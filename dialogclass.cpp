#include "dialogclass.h"
#include "ui_dialogclass.h"
#include "mainwindow.h"
#include <QDebug>
#include <QString>

extern QStringList globalclsunselect;
extern QStringList globalclsselect;

dialogclass::dialogclass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogclass)
{
    ui->setupUi(this);
    for (int i=0; i<globalclsunselect.count(); i++){
        ui->lsWidgetLeft->addItem(globalclsunselect.at(i));
        ui->lsWidgetLeft->item(i)->setFlags(ui->lsWidgetLeft->item(i)->flags()| Qt::ItemIsUserCheckable);
        ui->lsWidgetLeft->item(i)->setCheckState(Qt::Unchecked);
    }

    for (int i=0; i<globalclsselect.count(); i++){
        ui->lsWidgetRight->addItem(globalclsselect.at(i));
        ui->lsWidgetRight->item(i)->setFlags(ui->lsWidgetRight->item(i)->flags()| Qt::ItemIsUserCheckable);
        ui->lsWidgetRight->item(i)->setCheckState(Qt::Unchecked);
    }


}

dialogclass::~dialogclass()
{
    delete ui;
}


void dialogclass::on_btnLeftRight_clicked()
{
    int row;
    QStringList moveitem;
    for (int i=0; i<ui->lsWidgetLeft->count(); i++){
        if(ui->lsWidgetLeft->item(i)->checkState() == Qt::Checked){
            ui->lsWidgetRight->addItem(ui->lsWidgetLeft->item(i)->text());
            row = ui->lsWidgetRight->count()-1;
            ui->lsWidgetRight->item(row)->setFlags(ui->lsWidgetRight->item(row)->flags()| Qt::ItemIsUserCheckable);
            ui->lsWidgetRight->item(row)->setCheckState(Qt::Unchecked);
            moveitem.append(ui->lsWidgetLeft->item(i)->text());
        }
    }

    for (int i=0; i<moveitem.count(); i++){
        for (int j=0; j<ui->lsWidgetLeft->count(); j++){
            if (moveitem.at(i) == ui->lsWidgetLeft->item(j)->text()){
                ui->lsWidgetLeft->takeItem(j);
            }
        }
    }

}

void dialogclass::on_btnRightLeft_clicked()
{
    int row;
    QStringList moveitem;
    for (int i=0; i<ui->lsWidgetRight->count(); i++){
        if(ui->lsWidgetRight->item(i)->checkState() == Qt::Checked){
            ui->lsWidgetLeft->addItem(ui->lsWidgetRight->item(i)->text());
            row = ui->lsWidgetLeft->count()-1;
            ui->lsWidgetLeft->item(row)->setFlags(ui->lsWidgetLeft->item(row)->flags()| Qt::ItemIsUserCheckable);
            ui->lsWidgetLeft->item(row)->setCheckState(Qt::Unchecked);
            moveitem.append(ui->lsWidgetRight->item(i)->text());
        }
    }

    for (int i=0; i<moveitem.count(); i++){
        for (int j=0; j<ui->lsWidgetRight->count(); j++){
            if (moveitem.at(i) == ui->lsWidgetRight->item(j)->text()){
                ui->lsWidgetRight->takeItem(j);
            }
        }
    }
}

void dialogclass::on_buttonBox_accepted()
{
    globalclsunselect.clear();
    globalclsselect.clear();
    for (int i=0; i<ui->lsWidgetLeft->count(); i++){
        globalclsunselect.append(ui->lsWidgetLeft->item(i)->text());
    }
    for (int i=0; i<ui->lsWidgetRight->count(); i++){
        globalclsselect.append(ui->lsWidgetRight->item(i)->text());
    }

}

void dialogclass::on_buttonBox_rejected()
{

}
