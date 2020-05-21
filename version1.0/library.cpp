#include "library.h"
#include "ui_library.h"
#include "QDialog"
#include "QMessageBox"
#include "address.h"
#include "book.h"
#include "log.h"
#include <QtWidgets>
#include <QLabel>
#include<QPushButton>
#include<QTextStream>
#include <QTextEdit>
#include<QTextCodec>
Library::Library(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Library)
{
    ui->setupUi(this);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
}

Library::~Library()
{
    delete ui;
}

void Library::on_OK_Button_clicked()
{
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

    //QString bookname;
    for(int i=0;i<vec1.count();i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::fromStdString(vec1[i].getBook_id().toStdString())));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(name));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(vec1[i].get_year())));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(vec1[i].get_month())));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(vec1[i].get_day())));
    }
    file.close();
}
