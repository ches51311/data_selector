#ifndef DIALOGSOLVER_H
#define DIALOGSOLVER_H

#include <QDialog>

namespace Ui {
class dialogsolver;
}

class dialogsolver : public QDialog
{
    Q_OBJECT

public:
    explicit dialogsolver(QWidget *parent = 0);
    ~dialogsolver();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::dialogsolver *ui;
};

#endif // DIALOGSOLVER_H
