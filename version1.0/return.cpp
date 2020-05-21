#include "return.h"
#include "ui_return.h"
#include "address.h"
#include "book.h"
#include <QtWidgets>
#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include<QPushButton>
#include<QTextStream>
#include <QTextEdit>
#include <QTextCodec>
#include <QTextCodec>
#include"log.h"
Return::Return(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Return)
{
    ui->setupUi(this);

}

Return::~Return()
{
    delete ui;
}

void Return::on_pushButton_clicked()
{
    //QTextCodec *codec = QTextCodec::codecForName("GB2312");
    QString name;
    QFile usr(AddressOfCurrentMessage);
    if(usr.open(QIODevice::ReadOnly))
    {
        QTextStream u(&usr);
        while(!u.atEnd())
        {
            name=u.readLine();
        }
    }
    usr.close();
    QVector<Log> vec1;
    QFile file(AddressOfLogMessage);
    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        while(!stream.atEnd())
        {
            QStringList list=stream.readLine().split(QRegExp("\\s+"));
            if(list.contains(name)==true){
                Book b(list.at(0),static_cast<QString>(list.at(1)).toInt(),list.at(2));
                Log log(b,list.at(3),static_cast<QString>(list.at(4)).toInt(),static_cast<QString>(list.at(5)).toInt(),static_cast<QString>(list.at(6)).toInt());
                vec1.push_back(log);
            }
        }
    }
    ui->tableWidget->setRowCount(vec1.count());
    ui->tableWidget->setColumnCount(5);

    QStringList header;
    header<<"ID"<<"用户"<<"年"<<"月"<<"日";
    ui->tableWidget->setHorizontalHeaderLabels(header);

    for(int i=0;i<vec1.count();i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::fromStdString(vec1[i].getBook_id().toStdString())));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(name));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(vec1[i].get_year())));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(vec1[i].get_month()+1)));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(vec1[i].get_day())));
    }
    file.close();
}

void Return::on_OK_Button_clicked()
{
    int year,month,day;
    QString id=ui->lineEdit->text();
    QFile file(AddressOfLogMessage);
    //int line=0,i=0;
    QString list,line[20];
    QString listsmp;
    int i=0;
    if(file.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        QTextStream out(&file);
        while(!out.atEnd())
        {
            list=out.readLine();
            listsmp=list.simplified();
            if(!listsmp.contains(id))
            {
                line[i]=list;
                i++;
            }
            else{
                //获取日期
                year=2019;
                month=9;
                day=3;
            }
        }
    }
    file.resize(0);
    file.close();
    if(file.open(QIODevice::ReadWrite|QIODevice::Text))
    {

        QTextStream stream(&file);
        for(int j=0;j<i;j++)
        {
            stream<<line[j]<<endl;
        }
    }
    file.close();
    QString name;
    QFile sss(AddressOfCurrentMessage);
    if(sss.open(QIODevice::ReadOnly))
    {
        QTextStream u(&sss);
        while(!u.atEnd())
        {
            name=u.readLine();
        }
    }

    QStringList info[20];
    int i1=0;
    QFile usr(AddressOfUserMessage);
    if(usr.open(QIODevice::ReadWrite))
    {
        QTextStream out(&usr);
        while(!out.atEnd())
        {
            QStringList list=out.readLine().split(QRegExp("\\s+"));
            if(list.contains(name)){
                int current_book_num=list.at(3).toInt();
                //int max_book_num=list.at(4).toInt();
                if(current_book_num==0){
                    ui->info->setText(tr("信息错误"));
                }
                else
                {
                    int re=current_book_num-1;
                    QStringList l;
                    l<<list.at(0)<<list.at(1)<<list.at(2)<<QString::number(re)<<list.at(4);
                    list=l;
                    //year=list.at(5).toInt();
                    //month=list.at(6).toInt()
                    //check<<list.at(3)<<endl;
                }
            }
            info[i1]=list;
            i1++;
        }
    }
    usr.close();
    usr.resize(0);
    if(usr.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&usr);
        for(int j=0;j<i1;j++)
        {
            stream<<info[j].join(" ")<<endl;
        }
    }
    usr.close();
    int now_year=ui->yearEdit->text().toInt();
    int now_month=ui->monthEdit->text().toInt();
    int now_day=ui->dayEdit->text().toInt();

    int charge=0;
    charge=10*((now_year-year)*365+(now_month-month)*31+(now_day-day))/31;
    ui->info->setText(QString::number(charge));
}
