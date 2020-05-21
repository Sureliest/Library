#include "logindialog.h"
#include "ui_logindialog.h"
#include"QMessageBox"
#include"QTextStream"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowTitle("用户登录");
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginbtn_clicked()
{
    if(ui->usrLineEdit->text()==tr("shine")&&ui->pwdLineEdit->text()==tr("123456"))
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this,tr("警告"),tr("用户名或密码错误"),QMessageBox::Ok);
        ui->usrLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->usrLineEdit->setFocus();
    }
}
