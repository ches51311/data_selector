#include "dialogsaveas.h"
#include "ui_dialogsaveas.h"
#include "mainwindow.h"

extern QString globalsaveas;

dialogsaveas::dialogsaveas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogsaveas)
{
    ui->setupUi(this);
    ui->lineEdit->text() = globalsaveas;
}

dialogsaveas::~dialogsaveas()
{
    delete ui;
}

void dialogsaveas::on_buttonBox_accepted()
{
    globalsaveas = ui->lineEdit->text();
}
