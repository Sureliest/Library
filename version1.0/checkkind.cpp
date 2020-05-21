#include "checkkind.h"
#include "ui_checkkind.h"
#include "address.h"
#include "book.h"
#include <QtWidgets>
#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include<QPushButton>
#include<QTextStream>
#include <QTextEdit>
CheckKind::CheckKind(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckKind)
{
    ui->setupUi(this);
}

CheckKind::~CheckKind()
{
    delete ui;
}

void CheckKind::on_pushButton_clicked()
{
    QFile file(AddressOfBookMessage);
    //int book_kind;
    int a=ui->lineEdit->text().toInt();
    QVector<Book> vec;
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream stream(&file);
        while(!stream.atEnd())
        {
            QStringList list=stream.readLine().split(QRegExp("\\s+"));
            if(list.contains(QString::number(a)))
            {
                Book b(list.at(0),static_cast<QString>(list.at(1)).toInt(),list.at(2));
                vec.push_back(b);
            }
        }
    }
    file.close();
    switch(a)
    {
    case 1:
        ui->label_3->setText(tr("理学"));
        break;
    case 2:
        ui->label_3->setText(tr("文学"));
        break;

    case 3:
        ui->label_3->setText(tr("计算机"));
        break;

    case 4:
        ui->label_3->setText(tr("美术"));
        break;
    default:break;
    }

    ui->tableWidget->setRowCount(vec.count());
    ui->tableWidget->setColumnCount(2);

    QStringList header;
    header<<"书名"<<"编号";
    ui->tableWidget->setHorizontalHeaderLabels(header);


    for(int i=0;i<vec.count();i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(vec[i].getBook_name()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(vec[i].getBook_id()));
        //ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(vec[i].getBook_kind())));
    }
}
