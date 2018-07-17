#ifndef DIALOGNEWPRJ_H
#define DIALOGNEWPRJ_H

#include <QDialog>

namespace Ui {
class dialognewprj;
}

class dialognewprj : public QDialog
{
    Q_OBJECT

public:
    explicit dialognewprj(QWidget *parent = 0);
    ~dialognewprj();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::dialognewprj *ui;
};

#endif // DIALOGNEWPRJ_H
