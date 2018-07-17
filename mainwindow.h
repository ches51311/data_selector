#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QLinkedList>
#include <QDir>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}


class Project
{
public:
    Project() {
    }
    ~Project(){
    }
    void clear(){
        name.clear();
        prjitems.clear();
        testitems.clear();
        trainitems.clear();
        valitems.clear();
        testitemsclsname.clear();
        trainitemsclsname.clear();
        valitemsclsname.clear();
    }
    QString name;
    QStringList prjitems;
    QStringList testitems;
    QStringList trainitems;
    QStringList valitems;
    QStringList testitemsclsname;
    QStringList trainitemsclsname;
    QStringList valitemsclsname;

};

class Classes
{
public:
    Classes() {
        fl = new QStringList;
    }
    ~Classes(){
        delete fl;
    }
    QString name;
    QString xmlfolder;
    QString xmlfoldershort;
    QString imgfolder;
    QStringList clsitems;
    QStringList *fl;
};

class Templist
{
public:
    Templist(){
    }
    ~Templist(){
    }
    QString clsname;
    QStringList test;
    QStringList train;
    QStringList val;
    QStringList testcolor;
    QStringList traincolor;
    QStringList valcolor;
    QStringList testischeck;
    QStringList trainischeck;
    QStringList valischeck;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString workspacefile;
    void load();

private slots:
    void on_actionWorkSpace_triggered();

    void on_actionOpen_Project_triggered();

    void on_actionNew_Project_triggered();

    void on_actionClass_triggered();

    void on_actionGenerate_triggered();

    void on_actionCaffe_Configure_triggered();

    void on_actionSave_Project_triggered();

    void on_actionSave_As_triggered();

    void on_btnTestTrain_clicked();

    void on_btnTestVal_clicked();

    void on_btnTrainVal_clicked();

    void on_btnTrainTest_clicked();

    void on_btnValTest_clicked();

    void on_btnValTrain_clicked();

    void on_comboBoxCls_currentIndexChanged(const QString &arg1);

    void on_lsWidgetTest_currentItemChanged(QListWidgetItem *current);

    void on_lsWidgetTrain_currentItemChanged(QListWidgetItem *current);

    void on_lsWidgetVal_currentItemChanged(QListWidgetItem *current);


    void EnableOption_False();

    void EnableOption1();

    void EnableOption2();

    void EnableOption3();

    void EnableOption4();

    void OpenCls(QString file1);

    void InputCls(QString file1);

    void OpenPrj(QString file1);

    void InputPrj(QString file1);

    QStringList ReadPrj(QString file1);

    QStringList ReadPrjClsName(QString file1);

    void InitialList();

    void SetTempList(QString name);

    void SaveList(QString currentcls);

    void ShowList();

    void ShowPicture(QString fileJPEG);

    void RefreshLabelText();

    void FileClear(QString file1);

    void FileReplaceStr(QString file1, QString strold, QString strnew);

    void SetSolver();

    void SetSolverKey();

    void SAVE();

    void on_actionOpen_Training_Manager_triggered();

private:
    Ui::MainWindow *ui;
    int testvalue;
    int trainvalue;
    int valvalue;
    bool workspaceinput;
    bool isprjnew;
    QString fw;
    QString pypath;
    QString precls;
    QStringList warnings;
    QStringList warnings2;
    QStringList warnings3;
    QStringList warnings4;
    QStringList warnings5;
    QGraphicsScene *graphic;
    Project currentprj;
    QLinkedList<Templist*> templistlist;
    QLinkedList<Classes*> clslist;
    QLinkedList<Project*> prjlist;
};

#endif // MAINWINDOW_H
