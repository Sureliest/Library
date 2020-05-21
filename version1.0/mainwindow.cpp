#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDialog"
#include "QMessageBox"
#include "dialog.h"//按ID查找书名
#include "dialog1.h"//登录用户
#include "library.h"
#include "lend.h"
#include "return.h"
#include <QtWidgets>
#include <QLabel>
#include <QLineEdit>
#include<QPushButton>
#include<QTextStream>
#include <QTextEdit>
#include "address.h"
#include "qfileinfo.h"
#include "checkkind.h"


QString info[2];
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowTitle("图书管理系统v1.0");
    ui->pushButton->setText("还书");
    ui->pushButton_3->setText("书库");
    ui->pushButton_2->setText("已借");
    ui->pushButton_4->setText("借书");
    ui->kind_button->setText("按类别查找");
    ui->statusBar->showMessage(tr("by 温柔白夜 "));
    //ui->statusBar->showMessage(info[0]);
}

MainWindow::~MainWindow()
{
    QFile file(AddressOfCurrentMessage);
    file.resize(0);
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Return *rt=new Return(this);
    rt->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    Library *lib=new Library(this);
    lib->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    Lend *ld=new Lend(this);
    ld->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    Dialog *dlg=new Dialog(this);
    dlg->show();
}

void MainWindow::on_action_E_triggered()
{
    QMessageBox b;
    b.setWindowTitle(tr("警告"));
    b.setIcon(QMessageBox::Warning);
    b.setText(tr(" 是否退出？"));
    QPushButton *yesBtn = b.addButton(tr("是(&Y)"),
                           QMessageBox::YesRole);
    b.addButton(tr("否(&N)"), QMessageBox::NoRole);
    b.exec();
    if(b.clickedButton()==yesBtn)
        qApp->quit();
}

void MainWindow::on_action_I_triggered()
{
    Dialog1 *dlg=new Dialog1(this);
    dlg->show();
    if(dlg->exec()==Dialog1::Accepted)
    {
        QFileInfo file(AddressOfCurrentMessage);
        //int size=file.size();
        if(file.size()!=0)
        {
            QString name;
            QFile usr(AddressOfCurrentMessage);
            if(usr.open(QIODevice::ReadOnly))
            {
                QTextStream out(&usr);
                while(!out.atEnd())
                {
                    name=out.readLine();
                    ui->label->setText(name+"用户，欢迎使用！");
                }
            }
            usr.close();
        }
        else
        {
            ui->label->setText(tr("密码错误"));
        }
    }
}

void MainWindow::on_kind_button_clicked()
{
    CheckKind *ck=new CheckKind(this);
    ck->show();
}
