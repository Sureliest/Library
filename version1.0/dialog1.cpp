#include "dialog1.h"
#include "ui_dialog1.h"
#include "address.h"
#include <QtWidgets>
#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include<QPushButton>
#include<QTextStream>
#include <QTextEdit>
#include "user.h"
Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    ui->setupUi(this);
    ui->secondbox->hide();
    //ui->tribox->hide();
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);
    setColumnRange();
}

Dialog1::~Dialog1()
{
    delete ui;
}
void Dialog1::setColumnRange()
{
    //ui->priboxcolumn->clear();
    ui->secondboxcolumn->clear();
    //ui->triboxcolumn->clear();

    //ui->secondboxcolumn->addItem(tr("无"));
    ui->secondboxcolumn->addItem(tr("普通用户"));
    ui->secondboxcolumn->addItem(tr("高级用户"));
    //ui->triboxcolumn->addItem(tr("None"));

    /*QChar ch=first;
    while(ch<=last)
    {
        ui->priboxcolumn->addItem(QString(ch));
        ch=ch.unicode()+1;
    }*/
}


void Dialog1::on_OKButton_clicked()
{
    int flag=0;
    QString usrname=ui->usrnameEdit->text();
    QString usrpwd=ui->usrpwdEdit->text();
    QString usrlevel=ui->secondboxcolumn->currentText();
    QFile file(AddressOfUserMessage);
    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        while(!stream.atEnd())
        {
            QStringList list=stream.readLine().split(QRegExp("\\s+"));
            if(list.contains(usrname)==true&&list.contains(usrpwd)==true){
                flag=1;
                QFile currentUsr(AddressOfCurrentMessage);
                if(currentUsr.open(QIODevice::ReadWrite))
                {
                    QTextStream in(&currentUsr);
                    in<<usrname;
                }
                currentUsr.close();
                break;
            }
        }
    }
    file.close();
    if(flag==0)
    {
        bool level=true;
        if(usrlevel.compare(QStringLiteral("普通用户"))==0)
        {
            level=false;
        }
        User u(usrname,usrpwd,level);
        QFile file2(AddressOfUserMessage);
        if(file2.open(QIODevice::WriteOnly|QIODevice::Append))
        {
            QTextStream in(&file2);
            in<<u.getUsr_name()<<" "<<u.getUsr_pwd()<<" "<<u.getLevel()<<" "<<u.getCurrent()<<" "<<u.getMax()<<"\r\n";
        }
        file2.close();
        QFile cu2(AddressOfCurrentMessage);
        if(cu2.open(QIODevice::ReadWrite))
        {
            QTextStream in(&cu2);
            in<<usrname;
        }
        cu2.close();
    }
    //Accepted();
}
