#ifndef DIALOGSAVEAS_H
#define DIALOGSAVEAS_H

#include <QDialog>

namespace Ui {
class dialogsaveas;
}

class dialogsaveas : public QDialog
{
    Q_OBJECT

public:
    explicit dialogsaveas(QWidget *parent = 0);
    ~dialogsaveas();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::dialogsaveas *ui;
};

#endif // DIALOGSAVEAS_H
