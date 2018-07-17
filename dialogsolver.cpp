#include "dialogsolver.h"
#include "ui_dialogsolver.h"
#include "mainwindow.h"
#include <QDebug>


extern QStringList globalsolver;
extern QStringList globalsolverkey;

dialogsolver::dialogsolver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogsolver)
{
    ui->setupUi(this);


    ui->comboBox_0->setCurrentText(globalsolver[0]);
    ui->comboBox_1->setCurrentText(globalsolver[1]);
    ui->comboBox_2->setCurrentText(globalsolver[2]);
    ui->comboBox_3->setCurrentText(globalsolver[3]);
    ui->comboBox_4->setCurrentText(globalsolver[4]);
    ui->comboBox_5->setCurrentText(globalsolver[5]);
    ui->comboBox_6->setCurrentText(globalsolver[6]);
    ui->comboBox_7->setCurrentText(globalsolver[7]);
    ui->lineEdit_8->setText(globalsolver[8]);
    ui->lineEdit_9->setText(globalsolver[9]);
    ui->lineEdit_10->setText(globalsolver[10]);
    ui->lineEdit_11->setText(globalsolver[11]);
    ui->lineEdit_12->setText(globalsolver[12]);
    ui->lineEdit_13->setText(globalsolver[13]);
    ui->lineEdit_14->setText(globalsolver[14]);
    ui->lineEdit_15->setText(globalsolver[15]);
    ui->lineEdit_16->setText(globalsolver[16]);
    ui->lineEdit_17->setText(globalsolver[17]);
    ui->lineEdit_18->setText(globalsolver[18]);
    ui->lineEdit_19->setText(globalsolver[19]);
    ui->lineEdit_20->setText(globalsolver[20]);
    ui->lineEdit_21->setText(globalsolver[21]);
    ui->lineEdit_22->setText(globalsolver[22]);
    ui->lineEdit_23->setText(globalsolver[23]);


    ui->lineEdit_21->setEnabled(false);
    ui->lineEdit_22->setEnabled(false);
    ui->lineEdit_23->setEnabled(false);



    QRegExp rxInt("[1-9]\[0-9]*");
    QRegExp rxRealFraction("[0]\(.[0-9]*)");
    QRegExp rxRealNumber("(^-?[0-9])\[0-9]*\(.[0-9]*)");

    //QRegExp rx("/^0./[1-9]");

    //QValidator *validator1 = new QIntValidator(0,1000,this);
    QValidator *v8 = new QRegExpValidator(rxRealNumber,this);
    QValidator *v9 = new QRegExpValidator(rxRealNumber,this);
    QValidator *v10 = new QRegExpValidator(rxRealFraction,this);
    QValidator *v11 = new QRegExpValidator(rxRealFraction,this);
    QValidator *v12 = new QRegExpValidator(rxInt,this);
    QValidator *v13 = new QRegExpValidator(rxInt,this);
    QValidator *v14 = new QRegExpValidator(rxInt,this);
    QValidator *v15 = new QRegExpValidator(rxInt,this);
    QValidator *v16 = new QRegExpValidator(rxInt,this);
    QValidator *v17 = new QRegExpValidator(rxInt,this);
    QValidator *v18 = new QIntValidator(0,10,this);
    QValidator *v19 = new QRegExpValidator(rxInt,this);


    ui->lineEdit_8->setValidator(v8);
    ui->lineEdit_9->setValidator(v9);
    ui->lineEdit_10->setValidator(v10);
    ui->lineEdit_11->setValidator(v11);
    ui->lineEdit_12->setValidator(v12);
    ui->lineEdit_13->setValidator(v13);
    ui->lineEdit_14->setValidator(v14);
    ui->lineEdit_15->setValidator(v15);
    ui->lineEdit_16->setValidator(v16);
    ui->lineEdit_17->setValidator(v17);
    ui->lineEdit_18->setValidator(v18);
    ui->lineEdit_19->setValidator(v19);

}

dialogsolver::~dialogsolver()
{
    delete ui;
}

void dialogsolver::on_buttonBox_accepted()
{
    globalsolver.clear();
    globalsolver.append(ui->comboBox_0->currentText());
    globalsolver.append(ui->comboBox_1->currentText());
    globalsolver.append(ui->comboBox_2->currentText());
    globalsolver.append(ui->comboBox_3->currentText());
    globalsolver.append(ui->comboBox_4->currentText());
    globalsolver.append(ui->comboBox_5->currentText());
    globalsolver.append(ui->comboBox_6->currentText());
    globalsolver.append(ui->comboBox_7->currentText());
    globalsolver.append(ui->lineEdit_8->text());
    globalsolver.append(ui->lineEdit_9->text());
    globalsolver.append(ui->lineEdit_10->text());
    globalsolver.append(ui->lineEdit_11->text());
    globalsolver.append(ui->lineEdit_12->text());
    globalsolver.append(ui->lineEdit_13->text());
    globalsolver.append(ui->lineEdit_14->text());
    globalsolver.append(ui->lineEdit_15->text());
    globalsolver.append(ui->lineEdit_16->text());
    globalsolver.append(ui->lineEdit_17->text());
    globalsolver.append(ui->lineEdit_18->text());
    globalsolver.append(ui->lineEdit_19->text());
    globalsolver.append(ui->lineEdit_20->text());
    globalsolver.append(ui->lineEdit_21->text());
    globalsolver.append(ui->lineEdit_22->text());
    globalsolver.append(ui->lineEdit_23->text());

}
