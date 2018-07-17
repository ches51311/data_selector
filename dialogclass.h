#ifndef DIALOGCLASS_H
#define DIALOGCLASS_H

#include <QDialog>

namespace Ui {
class dialogclass;
}

class dialogclass : public QDialog
{
    Q_OBJECT

public:
    explicit dialogclass(QWidget *parent = 0);
    ~dialogclass();

private slots:
    void on_btnLeftRight_clicked();

    void on_btnRightLeft_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::dialogclass *ui;
};

#endif // DIALOGCLASS_H
