#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("picture/window.png"));
    MainWindow w;
    w.workspacefile = argv[1];
    w.load();
    w.setWindowTitle("data selector");
    w.show();
    return a.exec();
}
