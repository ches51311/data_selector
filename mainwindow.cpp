#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogsolver.h"
#include "dialogopenprj.h"
#include "dialognewprj.h"
#include "dialogclass.h"
#include "dialoggenerate.h"
#include "dialogsaveas.h"
#include <QDebug>
#include <QtCore>
#include <QtGui>
#include <QProcess>
#include <QFileDialog>
#include <QCoreApplication>
#include <QFile>
#include <QtDebug>
#include <QListWidgetItem>
#include <QKeyEvent>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QLinkedList>
#include <QThread>
#include <QProgressDialog>


QStringList globalprjs;
QString globalprj;
QString globalnewprj;
QStringList globalclsunselect;
QStringList globalclsselect;
QStringList globalsolver;
QStringList globalsolverkey;
QString globalsaveas;
int globaltestvalue;
int globaltrainvalue;
int globalvalvalue;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    EnableOption_False();

    ui->actionSave_As->setVisible(false);



    workspaceinput = false;
    graphic = new QGraphicsScene(this);
    warnings.clear();
    warnings2.clear();
    warnings3.clear();
    warnings4.clear();
    warnings5.clear();

    SetSolver();
    SetSolverKey();

    currentprj.clear();
    prjlist.clear();
    clslist.clear();
    ui->comboBoxCls->clear();
    ui->labelWorkSpace->clear();
    ui->labelPrjName->clear();
    ui->labelClsNum->clear();
    ui->labelTestNum->clear();
    ui->labelTrainNum->clear();
    ui->labelValNum->clear();
    ui->labelTotal->clear();
    graphic->clear();



    ui->actionWorkSpace->setIcon(QIcon("picture/workspace.png"));
    ui->actionOpen_Project->setIcon(QIcon("picture/open_project.png"));
    ui->actionNew_Project->setIcon(QIcon("picture/new_project.png"));
    ui->actionClass->setIcon(QIcon("picture/class.png"));
    ui->actionGenerate->setIcon(QIcon("picture/generate.png"));
    ui->actionCaffe_Configure->setIcon(QIcon("picture/caffe_configure.png"));
    ui->actionSave_Project->setIcon(QIcon("picture/save_project.png"));
    ui->actionSave_As->setIcon(QIcon("picture/save_as.png"));
    ui->actionOpen_Training_Manager->setIcon(QIcon("picture/training_manager.png"));

    ui->btnTestTrain->setIcon(QIcon("picture/move_to.png"));
    ui->btnTestVal->setIcon(QIcon("picture/move_to.png"));
    ui->btnTestDel->setIcon(QIcon("picture/move_to.png"));
    ui->btnTrainTest->setIcon(QIcon("picture/move_to.png"));
    ui->btnTrainVal->setIcon(QIcon("picture/move_to.png"));
    ui->btnTrainDel->setIcon(QIcon("picture/move_to.png"));
    ui->btnValTest->setIcon(QIcon("picture/move_to.png"));
    ui->btnValTrain->setIcon(QIcon("picture/move_to.png"));
    ui->btnValDel->setIcon(QIcon("picture/move_to.png"));

    ShowPicture("picture/start.jpg");
    ui->graphicsView->setEnabled(true);




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load(){
    if (workspacefile.isEmpty()){
        return;
    }
    QDir dir(workspacefile);
    if(!dir.exists()){
        return;
    }

    fw = workspacefile;
    ui->labelWorkSpace->setText(workspacefile);

    OpenPrj(fw);

    OpenCls(fw + "/Classes");

    EnableOption1();

    if (warnings.isEmpty() == false){
        QString warning = warnings.join("\n");
        warnings.clear();
        QMessageBox::about(NULL, "Remind", "Some xml file does not fit the correspond jpg file:\n" + warning);
    }

    if (warnings2.isEmpty() == false){
        QString warning2 = warnings2.join("\n");
        warnings2.clear();
        QMessageBox::about(NULL, "Remind", "Different directory have same class name, please check and revise it:\n" + warning2);
    }

    if (warnings3.isEmpty() == false){
        QString warning3 = warnings3.join("\n");
        warnings3.clear();
        QMessageBox::about(NULL, "Remind", "Following folder not exists, please check and revise prj file's directory data consistent or not :\n" + warning3);
    }

    if (warnings4.isEmpty() == false){
        QString warning4 = warnings4.join("\n");
        warnings4.clear();
        QMessageBox::about(NULL, "Remind", "Following file not exists, please check and revise it :\n" + warning4);
    }

    if (warnings5.isEmpty() == false){
        QString warning5 = warnings5.join("\n");
        warnings5.clear();
        QMessageBox::about(NULL, "Remind", "Following project reading failed :\n" + warning5);
    }

}


void MainWindow::on_actionWorkSpace_triggered()
{
    if (workspaceinput == true){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(NULL, "Question", "Input workspace Again?(It will clear all satus)", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No){return;}
    }

    EnableOption_False();

    workspaceinput = false;

    warnings.clear();
    warnings2.clear();
    warnings3.clear();
    warnings4.clear();
    warnings5.clear();
    currentprj.clear();
    prjlist.clear();
    clslist.clear();
    ui->comboBoxCls->clear();
    ui->labelWorkSpace->clear();
    ui->labelPrjName->clear();
    ui->labelClsNum->clear();
    ui->labelTestNum->clear();
    ui->labelTrainNum->clear();
    ui->labelValNum->clear();
    //graphic->clear();

    //SetSolver();
    //SetSolverKey();



    QString file1 = QFileDialog::getExistingDirectory(this);
    if (file1.isEmpty()){return;}
    fw = file1;

    OpenCls(fw + "/Classes");

    OpenPrj(fw);

    if (clslist.isEmpty()){
        QMessageBox::about(NULL, "Remind", "Is this a workspace? (do not enter too much under workspace)");
        return;
    }
    ui->labelWorkSpace->setText(file1);

    EnableOption1();

    if (warnings.isEmpty() == false){
        QString warning = warnings.join("\n");
        warnings.clear();
        QMessageBox::about(NULL, "Remind", "Some xml file not fit the correspond jpg file:\n" + warning);
    }

    if (warnings2.isEmpty() == false){
        QString warning2 = warnings2.join("\n");
        warnings2.clear();
        QMessageBox::about(NULL, "Remind", "Different directory have same class name, please check and revise it:\n" + warning2);
    }

    if (warnings3.isEmpty() == false){
        QString warning3 = warnings3.join("\n");
        warnings3.clear();
        QMessageBox::about(NULL, "Remind", "Following folder not exists, please check and revise prj file's directory data consistent or not :\n" + warning3);
    }

    if (warnings4.isEmpty() == false){
        QString warning4 = warnings4.join("\n");
        warnings4.clear();
        QMessageBox::about(NULL, "Remind", "Following file not exists, please check and revise it :\n" + warning4);
    }

    if (warnings5.isEmpty() == false){
        QString warning5 = warnings5.join("\n");
        warnings5.clear();
        QMessageBox::about(NULL, "Remind", "Following project reading failed :\n" + warning5);
    }

    workspaceinput = true;
}

void MainWindow::on_actionOpen_Project_triggered()
{
    globalprjs.clear();
    globalprj.clear();
    for (QLinkedList<Project*>::iterator prjiter = prjlist.begin(); prjiter != prjlist.end(); prjiter++){
        globalprjs.append((*prjiter)->name);
    }

    dialogOpenPrj diopen;
    diopen.setWindowTitle("Open Project");
    diopen.setModal(true);
    diopen.exec();
    if (globalprj.isEmpty()){return;}
    if (currentprj.name.isEmpty() == false){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(NULL, "Question", "Open another project(it will clear all current project)", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No){return;}
        if (reply == QMessageBox::Yes){
            EnableOption_False();
            EnableOption1();
        }
    }
    for (QLinkedList<Project*>::iterator prjiter = prjlist.begin(); prjiter != prjlist.end(); prjiter++){
        if ((*prjiter)->name == globalprj){
            currentprj.clear();
            currentprj.name = (*prjiter)->name;
            currentprj.prjitems = (*prjiter)->prjitems;
            //currentprj.testitems = (*prjiter)->testitems;
            //currentprj.trainitems = (*prjiter)->trainitems;
            //currentprj.valitems = (*prjiter)->valitems;
            //currentprj.testitemsclsname = (*prjiter)->testitemsclsname;
            //currentprj.trainitemsclsname = (*prjiter)->trainitemsclsname;
            //currentprj.valitemsclsname = (*prjiter)->valitemsclsname;
        }
    }
    ui->labelPrjName->setText("project : " + currentprj.name);
    EnableOption2();
    ui->actionSave_As->setVisible(true);
    isprjnew = false;
}

void MainWindow::on_actionNew_Project_triggered()
{
    globalnewprj.clear();

    if (currentprj.name.isEmpty() == false){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(NULL, "Question", "Open a New project?(it will clear all current project)", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No){return;}
        if (reply == QMessageBox::Yes){
            EnableOption_False();
            EnableOption1();
        }
    }

    dialognewprj dinew;
    dinew.setWindowTitle("New Project");
    dinew.setModal(true);
    dinew.exec();
    if (globalnewprj.isEmpty()){return;}
    for (QLinkedList<Project*>::iterator prjiter = prjlist.begin(); prjiter != prjlist.end(); prjiter++){
        if ((*prjiter)->name == globalnewprj){
            QMessageBox::about(NULL, "Remind", "Project name exists, please take another name");
            return;
        }
    }
    currentprj.clear();
    currentprj.name = globalnewprj;
    ui->labelPrjName->setText("project : " + currentprj.name);
    EnableOption2();
    ui->actionSave_As->setVisible(false);
    isprjnew = true;
}

void MainWindow::on_actionClass_triggered()
{
    globalclsunselect.clear();
    globalclsselect.clear();

    int count;
    if (currentprj.prjitems.isEmpty()){
        count = 0;
    }
    else{
        count = currentprj.prjitems.count();
    }
    bool prjselect;

    for (QLinkedList<Classes*>::iterator clsiter = clslist.begin(); clsiter != clslist.end(); clsiter++){
        prjselect = false;
        for (int i=0; i<count; i++){
            if (currentprj.prjitems.at(i) == (*clsiter)->name){prjselect = true;}
        }
        if (prjselect == true){globalclsselect.append((*clsiter)->name);}
        else{globalclsunselect.append((*clsiter)->name);}
    }

    dialogclass dicls;
    dicls.setWindowTitle("Select Classes");
    dicls.setModal(true);
    dicls.exec();
    bool check;

    QStringList itemchange;
    itemchange.clear();
    for (int i=0; i<currentprj.prjitems.count(); i++){
        check = false;
        for (int j=0; j<globalclsselect.count(); j++){
            if (currentprj.prjitems.at(i) == globalclsselect.at(j)){
                check = true;
            }
        }
        if (check == false){
            itemchange.append(currentprj.prjitems.at(i));
        }
    }

    for (int i=0; i<itemchange.count(); i++){
        currentprj.prjitems.removeOne(itemchange.at(i));
    }

    for (int i=0; i<globalclsselect.count(); i++){
        check = false;
        for (int j=0; j<currentprj.prjitems.count(); j++){
            if (globalclsselect.at(i) == currentprj.prjitems.at(j)){
                check = true;
            }
        }
        if (check == false){
            currentprj.prjitems.append(globalclsselect.at(i));
        }
    }


    QStringList currenttestitems;
    QStringList currenttestitemsclsname;
    QStringList currenttrainitems;
    QStringList currenttrainitemsclsname;
    QStringList currentvalitems;
    QStringList currentvalitemsclsname;

    check = false;
    for (QLinkedList<Project*>::iterator prjiter = prjlist.begin(); prjiter != prjlist.end(); prjiter++){
        if ((*prjiter)->name == currentprj.name){
            for (int i=0; i<currentprj.prjitems.count(); i++){
                for (int j=0; j<(*prjiter)->prjitems.count(); j++){
                    if (currentprj.prjitems.at(i) == (*prjiter)->prjitems.at(j)){
                        check = true;
                        for (int k=0; k<(*prjiter)->testitems.count(); k++){
                            if (currentprj.prjitems.at(i) == (*prjiter)->testitemsclsname.at(k)){
                                currenttestitems.append((*prjiter)->testitems.at(k));
                                currenttestitemsclsname.append((*prjiter)->testitemsclsname.at(k));
                            }
                        }
                        for (int k=0; k<(*prjiter)->trainitems.count(); k++){
                            if (currentprj.prjitems.at(i) == (*prjiter)->trainitemsclsname.at(k)){
                                currenttrainitems.append((*prjiter)->trainitems.at(k));
                                currenttrainitemsclsname.append((*prjiter)->trainitemsclsname.at(k));
                            }
                        }
                        for (int k=0; k<(*prjiter)->valitems.count(); k++){
                            if (currentprj.prjitems.at(i) == (*prjiter)->valitemsclsname.at(k)){
                                currentvalitems.append((*prjiter)->valitems.at(k));
                                currentvalitemsclsname.append((*prjiter)->valitemsclsname.at(k));
                            }
                        }
                    }
                }
            }
        }
    }

    if (check == true){
        currentprj.testitems = currenttestitems;
        currentprj.testitemsclsname = currenttestitemsclsname;
        currentprj.trainitems = currenttrainitems;
        currentprj.trainitemsclsname = currenttrainitemsclsname;
        currentprj.valitems = currentvalitems;
        currentprj.valitemsclsname = currentvalitemsclsname;
    }

    QString clsnum = QString::number(globalclsselect.count());
    ui->labelClsNum->setText("class number : " + clsnum);
    EnableOption3();
    if (globalclsselect.count()==0) {ui->actionGenerate->setEnabled(false);}


}

void MainWindow::on_actionGenerate_triggered()
{
    if (ui->lsWidgetTest->count() + ui->lsWidgetTrain->count() + ui->lsWidgetVal->count() > 0){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(NULL, "Question", "Generate again?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No){return;}
    }


    int test = currentprj.testitems.count();
    int train = currentprj.trainitems.count();
    int val = currentprj.valitems.count();
    if (test+train+val>0){
        globaltestvalue = test*100/(test+train+val);
        globaltrainvalue = train*100/(test+train+val);
        globalvalvalue = 100-globaltestvalue-globaltrainvalue;
    }
    else{
        globaltestvalue = 50;
        globaltrainvalue = 25;
        globalvalvalue = 25;
    }

    dialoggenerate digen;
    digen.setWindowTitle("Select Classes");
    digen.setModal(true);
    digen.exec();

    if (globaltestvalue == -1){return;}
    if (globaltrainvalue+globaltestvalue+globalvalvalue != 100){
        QMessageBox::about(NULL, "Remind", "Sum of each Item Percentage must be 100");
        return;
    }

    InitialList();

    ShowList();

    RefreshLabelText();

    QString fj;
    for (QLinkedList<Classes*>::iterator clsiter = clslist.begin(); clsiter != clslist.end(); clsiter++){
        if ((*clsiter)->name == ui->comboBoxCls->currentText()){
            fj = (*clsiter)->imgfolder;
        }
    }
    QString pic;
    if (ui->lsWidgetTest->count()>0){
        pic = ui->lsWidgetTest->item(0)->text().simplified();
    }
    QString fileJPEG = fj+"/"+pic+".jpg";

    ShowPicture(fileJPEG);


    EnableOption4();

}

void MainWindow::on_actionCaffe_Configure_triggered()
{
    dialogsolver di;
    di.setWindowTitle("caffe configure");
    di.setModal(true);
    di.exec();
}

void MainWindow::on_actionSave_Project_triggered()
{

    QMessageBox::StandardButton reply0;
    reply0 = QMessageBox::question(NULL, "Question", "Save the project?", QMessageBox::Yes | QMessageBox::No);
    if (reply0 == QMessageBox::No){return;}

    SAVE();

}

void MainWindow::on_actionSave_As_triggered()
{
    globalsaveas = currentprj.name;
    dialogsaveas disaveas;
    disaveas.setWindowTitle("Save As");
    disaveas.setModal(true);
    disaveas.exec();
    bool isexist = false;
    for (QLinkedList<Project*>::iterator prjiter = prjlist.begin(); prjiter != prjlist.end(); prjiter++){
        if ((*prjiter)->name == globalsaveas){
            isexist = true;
        }
    }

    if (isexist == true){
        QMessageBox::about(NULL, "Remind", "The file name is already used, please take another name");
        return;
    }
    QMessageBox::StandardButton reply0;
    reply0 = QMessageBox::question(NULL, "Question", "Save the project?", QMessageBox::Yes | QMessageBox::No);
    if (reply0 == QMessageBox::No){return;}
    currentprj.name = globalsaveas;
    SAVE();

}

void MainWindow::on_btnTestTrain_clicked()
{

    SaveList(ui->comboBoxCls->currentText());

    QStringList temptest;
    QStringList temptestcolor;
    QStringList temptestischeck;
    QStringList temptrain;
    QStringList temptraincolor;
    QStringList temptrainischeck;

    for (QLinkedList<Templist*>::iterator tempiter = templistlist.begin(); tempiter != templistlist.end(); tempiter++){
        if ((*tempiter)->clsname == ui->comboBoxCls->currentText()){
            temptrain = (*tempiter)->train;
            temptraincolor = (*tempiter)->traincolor;
            temptrainischeck = (*tempiter)->trainischeck;
            for (int i=0; i<(*tempiter)->test.count(); i++){
                if ((*tempiter)->testischeck.at(i) == "yes"){
                    temptrain.append((*tempiter)->test.at(i));
                    temptrainischeck.append("no");
                    if ((*tempiter)->testcolor.at(i) == "green"){
                        temptraincolor.append("blue_test");
                    }
                    if ((*tempiter)->testcolor.at(i) == "blue_train"){
                        temptraincolor.append("green");
                    }
                    if ((*tempiter)->testcolor.at(i) == "blue_val"){
                        temptraincolor.append("blue_val");
                    }
                    if ((*tempiter)->testcolor.at(i) == "red"){
                        temptraincolor.append("red");
                    }
                    if ((*tempiter)->testcolor.at(i) == "nocolor"){
                        temptraincolor.append("nocolor");
                    }
                }
                else{
                    temptest.append((*tempiter)->test.at(i));
                    temptestcolor.append((*tempiter)->testcolor.at(i));
                    temptestischeck.append("no");
                }

            }

            (*tempiter)->test = temptest;
            (*tempiter)->testcolor = temptestcolor;
            (*tempiter)->testischeck = temptestischeck;
            (*tempiter)->train = temptrain;
            (*tempiter)->traincolor = temptraincolor;
            (*tempiter)->trainischeck = temptrainischeck;
        }

    }

    ShowList();

    RefreshLabelText();
}

void MainWindow::on_btnTestVal_clicked()
{

    SaveList(ui->comboBoxCls->currentText());

    QStringList temptest;
    QStringList temptestcolor;
    QStringList temptestischeck;
    QStringList tempval;
    QStringList tempvalcolor;
    QStringList tempvalischeck;

    for (QLinkedList<Templist*>::iterator tempiter = templistlist.begin(); tempiter != templistlist.end(); tempiter++){
        if ((*tempiter)->clsname == ui->comboBoxCls->currentText()){
            tempval = (*tempiter)->val;
            tempvalcolor = (*tempiter)->valcolor;
            tempvalischeck = (*tempiter)->valischeck;
            for (int i=0; i<(*tempiter)->test.count(); i++){
                if ((*tempiter)->testischeck.at(i) == "yes"){
                    tempval.append((*tempiter)->test.at(i));
                    tempvalischeck.append("no");
                    if ((*tempiter)->testcolor.at(i) == "green"){
                        tempvalcolor.append("blue_test");
                    }
                    if ((*tempiter)->testcolor.at(i) == "blue_val"){
                        tempvalcolor.append("green");
                    }
                    if ((*tempiter)->testcolor.at(i) == "blue_train"){
                        tempvalcolor.append("blue_train");
                    }
                    if ((*tempiter)->testcolor.at(i) == "red"){
                        tempvalcolor.append("red");
                    }
                    if ((*tempiter)->testcolor.at(i) == "nocolor"){
                        tempvalcolor.append("nocolor");
                    }
                }
                else{
                    temptest.append((*tempiter)->test.at(i));
                    temptestcolor.append((*tempiter)->testcolor.at(i));
                    temptestischeck.append("no");
                }

            }

            (*tempiter)->test = temptest;
            (*tempiter)->testcolor = temptestcolor;
            (*tempiter)->testischeck = temptestischeck;
            (*tempiter)->val = tempval;
            (*tempiter)->valcolor = tempvalcolor;
            (*tempiter)->valischeck = tempvalischeck;
        }

    }

    ShowList();

    RefreshLabelText();

}

void MainWindow::on_btnTestDel_clicked()
{
    SaveList(ui->comboBoxCls->currentText());

    QStringList temptest;
    QStringList temptestcolor;
    QStringList temptestischeck;
    QStringList tempdel;
    QStringList tempdelischeck;

    for (QLinkedList<Templist*>::iterator tempiter = templistlist.begin(); tempiter != templistlist.end(); tempiter++){
        if ((*tempiter)->clsname == ui->comboBoxCls->currentText()){
            tempdel = (*tempiter)->del;
            tempdelischeck = (*tempiter)->delischeck;
            for (int i=0; i<(*tempiter)->test.count(); i++){
                if ((*tempiter)->testischeck.at(i) == "yes"){
                    tempdel.append((*tempiter)->test.at(i));
                    tempdelischeck.append("no");
                }
                else{
                    temptest.append((*tempiter)->test.at(i));
                    temptestcolor.append((*tempiter)->testcolor.at(i));
                    temptestischeck.append("no");
                }

            }

            (*tempiter)->test = temptest;
            (*tempiter)->testcolor = temptestcolor;
            (*tempiter)->testischeck = temptestischeck;
            (*tempiter)->del = tempdel;
            (*tempiter)->delischeck = tempdelischeck;
        }

    }

    ShowList();

    RefreshLabelText();



}

void MainWindow::on_btnTrainVal_clicked()
{

    SaveList(ui->comboBoxCls->currentText());

    QStringList temptrain;
    QStringList temptraincolor;
    QStringList temptrainischeck;
    QStringList tempval;
    QStringList tempvalcolor;
    QStringList tempvalischeck;

    for (QLinkedList<Templist*>::iterator tempiter = templistlist.begin(); tempiter != templistlist.end(); tempiter++){
        if ((*tempiter)->clsname == ui->comboBoxCls->currentText()){
            tempval = (*tempiter)->val;
            tempvalcolor = (*tempiter)->valcolor;
            tempvalischeck = (*tempiter)->valischeck;
            for (int i=0; i<(*tempiter)->train.count(); i++){
                if ((*tempiter)->trainischeck.at(i) == "yes"){
                    tempval.append((*tempiter)->train.at(i));
                    tempvalischeck.append("no");
                    if ((*tempiter)->traincolor.at(i) == "green"){
                        tempvalcolor.append("blue_train");
                    }
                    if ((*tempiter)->traincolor.at(i) == "blue_val"){
                        tempvalcolor.append("green");
                    }
                    if ((*tempiter)->traincolor.at(i) == "blue_test"){
                        tempvalcolor.append("blue_test");
                    }
                    if ((*tempiter)->traincolor.at(i) == "red"){
                        tempvalcolor.append("red");
                    }
                    if ((*tempiter)->traincolor.at(i) == "nocolor"){
                        tempvalcolor.append("nocolor");
                    }
                }
                else{
                    temptrain.append((*tempiter)->train.at(i));
                    temptraincolor.append((*tempiter)->traincolor.at(i));
                    temptrainischeck.append("no");
                }

            }

            (*tempiter)->train = temptrain;
            (*tempiter)->traincolor = temptraincolor;
            (*tempiter)->trainischeck = temptrainischeck;
            (*tempiter)->val = tempval;
            (*tempiter)->valcolor = tempvalcolor;
            (*tempiter)->valischeck = tempvalischeck;
        }

    }

    ShowList();

    RefreshLabelText();
}

void MainWindow::on_btnTrainTest_clicked()
{

    SaveList(ui->comboBoxCls->currentText());

    QStringList temptrain;
    QStringList temptraincolor;
    QStringList temptrainischeck;
    QStringList temptest;
    QStringList temptestcolor;
    QStringList temptestischeck;

    for (QLinkedList<Templist*>::iterator tempiter = templistlist.begin(); tempiter != templistlist.end(); tempiter++){
        if ((*tempiter)->clsname == ui->comboBoxCls->currentText()){
            temptest = (*tempiter)->test;
            temptestcolor = (*tempiter)->testcolor;
            temptestischeck = (*tempiter)->testischeck;
            for (int i=0; i<(*tempiter)->train.count(); i++){
                if ((*tempiter)->trainischeck.at(i) == "yes"){
                    temptest.append((*tempiter)->train.at(i));
                    temptestischeck.append("no");
                    if ((*tempiter)->traincolor.at(i) == "green"){
                        temptestcolor.append("blue_train");
                    }
                    if ((*tempiter)->traincolor.at(i) == "blue_test"){
                        temptestcolor.append("green");
                    }
                    if ((*tempiter)->traincolor.at(i) == "blue_val"){
                        temptestcolor.append("blue_val");
                    }
                    if ((*tempiter)->traincolor.at(i) == "red"){
                        temptestcolor.append("red");
                    }
                    if ((*tempiter)->traincolor.at(i) == "nocolor"){
                        temptestcolor.append("nocolor");
                    }
                }
                else{
                    temptrain.append((*tempiter)->train.at(i));
                    temptraincolor.append((*tempiter)->traincolor.at(i));
                    temptrainischeck.append("no");
                }

            }

            (*tempiter)->train = temptrain;
            (*tempiter)->traincolor = temptraincolor;
            (*tempiter)->trainischeck = temptrainischeck;
            (*tempiter)->test = temptest;
            (*tempiter)->testcolor = temptestcolor;
            (*tempiter)->testischeck = temptestischeck;
        }

    }

    ShowList();

    RefreshLabelText();

}

void MainWindow::on_btnTrainDel_clicked()
{
    SaveList(ui->comboBoxCls->currentText());

    QStringList temptrain;
    QStringList temptraincolor;
    QStringList temptrainischeck;
    QStringList tempdel;
    QStringList tempdelischeck;

    for (QLinkedList<Templist*>::iterator tempiter = templistlist.begin(); tempiter != templistlist.end(); tempiter++){
        if ((*tempiter)->clsname == ui->comboBoxCls->currentText()){
            tempdel = (*tempiter)->del;
            tempdelischeck = (*tempiter)->delischeck;
            for (int i=0; i<(*tempiter)->train.count(); i++){
                if ((*tempiter)->trainischeck.at(i) == "yes"){
                    tempdel.append((*tempiter)->train.at(i));
                    tempdelischeck.append("no");
                }
                else{
                    temptrain.append((*tempiter)->train.at(i));
                    temptraincolor.append((*tempiter)->traincolor.at(i));
                    temptrainischeck.append("no");
                }

            }

            (*tempiter)->train = temptrain;
            (*tempiter)->traincolor = temptraincolor;
            (*tempiter)->trainischeck = temptrainischeck;
            (*tempiter)->del = tempdel;
            (*tempiter)->delischeck = tempdelischeck;
        }

    }

    ShowList();

    RefreshLabelText();


}

void MainWindow::on_btnValTest_clicked()
{
    SaveList(ui->comboBoxCls->currentText());

    QStringList tempval;
    QStringList tempvalcolor;
    QStringList tempvalischeck;
    QStringList temptest;
    QStringList temptestcolor;
    QStringList temptestischeck;

    for (QLinkedList<Templist*>::iterator tempiter = templistlist.begin(); tempiter != templistlist.end(); tempiter++){
        if ((*tempiter)->clsname == ui->comboBoxCls->currentText()){
            temptest = (*tempiter)->test;
            temptestcolor = (*tempiter)->testcolor;
            temptestischeck = (*tempiter)->testischeck;
            for (int i=0; i<(*tempiter)->val.count(); i++){
                if ((*tempiter)->valischeck.at(i) == "yes"){
                    temptest.append((*tempiter)->val.at(i));
                    temptestischeck.append("no");
                    if ((*tempiter)->valcolor.at(i) == "green"){
                        temptestcolor.append("blue_val");
                    }
                    if ((*tempiter)->valcolor.at(i) == "blue_test"){
                        temptestcolor.append("green");
                    }
                    if ((*tempiter)->valcolor.at(i) == "blue_train"){
                        temptestcolor.append("blue_train");
                    }
                    if ((*tempiter)->valcolor.at(i) == "red"){
                        temptestcolor.append("red");
                    }
                    if ((*tempiter)->valcolor.at(i) == "nocolor"){
                        temptestcolor.append("nocolor");
                    }
                }
                else{
                    tempval.append((*tempiter)->val.at(i));
                    tempvalcolor.append((*tempiter)->valcolor.at(i));
                    tempvalischeck.append("no");
                }

            }

            (*tempiter)->val = tempval;
            (*tempiter)->valcolor = tempvalcolor;
            (*tempiter)->valischeck = tempvalischeck;
            (*tempiter)->test = temptest;
            (*tempiter)->testcolor = temptestcolor;
            (*tempiter)->testischeck = temptestischeck;
        }

    }

    ShowList();

    RefreshLabelText();

}

void MainWindow::on_btnValTrain_clicked()
{

    SaveList(ui->comboBoxCls->currentText());

    QStringList tempval;
    QStringList tempvalcolor;
    QStringList tempvalischeck;
    QStringList temptrain;
    QStringList temptraincolor;
    QStringList temptrainischeck;

    for (QLinkedList<Templist*>::iterator tempiter = templistlist.begin(); tempiter != templistlist.end(); tempiter++){
        if ((*tempiter)->clsname == ui->comboBoxCls->currentText()){
            temptrain = (*tempiter)->train;
            temptraincolor = (*tempiter)->traincolor;
            temptrainischeck = (*tempiter)->trainischeck;
            for (int i=0; i<(*tempiter)->val.count(); i++){
                if ((*tempiter)->valischeck.at(i) == "yes"){
                    temptrain.append((*tempiter)->val.at(i));
                    temptrainischeck.append("no");
                    if ((*tempiter)->valcolor.at(i) == "green"){
                        temptraincolor.append("blue_val");
                    }
                    if ((*tempiter)->valcolor.at(i) == "blue_train"){
                        temptraincolor.append("green");
                    }
                    if ((*tempiter)->valcolor.at(i) == "blue_test"){
                        temptraincolor.append("blue_test");
                    }
                    if ((*tempiter)->valcolor.at(i) == "red"){
                        temptraincolor.append("red");
                    }
                    if ((*tempiter)->valcolor.at(i) == "nocolor"){
                        temptraincolor.append("nocolor");
                    }
                }
                else{
                    tempval.append((*tempiter)->val.at(i));
                    tempvalcolor.append((*tempiter)->valcolor.at(i));
                    tempvalischeck.append("no");
                }

            }

            (*tempiter)->val = tempval;
            (*tempiter)->valcolor = tempvalcolor;
            (*tempiter)->valischeck = tempvalischeck;
            (*tempiter)->train = temptrain;
            (*tempiter)->traincolor = temptraincolor;
            (*tempiter)->trainischeck = temptrainischeck;
        }

    }

    ShowList();

    RefreshLabelText();

}

void MainWindow::on_btnValDel_clicked()
{
    SaveList(ui->comboBoxCls->currentText());

    QStringList tempval;
    QStringList tempvalcolor;
    QStringList tempvalischeck;
    QStringList tempdel;
    QStringList tempdelischeck;

    for (QLinkedList<Templist*>::iterator tempiter = templistlist.begin(); tempiter != templistlist.end(); tempiter++){
        if ((*tempiter)->clsname == ui->comboBoxCls->currentText()){
            tempdel = (*tempiter)->del;
            tempdelischeck = (*tempiter)->delischeck;
            for (int i=0; i<(*tempiter)->val.count(); i++){
                if ((*tempiter)->valischeck.at(i) == "yes"){
                    tempdel.append((*tempiter)->val.at(i));
                    tempdelischeck.append("no");
                }
                else{
                    tempval.append((*tempiter)->val.at(i));
                    tempvalcolor.append((*tempiter)->valcolor.at(i));
                    tempvalischeck.append("no");
                }

            }

            (*tempiter)->val = tempval;
            (*tempiter)->valcolor = tempvalcolor;
            (*tempiter)->valischeck = tempvalischeck;
            (*tempiter)->del = tempdel;
            (*tempiter)->delischeck = tempdelischeck;
        }

    }

    ShowList();

    RefreshLabelText();


}

void MainWindow::on_comboBoxCls_currentIndexChanged(const QString &arg1)
{

    SaveList(precls);

    precls = arg1;

    ShowList();

    RefreshLabelText();

    QString fj;
    for (QLinkedList<Classes*>::iterator clsiter = clslist.begin(); clsiter != clslist.end(); clsiter++){
        if ((*clsiter)->name == ui->comboBoxCls->currentText()){
            fj = (*clsiter)->imgfolder;
        }
    }
    QString pic;
    if (ui->lsWidgetTest->count()>0){
        pic = ui->lsWidgetTest->item(0)->text().simplified();
    }
    QString fileJPEG = fj+"/"+pic+".jpg";
    ShowPicture(fileJPEG);

}

void MainWindow::on_lsWidgetTest_currentItemChanged(QListWidgetItem *current)
{
    if(current==NULL){return;}
    QString fj;
    for (QLinkedList<Classes*>::iterator clsiter = clslist.begin(); clsiter != clslist.end(); clsiter++){
        if ((*clsiter)->name == ui->comboBoxCls->currentText()){
            fj = (*clsiter)->imgfolder;
        }
    }
    QString pic;
    if (ui->lsWidgetTest->count()>0){
        pic = current->text().simplified();
    }
    QString fileJPEG = fj+"/"+pic+".jpg";
    ShowPicture(fileJPEG);
}

void MainWindow::on_lsWidgetTrain_currentItemChanged(QListWidgetItem *current)
{
    if(current==NULL){return;}
    QString fj;
    for (QLinkedList<Classes*>::iterator clsiter = clslist.begin(); clsiter != clslist.end(); clsiter++){
        if ((*clsiter)->name == ui->comboBoxCls->currentText()){
            fj = (*clsiter)->imgfolder;
        }
    }
    QString pic;
    if (ui->lsWidgetTest->count()>0){
        pic = current->text().simplified();
    }
    QString fileJPEG = fj+"/"+pic+".jpg";
    ShowPicture(fileJPEG);
}

void MainWindow::on_lsWidgetVal_currentItemChanged(QListWidgetItem *current)
{
    if(current==NULL){return;}
    QString fj;
    for (QLinkedList<Classes*>::iterator clsiter = clslist.begin(); clsiter != clslist.end(); clsiter++){
        if ((*clsiter)->name == ui->comboBoxCls->currentText()){
            fj = (*clsiter)->imgfolder;
        }
    }
    QString pic;
    if (ui->lsWidgetTest->count()>0){
        pic = current->text().simplified();
    }
    QString fileJPEG = fj+"/"+pic+".jpg";
    ShowPicture(fileJPEG);
}


//Disable Qt object
void MainWindow::EnableOption_False(){
    ui->actionOpen_Project->setEnabled(false);
    ui->actionNew_Project->setEnabled(false);
    ui->actionClass->setEnabled(false);
    ui->actionGenerate->setEnabled(false);
    ui->actionCaffe_Configure->setEnabled(false);
    ui->actionSave_Project->setEnabled(false);
    ui->actionSave_As->setEnabled(false);
    ui->actionOpen_Training_Manager->setEnabled(false);

    ui->comboBoxCls->setEnabled(false);
    ui->tabWidget->setEnabled(false);
    ui->graphicsView->setEnabled(false);

}

//Enable Qt object
void MainWindow::EnableOption1(){
    ui->actionOpen_Project->setEnabled(true);
    ui->actionNew_Project->setEnabled(true);

}

//Enable Qt object
void MainWindow::EnableOption2(){

    ui->actionClass->setEnabled(true);

}

//Enable Qt object
void MainWindow::EnableOption3(){

    ui->actionGenerate->setEnabled(true);

}

//Enable Qt object
void MainWindow::EnableOption4(){
    ui->comboBoxCls->setEnabled(true);
    ui->tabWidget->setEnabled(true);
    ui->graphicsView->setEnabled(true);
    ui->actionCaffe_Configure->setEnabled(true);
    ui->actionSave_Project->setEnabled(true);
    ui->actionSave_As->setEnabled(true);
}

//Search and open ".cls" file
void MainWindow::OpenCls(QString file1){

    QDir dir(file1);
    QStringList items;
    QString item1;

    dir.setFilter(QDir::Files);
    items = dir.entryList();
    for (int i=0; i<items.count(); i++){
        item1 = file1 + "/" + items.at(i);
        if (item1.endsWith(".cls")){
            InputCls(item1);
        }
    }

    dir.setFilter(QDir::AllDirs|QDir::NoDotAndDotDot);
    items = dir.entryList();
    for (int i=0; i<items.count(); i++){
        item1 = file1 +"/"+ items.at(i);
        OpenCls(item1);
    }

}

//Read ".cls" file and input object
void MainWindow::InputCls(QString file1){
    QFile file2(file1);
    QDir dir(file1);
    dir.cdUp();
    file2.open(QIODevice::ReadOnly);
    QByteArray b=file2.readAll();
    QJsonDocument doc=QJsonDocument::fromJson(b);
    QJsonObject doc2 = doc.object();
    QString fileup = dir.absolutePath();
    QString filecurrent = dir.dirName();

    Classes *cls = new Classes;
    QStringList *fl = new QStringList;
    QStringList clsitems;
    QString clsname = doc2.value("predefineClass").toString();
    QJsonArray jlabel = doc2.value("classification").toArray();

    QStringList label;
    for (int i=0; i<jlabel.count(); i++){
        label.append(jlabel.at(i).toString());
    }
    cls->label = label;

    cls->name = clsname;
    cls->xmlfolder = fileup +"/"+ doc2.value("anno_dir_path").toString();
    cls->xmlfoldershort = filecurrent+"/"+ doc2.value("anno_dir_path").toString();
    cls->imgfolder = fileup +"/"+ doc2.value("img_dir_path").toString();

    bool direxist = true;
    QDir dircheck1(cls->xmlfolder);
    if (dircheck1.exists() == false){
        warnings3.append(cls->xmlfolder);
        direxist = false;
    }
    QDir dircheck2(cls->imgfolder);
    if (dircheck2.exists() == false){
        warnings3.append(cls->imgfolder);
        direxist = false;
    }
    if (direxist == false){return;}

    QDir dirxml(cls->xmlfolder);
    dirxml.setFilter(QDir::Files);
    QStringList folderxmls = dirxml.entryList();
    QString folderxml;


    QDir dirjpg(cls->imgfolder);
    dirjpg.setFilter(QDir::Files);
    QStringList folderjpgs = dirjpg.entryList();
    QString folderjpg;

    for (int i=0; i<folderjpgs.count(); i++){
        folderjpg = folderjpgs.at(i);
        if (folderjpg.endsWith(".jpg") == true){
            folderjpg.remove(".jpg");
            folderjpgs.replace(i,folderjpg);
        }
        else{
            //folderjpgs.removeAt(i);
        }
    }


    for (int i=0; i<folderxmls.count(); i++){
        folderxml = folderxmls.at(i);
        if (folderxml.endsWith(".xml")){
            folderxml.remove(".xml");
            if (folderjpgs.indexOf(folderxml)==-1){
                warnings.append("\n" + folderxml + " at directory\n" + fileup);
                continue;}
            clsitems.append(folderxml);
            fl->append("noselect");
        }
    }


    cls->clsitems = clsitems;
    cls->fl = fl;

    bool rep = false;

    for (QLinkedList<Classes*>::iterator clsiter = clslist.begin(); clsiter != clslist.end(); clsiter++){
        if ((*clsiter)->name == clsname){
            rep =true;
        }
    }

    if (rep == false){
        clslist << cls;
    }

    file2.close();

}

//search and open ".prj" file
void MainWindow::OpenPrj(QString file1){

    QDir dir(file1);
    QStringList items;
    QString item1;

    dir.setFilter(QDir::Files);
    items = dir.entryList();
    for (int i=0; i<items.count(); i++){
        item1 = file1 + "/" + items.at(i);
        if (item1.endsWith(".prj")){
            InputPrj(item1);
        }
    }

    dir.setFilter(QDir::AllDirs|QDir::NoDotAndDotDot);
    items = dir.entryList();
    for (int i=0; i<items.count(); i++){
        item1 = file1 +"/"+ items.at(i);
        OpenPrj(item1);
    }
}

//Read ".prj" file and input project
void MainWindow::InputPrj(QString file1){
    QFile file2(file1);
    file2.open(QIODevice::ReadOnly);
    QByteArray b=file2.readAll();
    QJsonDocument doc=QJsonDocument::fromJson(b);
    QJsonObject doc2 = doc.object();

    Project *prj = new Project;
    QStringList prjitems;
    QString prjname = doc2.value("project_name").toString();
    QJsonArray prjitem = doc2.value("class").toArray();

    prj->name = prjname;


    for (int i=0; i<prjitem.count(); i++){
        prjitems.append(prjitem.at(i).toString());
    }

    prj->prjitems = prjitems;


    QString pathtest;
    pathtest = file1.remove(".prj") + "/test.txt";
    prj->testitems = ReadPrj(pathtest);
    prj->testitemsclsname = ReadPrjClsName(pathtest);

    QString pathtrain;
    pathtrain = file1.remove(".prj") + "/train.txt";
    prj->trainitems = ReadPrj(pathtrain);
    prj->trainitemsclsname = ReadPrjClsName(pathtrain);

    QString pathval;
    pathval = file1.remove(".prj") + "/val.txt";
    prj->valitems = ReadPrj(pathval);
    prj->valitemsclsname = ReadPrjClsName(pathval);

    bool warn = false;

    for (QLinkedList<Project*>::iterator prjiter = prjlist.begin(); prjiter != prjlist.end(); prjiter++){
        if ((*prjiter)->name == prjname){
            warn =true;
        }
    }

    if (prj->testitems.isEmpty() || prj->trainitems.isEmpty() || prj->valitems.isEmpty()){
        warnings5.append(prj->name);
        warn = true;
    }

    if (warn == false){
        prjlist << prj;
    }



    file2.close();





}

//Read project respectively
QStringList MainWindow::ReadPrj(QString file1){
    QFile file2(file1);
    file2.open(QIODevice::ReadOnly);
    QStringList readitems;

    if (file2.exists() == false){
        warnings4.append(file1);
        return readitems;
    }

    QTextStream fdata(&file2);
    QStringList fonts;
    QString line;
    QString item;


    while (!fdata.atEnd()){
        line = fdata.readLine();
        line.remove('\n');
        fonts = line.split("/");
        item = fonts.last();
        item.remove(".xml");
        readitems.append(item);

    }
    file2.close();
    return readitems;
}

//Read class name of project
QStringList MainWindow::ReadPrjClsName(QString file1){
    QFile file2(file1);
    file2.open(QIODevice::ReadOnly);
    QStringList readitems;

    if (file2.exists() == false){
        warnings4.append(file1);
        return readitems;
    }

    QTextStream fdata(&file2);
    QStringList fonts;
    QString line;
    QString item;


    while (!fdata.atEnd()){
        line = fdata.readLine();
        line.remove('\n');
        fonts = line.split("/");
        item = fonts.first();
        readitems.append(item);
    }
    file2.close();
    return readitems;

}

//Set templist a little
void MainWindow::SetTempList(QString name){
    Templist *templist = new Templist;
    templist->clsname = name;
    templistlist << templist;
}

//Initial the List !!
void MainWindow::InitialList(){

    ui->comboBoxCls->clear();
    templistlist.clear();
    for (int i=0; i<currentprj.prjitems.count(); i++){
        ui->comboBoxCls->addItem(currentprj.prjitems.at(i));
        SetTempList(currentprj.prjitems.at(i));
    }

//these three append the currentproject's information!!
    for (int i=0; i<currentprj.testitems.count(); i++){
        for (QLinkedList<Templist*>::iterator tempiter = templistlist.begin(); tempiter != templistlist.end(); tempiter++){
            if ((*tempiter)->clsname == currentprj.testitemsclsname.at(i)){
                (*tempiter)->test.append(currentprj.testitems.at(i));
                (*tempiter)->testcolor.append("red");//uncheck
            }
        }
    }




    for (int i=0; i<currentprj.trainitems.count(); i++){
        for (QLinkedList<Templist*>::iterator tempiter = templistlist.begin(); tempiter != templistlist.end(); tempiter++){
            if ((*tempiter)->clsname == currentprj.trainitemsclsname.at(i)){
                (*tempiter)->train.append(currentprj.trainitems.at(i));
                (*tempiter)->traincolor.append("red");
            }
        }
    }


    for (int i=0; i<currentprj.valitems.count(); i++){
        for (QLinkedList<Templist*>::iterator tempiter = templistlist.begin(); tempiter != templistlist.end(); tempiter++){
            if ((*tempiter)->clsname == currentprj.valitemsclsname.at(i)){
                (*tempiter)->val.append(currentprj.valitems.at(i));
                (*tempiter)->valcolor.append("red");
            }
        }
    }


//these check and append something lose class!!
    QStringList clsitemsnow;
    QStringList templisttest;
    QStringList templisttestcolor;
    QStringList templisttrain;
    QStringList templisttraincolor;
    QStringList templistval;
    QStringList templistvalcolor;


    bool check;
    for (int i=0; i<currentprj.prjitems.count(); i++){
        for (QLinkedList<Classes*>::iterator clsiter = clslist.begin(); clsiter != clslist.end(); clsiter++){
            if ((*clsiter)->name == currentprj.prjitems.at(i)){clsitemsnow = (*clsiter)->clsitems;}
        }
        for (QLinkedList<Templist*>::iterator tempiter = templistlist.begin(); tempiter != templistlist.end(); tempiter++){
            if((*tempiter)->clsname == currentprj.prjitems.at(i)){
                templisttest = (*tempiter)->test;
                (*tempiter)->clsname;
                templisttrain = (*tempiter)->train;
                templistval = (*tempiter)->val;
                templisttestcolor = (*tempiter)->testcolor;
                templisttraincolor = (*tempiter)->traincolor;
                templistvalcolor = (*tempiter)->valcolor;
            }
        }

        for (int j=0; j<clsitemsnow.count(); j++){
            check = false;
            for (int k=0; k<templisttest.count(); k++){
                if (clsitemsnow.at(j) == templisttest.at(k)){
                    templisttestcolor[k] = "green";
                    check = true;
                }
            }
            for (int k=0; k<templisttrain.count(); k++){
                if (clsitemsnow.at(j) == templisttrain.at(k)){
                    templisttraincolor[k] = "green";
                    check = true;
                }
            }
            for (int k=0; k<templistval.count(); k++){
                if (clsitemsnow.at(j) == templistval.at(k)){
                    templistvalcolor[k] = "green";
                    check = true;
                }
            }
            //append nocolor into test
            if (check == false){
                templisttest.append(clsitemsnow.at(j));
                templisttestcolor.append("nocolor");
            }

        }



        for (QLinkedList<Templist*>::iterator tempiter = templistlist.begin(); tempiter != templistlist.end(); tempiter++){
            if((*tempiter)->clsname == currentprj.prjitems.at(i)){
                (*tempiter)->test = templisttest;
                (*tempiter)->train = templisttrain;
                (*tempiter)->val = templistval;
                (*tempiter)->testcolor = templisttestcolor;
                (*tempiter)->traincolor = templisttraincolor;
                (*tempiter)->valcolor = templistvalcolor;
            }
        }
    }


    int currentlen;
    int goaltest;
    int goaltrain;
    int goalval;
    int replacecount;

    int removecount;


    //sync percentage
    for (QLinkedList<Templist*>::iterator tempiter = templistlist.begin(); tempiter != templistlist.end(); tempiter++){
        currentlen = (*tempiter)->test.count() + (*tempiter)->train.count() + (*tempiter)->val.count();
        goaltest = globaltestvalue*currentlen/100;
        goaltrain = globaltrainvalue*currentlen/100;
        goalval = globalvalvalue*currentlen/100;

        if ((*tempiter)->test.count() > goaltest){
            replacecount = (*tempiter)->test.count() - goaltest;
            for (int i=0; i<replacecount; i++){
                check = false;
                removecount = 0;
                for (int j=0; j<(*tempiter)->testcolor.count(); j++){
                    if ((*tempiter)->testcolor.at(j) == "nocolor" && check == false && (*tempiter)->train.count() < goaltrain){
                        (*tempiter)->train.append((*tempiter)->test.at(j));
                        (*tempiter)->traincolor.append("nocolor");
                        (*tempiter)->test.removeAt(j-removecount);
                        (*tempiter)->testcolor.removeAt(j-removecount);
                        removecount = removecount+1;
                        check = true;
                    }
                    if ((*tempiter)->testcolor.at(j) == "nocolor" && check == false && (*tempiter)->val.count() < goalval){
                        (*tempiter)->val.append((*tempiter)->test.at(j));
                        (*tempiter)->valcolor.append("nocolor");
                        (*tempiter)->test.removeAt(j-removecount);
                        (*tempiter)->testcolor.removeAt(j-removecount);
                        removecount = removecount+1;
                        check = true;
                    }
                }
                removecount = 0;
                for (int j=0; j<(*tempiter)->testcolor.count(); j++){
                    if ((*tempiter)->testcolor.at(j) == "green" && check == false && (*tempiter)->train.count() < goaltrain){
                        (*tempiter)->train.append((*tempiter)->test.at(j));
                        (*tempiter)->traincolor.append("blue_test");
                        (*tempiter)->test.removeAt(j-removecount);
                        (*tempiter)->testcolor.removeAt(j-removecount);
                        removecount = removecount+1;
                        check = true;
                    }
                    if ((*tempiter)->testcolor.at(j) == "green" && check == false && (*tempiter)->val.count() < goalval){
                        (*tempiter)->val.append((*tempiter)->test.at(j));
                        (*tempiter)->valcolor.append("blue_test");
                        (*tempiter)->test.removeAt(j-removecount);
                        (*tempiter)->testcolor.removeAt(j-removecount);
                        removecount = removecount+1;
                        check = true;
                    }
                }

            }
        }

        if ((*tempiter)->train.count() > goaltrain){
            replacecount = (*tempiter)->train.count() - goaltrain;
            for (int i=0; i<replacecount; i++){
                check = false;
                removecount = 0;
                for (int j=0; j<(*tempiter)->traincolor.count(); j++){
                    if ((*tempiter)->traincolor.at(j) == "nocolor" && check == false && (*tempiter)->test.count() < goaltest){
                        (*tempiter)->test.append((*tempiter)->train.at(j));
                        (*tempiter)->testcolor.append("nocolor");
                        (*tempiter)->train.removeAt(j-removecount);
                        (*tempiter)->traincolor.removeAt(j-removecount);
                        removecount = removecount+1;
                        check = true;
                    }
                    if ((*tempiter)->traincolor.at(j) == "nocolor" && check == false && (*tempiter)->val.count() < goalval){
                        (*tempiter)->val.append((*tempiter)->train.at(j));
                        (*tempiter)->valcolor.append("nocolor");
                        (*tempiter)->train.removeAt(j-removecount);
                        (*tempiter)->traincolor.removeAt(j-removecount);
                        removecount = removecount+1;
                        check = true;
                    }
                }
                removecount = 0;
                for (int j=0; j<(*tempiter)->traincolor.count(); j++){
                    if ((*tempiter)->traincolor.at(j) == "green" && check == false && (*tempiter)->test.count() < goaltest){
                        (*tempiter)->test.append((*tempiter)->train.at(j));
                        (*tempiter)->testcolor.append("blue_train");
                        (*tempiter)->train.removeAt(j-removecount);
                        (*tempiter)->traincolor.removeAt(j-removecount);
                        removecount = removecount+1;
                        check = true;
                    }
                    if ((*tempiter)->traincolor.at(j) == "green" && check == false && (*tempiter)->val.count() < goalval){
                        (*tempiter)->val.append((*tempiter)->train.at(j));
                        (*tempiter)->valcolor.append("blue_train");
                        (*tempiter)->train.removeAt(j-removecount);
                        (*tempiter)->traincolor.removeAt(j-removecount);
                        removecount = removecount+1;
                        check = true;
                    }
                }

            }
        }

        if ((*tempiter)->val.count() > goalval){
            replacecount = (*tempiter)->val.count() - goalval;
            for (int i=0; i<replacecount; i++){
                check = false;
                removecount = 0;
                for (int j=0; j<(*tempiter)->valcolor.count(); j++){
                    if ((*tempiter)->valcolor.at(j) == "nocolor" && check == false && (*tempiter)->test.count() < goaltest){
                        (*tempiter)->test.append((*tempiter)->val.at(j));
                        (*tempiter)->testcolor.append("nocolor");
                        (*tempiter)->val.removeAt(j-removecount);
                        (*tempiter)->valcolor.removeAt(j-removecount);
                        removecount = removecount+1;
                        check = true;
                    }
                    if ((*tempiter)->valcolor.at(j) == "nocolor" && check == false && (*tempiter)->train.count() < goaltrain){
                        (*tempiter)->train.append((*tempiter)->val.at(j));
                        (*tempiter)->traincolor.append("nocolor");
                        (*tempiter)->val.removeAt(j-removecount);
                        (*tempiter)->valcolor.removeAt(j-removecount);
                        removecount = removecount+1;
                        check = true;
                    }
                }
                removecount = 0;
                for (int j=0; j<(*tempiter)->valcolor.count(); j++){
                    if ((*tempiter)->valcolor.at(j) == "green" && check == false && (*tempiter)->test.count() < goaltest){
                        (*tempiter)->test.append((*tempiter)->val.at(j));
                        (*tempiter)->testcolor.append("blue_val");
                        (*tempiter)->val.removeAt(j-removecount);
                        (*tempiter)->valcolor.removeAt(j-removecount);
                        removecount = removecount+1;
                        check = true;
                    }
                    if ((*tempiter)->valcolor.at(j) == "green" && check == false && (*tempiter)->train.count() < goaltrain){
                        (*tempiter)->train.append((*tempiter)->val.at(j));
                        (*tempiter)->traincolor.append("blue_val");
                        (*tempiter)->val.removeAt(j-removecount);
                        (*tempiter)->valcolor.removeAt(j-removecount);
                        removecount = removecount+1;
                        check = true;
                    }
                }

            }
        }

    }



    //pick no color to random it!

    int testcount;
    int traincount;
    int valcount;
    int oldcount;
    QStringList randomall;
    QStringList temptest;
    QStringList temptestcolor;
    QStringList temptrain;
    QStringList temptraincolor;
    QStringList tempval;
    QStringList tempvalcolor;

    for (QLinkedList<Templist*>::iterator tempiter = templistlist.begin(); tempiter != templistlist.end(); tempiter++){
        randomall.clear();
        temptest.clear();
        temptestcolor.clear();
        temptrain.clear();
        temptraincolor.clear();
        tempval.clear();
        tempvalcolor.clear();
        testcount = 0;
        traincount = 0;
        valcount = 0;

        oldcount = (*tempiter)->test.count();
        for (int i=0; i<oldcount; i++){
            if ((*tempiter)->testcolor.at(i) == "nocolor"){
                randomall.append((*tempiter)->test.at(i));
                testcount = testcount + 1;
            }
            else{
                temptest.append((*tempiter)->test.at(i));
                temptestcolor.append((*tempiter)->testcolor.at(i));
            }
        }

        oldcount = (*tempiter)->train.count();
        for (int i=0; i<oldcount; i++){
            if ((*tempiter)->traincolor.at(i) == "nocolor"){
                randomall.append((*tempiter)->train.at(i));
                traincount = traincount + 1;
            }
            else{
                temptrain.append((*tempiter)->train.at(i));
                temptraincolor.append((*tempiter)->traincolor.at(i));
            }
        }

        oldcount = (*tempiter)->val.count();
        for (int i=0; i<oldcount; i++){
            if ((*tempiter)->valcolor.at(i) == "nocolor"){
                randomall.append((*tempiter)->val.at(i));
                valcount = valcount + 1;
            }
            else{
                tempval.append((*tempiter)->val.at(i));
                tempvalcolor.append((*tempiter)->valcolor.at(i));
            }
        }

        std::random_shuffle(randomall.begin(), randomall.end());

        for (int i=0; i<testcount; i++){
            temptest.append(randomall.at(i));
            temptestcolor.append("nocolor");
        }
        for (int i=testcount; i<testcount+traincount; i++){
            temptrain.append(randomall.at(i));
            temptraincolor.append("nocolor");
        }
        for (int i=testcount+traincount; i<testcount+traincount+valcount; i++){
            tempval.append(randomall.at(i));
            tempvalcolor.append("nocolor");
        }

        (*tempiter)->test = temptest;
        (*tempiter)->testcolor = temptestcolor;
        (*tempiter)->train = temptrain;
        (*tempiter)->traincolor = temptraincolor;
        (*tempiter)->val = tempval;
        (*tempiter)->valcolor = tempvalcolor;

    }


    for (QLinkedList<Templist*>::iterator tempiter = templistlist.begin(); tempiter != templistlist.end(); tempiter++){
        for (int i=0; i<(*tempiter)->test.count(); i++){
            (*tempiter)->testischeck.append("no");
        }
        for (int i=0; i<(*tempiter)->train.count(); i++){
            (*tempiter)->trainischeck.append("no");
        }
        for (int i=0; i<(*tempiter)->val.count(); i++){
            (*tempiter)->valischeck.append("no");
        }
    }

}

//Show the current list
void MainWindow::ShowList(){
    QString clsname = ui->comboBoxCls->currentText();
    ui->lsWidgetTest->clear();
    ui->lsWidgetTrain->clear();
    ui->lsWidgetVal->clear();
    ui->lsWidgetDel->clear();
    QStringList templisttest;
    QStringList templisttestcolor;
    QStringList templisttestischeck;
    QStringList templisttrain;
    QStringList templisttraincolor;
    QStringList templisttrainischeck;
    QStringList templistval;
    QStringList templistvalcolor;
    QStringList templistvalischeck;
    QStringList templistdel;
    QStringList templistdelischeck;
    for (QLinkedList<Templist*>::iterator tempiter = templistlist.begin(); tempiter != templistlist.end(); tempiter++){
        if((*tempiter)->clsname == clsname){
            templisttest = (*tempiter)->test;
            templisttrain = (*tempiter)->train;
            templistval = (*tempiter)->val;
            templistdel = (*tempiter)->del;
            templisttestcolor = (*tempiter)->testcolor;
            templisttraincolor = (*tempiter)->traincolor;
            templistvalcolor = (*tempiter)->valcolor;
            templisttestischeck = (*tempiter)->testischeck;
            templisttrainischeck = (*tempiter)->trainischeck;
            templistvalischeck = (*tempiter)->valischeck;
            templistdelischeck = (*tempiter)->delischeck;
        }
    }

    for (int i=0; i<templisttest.count(); i++){
        ui->lsWidgetTest->addItem(templisttest.at(i));
        ui->lsWidgetTest->item(i)->setFlags(ui->lsWidgetTest->item(i)->flags()| Qt::ItemIsUserCheckable);
        if (templisttestischeck.at(i) == "no"){
            ui->lsWidgetTest->item(i)->setCheckState(Qt::Unchecked);
        }
        else{
            ui->lsWidgetTest->item(i)->setCheckState(Qt::Checked);
        }

        if (templisttestcolor.at(i) == "green"){
            ui->lsWidgetTest->item(i)->setBackgroundColor(Qt::green);
        }
        if (templisttestcolor.at(i) == "red"){
            ui->lsWidgetTest->item(i)->setBackgroundColor(Qt::red);
        }
        if (templisttestcolor.at(i) == "blue_test" || templisttestcolor.at(i) == "blue_train" || templisttestcolor.at(i) == "blue_val"){
            ui->lsWidgetTest->item(i)->setBackgroundColor(Qt::cyan);
        }
    }

    for (int i=0; i<templisttrain.count(); i++){
        ui->lsWidgetTrain->addItem(templisttrain.at(i));
        ui->lsWidgetTrain->item(i)->setFlags(ui->lsWidgetTrain->item(i)->flags()| Qt::ItemIsUserCheckable);
        if (templisttrainischeck.at(i) == "no"){
            ui->lsWidgetTrain->item(i)->setCheckState(Qt::Unchecked);
        }
        else{
            ui->lsWidgetTrain->item(i)->setCheckState(Qt::Checked);
        }

        if (templisttraincolor.at(i) == "green"){
            ui->lsWidgetTrain->item(i)->setBackgroundColor(Qt::green);
        }
        if (templisttraincolor.at(i) == "red"){
            ui->lsWidgetTrain->item(i)->setBackgroundColor(Qt::red);
        }
        if (templisttraincolor.at(i) == "blue_test" || templisttraincolor.at(i) == "blue_train" || templisttraincolor.at(i) == "blue_val"){
            ui->lsWidgetTrain->item(i)->setBackgroundColor(Qt::cyan);
        }
    }

    for (int i=0; i<templistval.count(); i++){
        ui->lsWidgetVal->addItem(templistval.at(i));
        ui->lsWidgetVal->item(i)->setFlags(ui->lsWidgetVal->item(i)->flags()| Qt::ItemIsUserCheckable);
        if (templistvalischeck.at(i) == "no"){
            ui->lsWidgetVal->item(i)->setCheckState(Qt::Unchecked);
        }
        else{
            ui->lsWidgetVal->item(i)->setCheckState(Qt::Checked);
        }

        if (templistvalcolor.at(i) == "green"){
            ui->lsWidgetVal->item(i)->setBackgroundColor(Qt::green);
        }
        if (templistvalcolor.at(i) == "red"){
            ui->lsWidgetVal->item(i)->setBackgroundColor(Qt::red);
        }
        if (templistvalcolor.at(i) == "blue_test" || templistvalcolor.at(i) == "blue_train" || templistvalcolor.at(i) == "blue_val"){
            ui->lsWidgetVal->item(i)->setBackgroundColor(Qt::cyan);
        }
    }

    for (int i=0; i<templistdel.count(); i++){
        ui->lsWidgetDel->addItem(templistdel.at(i));
        ui->lsWidgetDel->item(i)->setFlags(ui->lsWidgetDel->item(i)->flags()| Qt::ItemIsUserCheckable);
        if (templistdelischeck.at(i) == "no"){
            ui->lsWidgetDel->item(i)->setCheckState(Qt::Unchecked);
        }
        else{
            ui->lsWidgetDel->item(i)->setCheckState(Qt::Checked);
        }

    }

    ui->lsWidgetTest->sortItems();
    ui->lsWidgetTrain->sortItems();
    ui->lsWidgetVal->sortItems();
    ui->lsWidgetDel->sortItems();
}

//Save the current list
void MainWindow::SaveList(QString currentcls){

    QStringList temptestischeck;
    QStringList temptrainischeck;
    QStringList tempvalischeck;
    QStringList tempdelischeck;
    for (QLinkedList<Templist*>::iterator tempiter = templistlist.begin(); tempiter != templistlist.end(); tempiter++){
        if ((*tempiter)->clsname == currentcls){
            if ((*tempiter)->test.count() != ui->lsWidgetTest->count()){return;}
            for (int i=0; i<(*tempiter)->test.count(); i++){
                for (int j=0; j<ui->lsWidgetTest->count(); j++){
                    if (ui->lsWidgetTest->item(j)->text() == (*tempiter)->test.at(i) && ui->lsWidgetTest->item(j)->checkState() == Qt::Checked){
                        temptestischeck.append("yes");
                    }
                    if (ui->lsWidgetTest->item(j)->text() == (*tempiter)->test.at(i) && ui->lsWidgetTest->item(j)->checkState() == Qt::Unchecked){
                        temptestischeck.append("no");
                    }
                }
            }

            for (int i=0; i<(*tempiter)->train.count(); i++){
                for (int j=0; j<ui->lsWidgetTrain->count(); j++){
                    if (ui->lsWidgetTrain->item(j)->text() == (*tempiter)->train.at(i) && ui->lsWidgetTrain->item(j)->checkState() == Qt::Checked){
                        temptrainischeck.append("yes");
                    }
                    if (ui->lsWidgetTrain->item(j)->text() == (*tempiter)->train.at(i) && ui->lsWidgetTrain->item(j)->checkState() == Qt::Unchecked){
                        temptrainischeck.append("no");
                    }
                }
            }

            for (int i=0; i<(*tempiter)->val.count(); i++){
                for (int j=0; j<ui->lsWidgetVal->count(); j++){
                    if (ui->lsWidgetVal->item(j)->text() == (*tempiter)->val.at(i) && ui->lsWidgetVal->item(j)->checkState() == Qt::Checked){
                        tempvalischeck.append("yes");
                    }
                    if (ui->lsWidgetVal->item(j)->text() == (*tempiter)->val.at(i) && ui->lsWidgetVal->item(j)->checkState() == Qt::Unchecked){
                        tempvalischeck.append("no");
                    }
                }
            }

            for (int i=0; i<(*tempiter)->del.count(); i++){
                for (int j=0; j<ui->lsWidgetDel->count(); j++){
                    if (ui->lsWidgetDel->item(j)->text() == (*tempiter)->del.at(i) && ui->lsWidgetDel->item(j)->checkState() == Qt::Checked){
                        tempdelischeck.append("yes");
                    }
                    if (ui->lsWidgetDel->item(j)->text() == (*tempiter)->del.at(i) && ui->lsWidgetDel->item(j)->checkState() == Qt::Unchecked){
                        tempdelischeck.append("no");
                    }
                }
            }


            (*tempiter)->testischeck = temptestischeck;
            (*tempiter)->trainischeck = temptrainischeck;
            (*tempiter)->valischeck = tempvalischeck;
            (*tempiter)->delischeck = tempdelischeck;
        }
    }



}

//Show the Picture
void MainWindow::ShowPicture(QString fileJPEG){

    QImage image;
    bool imgload;
    imgload = image.load(fileJPEG);
    int x = ui->graphicsView->width();
    int y = ui->graphicsView->height();
    image = image.scaled(x-5,y-5,Qt::KeepAspectRatio);
    //QGraphicsScene *graphic = new QGraphicsScene(this);
    graphic->clear();

    if (imgload == true){
        graphic -> addPixmap(QPixmap::fromImage(image));
    }
    else{
        QFont font;
        font.setPointSize(30);
        //font.setStyle(QFont::StyleItalic);
        graphic->addText("No Picture", font);
        //ui->graphicsView->setScene(graphic);
    }
    ui->graphicsView->setAlignment(Qt::AlignCenter);//???can't work O_Q
    ui->graphicsView->setScene(graphic);


    //ui->graphicsView->setAlignment(Qt::AlignHCenter);
    //ui->graphicsView->setAlignment(Qt::AlignVCenter);


}

//Refresh the image number, percentage, ...
void MainWindow::RefreshLabelText(){
    int testcount = ui->lsWidgetTest->count() ;
    int traincount = ui->lsWidgetTrain->count();
    int valcount = ui->lsWidgetVal->count();
    int totalcount = testcount + traincount + valcount;
    if (totalcount == 0){totalcount = 1;}
    QString testnum = QString::number(testcount);
    QString trainnum = QString::number(traincount);
    QString valnum = QString::number(valcount);
    QString testpercentage = QString::number((100*testcount)/totalcount);
    QString trainpercentage = QString::number((100*traincount)/totalcount);
    QString valpercentage = QString::number((100*valcount)/totalcount);
    QString totalnum = QString::number(totalcount);
    ui->labelTestNum->setText("Image Number : "+testnum+"("+testpercentage+"%)");
    ui->labelTrainNum->setText("Image Number : "+trainnum+"("+trainpercentage+"%)");
    ui->labelValNum->setText("Image Number : "+valnum+"("+valpercentage+"%)");
    ui->labelTotal->setText(ui->comboBoxCls->currentText()+" : "+totalnum);
    ui->labelTestNum->setAlignment(Qt::AlignCenter);
    ui->labelTrainNum->setAlignment(Qt::AlignCenter);
    ui->labelValNum->setAlignment(Qt::AlignCenter);
    ui->labelTotal->setAlignment(Qt::AlignLeft);
}

//Clear the file
void MainWindow::FileClear(QString file1){
    if (file1.isEmpty()){
        return;
    }
    QDir dir(file1);
    if(!dir.exists()){
        return;
    }
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo file, fileList){
        if (file.isFile()){
            file.dir().remove(file.fileName());
        }else{
            FileClear(file.absoluteFilePath());
        }
    }
    dir.rmpath(dir.absolutePath());
}

//Replace the string of file
void MainWindow::FileReplaceStr(QString file1, QString strold, QString strnew)
{
    QString strAll;
    QString tempStr;
    QStringList strList;
    int ind;
    QFile readFile(file1);
    if(readFile.open((QIODevice::ReadOnly|QIODevice::Text)))
    {
        QTextStream stream(&readFile);
        strAll=stream.readAll();
    }
    readFile.close();
    QFile writeFile(file1);
    if(writeFile.open(QIODevice::WriteOnly|QIODevice::Text))
    {
            QTextStream stream(&writeFile);
            strList=strAll.split("\n");
            for(int i=0;i<strList.count();i++)
            {
                tempStr = strList.at(i);
                for (int j=0; j<10; j++){
                    if (tempStr.contains(strold)){
                        ind = tempStr.indexOf(strold);
                        tempStr.replace(ind,strold.length(),QString(strnew));
                    }
                }
                stream<<tempStr;
                if(i!=strList.count()-1){
                    stream<<'\n';
                }
            }
    }
    writeFile.close();
}

//Set solver.prototxt's parameter
void MainWindow::SetSolver(){
    globalsolver.clear();
    globalsolver.append("\"multistep\"");
    globalsolver.append("false");
    globalsolver.append("GPU");
    globalsolver.append("true");
    globalsolver.append("\"SGD\"");
    globalsolver.append("\"detection\"");
    globalsolver.append("false");
    globalsolver.append("\"11point\"");
    globalsolver.append("0.001");
    globalsolver.append("0.1");
    globalsolver.append("0.9");
    globalsolver.append("0.0005");
    globalsolver.append("120000");
    globalsolver.append("1");
    globalsolver.append("619");
    globalsolver.append("1000");
    globalsolver.append("10");
    globalsolver.append("80000");
    globalsolver.append("0");
    globalsolver.append("10");
    globalsolver.append("80000, 100000, 1200000");
    globalsolver.append("\"obj_models/ORproject/source/train.prototxt\"");
    globalsolver.append("\"obj_models/ORproject/source/test.prototxt\"");
    globalsolver.append("\"obj_models/ORproject/sink/snapshot/ORproject\"");

}

//Set solver.prototxt's parameter's key
void MainWindow::SetSolverKey(){
    globalsolverkey.clear();
    globalsolverkey.append("lr_policy");
    globalsolverkey.append("test_initialization");
    globalsolverkey.append("solver_mode");
    globalsolverkey.append("snapshot_after_train");
    globalsolverkey.append("type");
    globalsolverkey.append("eval_type");
    globalsolverkey.append("debug_info");
    globalsolverkey.append("ap_version");
    globalsolverkey.append("base_lr");
    globalsolverkey.append("gamma");
    globalsolverkey.append("momentum");
    globalsolverkey.append("weight_decay");
    globalsolverkey.append("max_iter");
    globalsolverkey.append("iter_size");
    globalsolverkey.append("test_iter");
    globalsolverkey.append("test_interval");
    globalsolverkey.append("display");
    globalsolverkey.append("snapshot");
    globalsolverkey.append("device_id");
    globalsolverkey.append("average_loss");
    globalsolverkey.append("stepvalue");
    globalsolverkey.append("train_net");
    globalsolverkey.append("test_net");
    globalsolverkey.append("snapshot_prefix");


}

//SAVE the project!!
void MainWindow::SAVE(){

    if (ui->lsWidgetTest->count()==0 && ui->lsWidgetTrain->count()==0 && ui->lsWidgetVal->count()==0){
        QMessageBox::about(NULL, "Remind", "Empty List");
        return;
    }

    QString fname = currentprj.name;

    FileClear(fw + "/Categories/"+fname);
    QDir dir0(fw + "/Categories");
    dir0.mkdir(fname);



//create .prj
    QJsonObject jproject;
    {
        {
            QJsonObject slvr;
            for (int i=0; i<globalsolver.count(); i++){
                slvr.insert(globalsolverkey[i],globalsolver[i]);
            }
            jproject.insert("solver", slvr);
        }
        {
            QJsonArray cls;
            for (int i=0; i<currentprj.prjitems.count(); i++){
                cls.append(currentprj.prjitems.at(i));
            }
            jproject.insert("class", cls);
        }
        jproject.insert("project_name", fname);
        jproject.insert("workspace", fw);
        jproject.insert("version", "2.0.0");
    }

    QJsonDocument docproject(jproject);
    QString strproject(docproject.toJson());
    QFile prjfile(fw + "/Categories/" +fname+ ".prj");
    prjfile.open(QIODevice::WriteOnly);
    QTextStream prjout(&prjfile);
    prjout << strproject;
    prjfile.close();


    //SaveList(currentcls);


    QString shortxmlfolder;

    //create test.txt
    QStringList testlist;
    for (QLinkedList<Templist*>::iterator tempiter = templistlist.begin(); tempiter != templistlist.end(); tempiter++){
        for (QLinkedList<Classes*>::iterator clsiter = clslist.begin(); clsiter != clslist.end(); clsiter++){
            if ((*clsiter)->name == (*tempiter)->clsname){
                shortxmlfolder = (*clsiter)->xmlfoldershort;
            }
        }
        for (int i=0; i<(*tempiter)->test.count(); i++){
            if ((*tempiter)->testcolor.at(i) != "red"){
                testlist.append(shortxmlfolder+"/"+(*tempiter)->test.at(i)+".xml");
            }
        }
    }

    std::sort(testlist.begin(), testlist.end());
    QFile testfile(fw + "/Categories/" +fname+ "/test.txt");
    testfile.open(QIODevice::WriteOnly);
    QTextStream testout(&testfile);
    for (int i=0; i<testlist.count(); i++){
        testout << testlist.at(i) << "\n";
    }
    testfile.close();


    //create train.txt
    QStringList trainlist;
    for (QLinkedList<Templist*>::iterator tempiter = templistlist.begin(); tempiter != templistlist.end(); tempiter++){
        for (QLinkedList<Classes*>::iterator clsiter = clslist.begin(); clsiter != clslist.end(); clsiter++){
            if ((*clsiter)->name == (*tempiter)->clsname){
                shortxmlfolder = (*clsiter)->xmlfoldershort;
            }
        }
        for (int i=0; i<(*tempiter)->train.count(); i++){
            if ((*tempiter)->traincolor.at(i) != "red"){
                trainlist.append(shortxmlfolder+"/"+(*tempiter)->train.at(i)+".xml");
            }
        }
    }
    //std::sort(trainlist.begin(), trainlist.end());
    std::random_shuffle(trainlist.begin(), trainlist.end());
    QFile trainfile(fw + "/Categories/" +fname+ "/train.txt");
    trainfile.open(QIODevice::WriteOnly);
    QTextStream trainout(&trainfile);
    for (int i=0; i<trainlist.count(); i++){
        trainout << trainlist.at(i) << "\n";
    }
    trainfile.close();

    //create val.txt
    QStringList vallist;
    for (QLinkedList<Templist*>::iterator tempiter = templistlist.begin(); tempiter != templistlist.end(); tempiter++){
        for (QLinkedList<Classes*>::iterator clsiter = clslist.begin(); clsiter != clslist.end(); clsiter++){
            if ((*clsiter)->name == (*tempiter)->clsname){
                shortxmlfolder = (*clsiter)->xmlfoldershort;
            }
        }
        for (int i=0; i<(*tempiter)->val.count(); i++){
            if ((*tempiter)->valcolor.at(i) != "red"){
                vallist.append(shortxmlfolder+"/"+(*tempiter)->val.at(i)+".xml");
            }
        }
    }
    //std::sort(vallist.begin(), vallist.end());
    std::random_shuffle(vallist.begin(), vallist.end());
    QFile valfile(fw + "/Categories/" +fname+ "/val.txt");
    valfile.open(QIODevice::WriteOnly);
    QTextStream valout(&valfile);
    for (int i=0; i<vallist.count(); i++){
        valout << vallist.at(i) << "\n";
    }
    valfile.close();

    //create trainval.txt
    QStringList trainvallist;
    trainvallist = trainlist + vallist;
    //std::sort(trainvallist.begin(), trainvallist.end());
    std::random_shuffle(trainvallist.begin(), trainvallist.end());
    QFile trainvalfile(fw + "/Categories/" +fname+ "/trainval.txt");
    trainvalfile.open(QIODevice::WriteOnly);
    QTextStream trainvalout(&trainvalfile);
    for (int i=0; i<trainvallist.count(); i++){
        trainvalout << trainvallist.at(i) << "\n";
    }
    trainvalfile.close();

    //create labelmap.prototxt

    ///////////////////////////do there


    QStringList label;
    bool check = false;

    for (int i=0; i<currentprj.prjitems.count(); i++){
        for (QLinkedList<Classes*>::iterator clsiter = clslist.begin(); clsiter != clslist.end(); clsiter++){
            if (currentprj.prjitems.at(i) == (*clsiter)->name){
                for (int j=0; j<(*clsiter)->label.count(); j++){
                    check = false;
                    for (int k=0; k<label.count(); k++){
                        if (label.at(k) == (*clsiter)->label.at(j)){
                            check = true;
                        }
                    }
                    if (check == false){
                        label.append((*clsiter)->label.at(j));
                    }
                }
            }
        }
    }



    QFile labelfile(fw + "/Categories/" +fname+ "/labelmap.prototxt");
    labelfile.open(QIODevice::WriteOnly);
    QTextStream labelout(&labelfile);
    int labellen = label.count();
    QString labelitem;

    labelout << "item {\n";
    labelout << "  name: \"none_of_the_above\"\n";
    labelout << "  label: 0\n";
    labelout << "  display_name: \"background\"\n";
    labelout << "}\n";

    for (int i=0; i<labellen; i++){
        labelitem = label.at(i);
        labelout << "item {\n";
        labelout << "  name: \""+labelitem+"\"\n";
        labelout << "  label: "+QString::number(i+1)+"\n";
        labelout << "  display_name: \""+labelitem+"\"\n";
        labelout << "}\n";
    }
    labelfile.close();

    QDir dir1(fw + "/Categories/" +fname);
    dir1.mkdir("source");

    QString pathfrom;
    QString pathto;


    //pathfrom = fw + "/Categories/template/run.sh";
    pathfrom = "template/run.sh";
    pathto = fw + "/Categories/" + fname + "/source/run.sh";
    QFile::copy(pathfrom, pathto);

    //pathfrom = fw + "/Categories/template/stop.sh";
    pathfrom = "template/stop.sh";
    pathto = fw + "/Categories/" + fname + "/source/stop.sh";
    QFile::copy(pathfrom, pathto);

    pathfrom = "template/pdfreport.py";
    pathto = fw + "/Categories/" + fname + "/source/pdfreport.py";
    QFile::copy(pathfrom, pathto);

    QString testoutnum;
    QString clsnum;
    testoutnum = QString::number(testlist.count());
    clsnum = QString::number(currentprj.prjitems.count() + 1);

    FileReplaceStr(fw + "/Categories/" + fname + "/source/run.sh", "ORproject", fname);



    QProcess process(this);
    QStringList args;
    args.append("template/gen_prototxt.py");
    //args.append(fw+"/Categories/template/gen_prototxt.py");
    args.append(clsnum);
    args.append(testoutnum);
    args.append("obj_models/"+fname);
    args.append(fw + "/Categories/" + fname);
    process.start("template/gen_prototxt.sh",args);
    //process.start(fw+"/Categories/template/gen_prototxt.sh",args);
    process.waitForFinished(-1);


    QString strAll;
    QString tempStr;
    QString tempStr2;
    QStringList tempStrList;
    QStringList strList;
    QFile readFile(fw + "/Categories/" + fname + "/source/solver.prototxt");
    if(readFile.open((QIODevice::ReadOnly|QIODevice::Text)))
    {
        QTextStream stream(&readFile);
        strAll=stream.readAll();
    }
    readFile.close();
    QFile writeFile(fw + "/Categories/" + fname + "/source/solver.prototxt");
    if(writeFile.open(QIODevice::WriteOnly|QIODevice::Text))
    {
            QTextStream stream(&writeFile);
            strList=strAll.split("\n");
            for(int i=0;i<strList.count();i++)
            {
                tempStr = strList.at(i);
                tempStrList=tempStr.split(":");
                if (tempStrList.count()>1){
                    tempStr2=tempStrList[0];
                    for (int j=0;j<globalsolverkey.count();j++){
                        if (tempStr2.contains(globalsolverkey.at(j))){
                            if (tempStr2.contains("stepvalue") == false){
                                tempStrList[1]=globalsolver[j];
                            }
                            if (tempStr2.contains("snapshot_after_train")){
                                tempStrList[1]=globalsolver[3];
                            }
                        }
                    }
                        tempStr = tempStrList.at(0)+": "+tempStrList.at(1);
                }
                stream<<tempStr;
                if(i!=strList.count()-1){
                    stream<<'\n';
                }
            }
    }
    writeFile.close();

    FileReplaceStr(fw + "/Categories/" + fname + "/source/solver.prototxt", "ORproject", fname);




    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(NULL, "Done", "The project"+fname+"is saved at : \n"+ fw + "/Categories)\n Open the Training Manager?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes){
        QProcess process2(this);
        process2.startDetached("training_manager  "+ fw + "/Categories/" + currentprj.name + ".prj");
        qDebug() << "=D";}
    ui->actionOpen_Training_Manager->setEnabled(true);
}

void MainWindow::on_actionOpen_Training_Manager_triggered()
{
    QProcess process2(this);
    process2.startDetached("training_manager  "+ fw + "/Categories/" + currentprj.name + ".prj");
}






