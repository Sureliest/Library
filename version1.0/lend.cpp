#include "lend.h"
#include "ui_lend.h"
#include "address.h"
#include "book.h"
#include <QtWidgets>
#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include<QPushButton>
#include<QTextStream>
#include <QTextEdit>
Lend::Lend(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Lend)
{
    ui->setupUi(this);
}

Lend::~Lend()
{
    delete ui;
}


void Lend::on_sort_clicked()
{
    QVector<Book> vec;
    QFile file(AddressOfBookMessage);
    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        while(!stream.atEnd())
        {
            QStringList list=stream.readLine().split(QRegExp("\\s+"));
            Book b1(list.at(0),static_cast<QString>(list.at(1)).toInt(),list.at(2));
            vec.push_back(b1);
        }
    }
    ui->tableWidget->setRowCount(vec.count());
    ui->tableWidget->setColumnCount(3);

    QStringList header;
    header<<"书名"<<"编号"<<"类别";
    ui->tableWidget->setHorizontalHeaderLabels(header);


    for(int i=0;i<vec.count();i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(vec[i].getBook_name()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(vec[i].getBook_id()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(vec[i].getBook_kind())));
    }
    file.close();
}
