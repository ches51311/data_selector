#ifndef DIALOGOPENPRJ_H
#define DIALOGOPENPRJ_H

#include <QDialog>

namespace Ui {
class dialogOpenPrj;
}

class dialogOpenPrj : public QDialog
{
    Q_OBJECT

public:
    explicit dialogOpenPrj(QWidget *parent = 0);
    ~dialogOpenPrj();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::dialogOpenPrj *ui;
};

#endif // DIALOGOPENPRJ_H
