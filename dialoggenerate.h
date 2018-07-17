#ifndef DIALOGGENERATE_H
#define DIALOGGENERATE_H


#include <QDialog>

namespace Ui {
class dialoggenerate;
}

class dialoggenerate : public QDialog
{
    Q_OBJECT

public:
    explicit dialoggenerate(QWidget *parent = 0);
    ~dialoggenerate();

private slots:
    void on_spinBoxTest_valueChanged(int arg1);

    void on_spinBoxTrain_valueChanged(int arg1);

    void on_spinBoxVal_valueChanged(int arg1);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_dialoggenerate_finished(int result);

private:
    Ui::dialoggenerate *ui;
};

#endif // DIALOGGENERATE_H
